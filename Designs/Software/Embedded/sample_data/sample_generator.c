#include <stdio.h> /* printf, sprintf */
#include <stdlib.h> /* exit */
#include <unistd.h> /* read, write, close */
#include <string.h> /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h> /* struct hostent, gethostbyname */

void error(const char *msg) { perror(msg); exit(0); }

struct SensorData {
   double h2o_level;
   double h2o_stored;
   double ph_level;
   double ph_up_stored;
   double ph_down_stored;
   double ec_level;
   double ec_stored;
   double temp_measured;
   double flow_measured;
   double flow_target;
   double ph_target;
   double ec_target;
};

void setRandomData(struct SensorData *sd) {
   sd->h2o_level =       rand() % 256;
   sd->h2o_stored =      rand() % 256;
   sd->ph_level =        rand() % 256;
   sd->ph_up_stored =    rand() % 256;
   sd->ph_down_stored =  rand() % 256;
   sd->ec_level =        rand() % 256;
   sd->ec_stored =       rand() % 256;
   sd->temp_measured =   rand() % 256;
   sd->flow_measured =   rand() % 256;
   sd->flow_target =     rand() % 256;
   sd->ph_target =       rand() % 256;
   sd->ec_target =       rand() % 256;
}

void getGETstr(char *buf, struct SensorData *sd) {
   sprintf(
      buf,
      "ProductID=password&"
      "h2o_level=%f&"
      "h2o_stored=%f&"
      "ph_level=%f&"
      "ph_up_stored=%f&"
      "ph_down_stored=%f&"
      "ec_level=%f&"
      "ec_stored=%f&"
      "temp_measured=%f&"
      "flow_measured=%f&"
      "flow_target=%f&"
      "ph_target=%f&"
      "ec_target=%f",
      sd->h2o_level,
      sd->h2o_stored,
      sd->ph_level,
      sd->ph_up_stored,
      sd->ph_down_stored,
      sd->ec_level,
      sd->ec_stored,
      sd->temp_measured,
      sd->flow_measured,
      sd->flow_target,
      sd->ph_target,
      sd->ec_target
   );
}

int main(int argc,char *argv[])
{
   struct SensorData *sd = malloc(sizeof(*sd));
   setRandomData(sd);
   char httpGETdata[2048];
   getGETstr(httpGETdata,sd);
   printf("%s\n",httpGETdata);

   /* first what are we going to send and where are we going to send it? */
   int portno =        80;
   char *host =        "sdp.ballistaline.com";
   char *message_fmt = "GET http://sdp.ballistaline.com/dataReceiver.php?%s HTTP/1.0\r\n\r\n";

   struct hostent *server;
   struct sockaddr_in serv_addr;
   int sockfd, bytes, sent, received, total;
   char message[1024],response[4096];

   if (argc < 2) { puts("Parameters: <GET>"); exit(0); }

   /* fill in the parameters */
   sprintf(message,message_fmt,httpGETdata);
   printf("Request:\n%s\n",message);

   /* create the socket */
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   if (sockfd < 0) error("ERROR opening socket");

   /* lookup the ip address */
   server = gethostbyname(host);
   if (server == NULL) error("ERROR, no such host");

   /* fill in the structure */
   memset(&serv_addr,0,sizeof(serv_addr));
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_port = htons(portno);
   memcpy(&serv_addr.sin_addr.s_addr,server->h_addr,server->h_length);

   /* connect the socket */
   if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
     error("ERROR connecting");

   /* send the request */
   total = strlen(message);
   sent = 0;
   do {
     bytes = write(sockfd,message+sent,total-sent);
     if (bytes < 0)
         error("ERROR writing message to socket");
     if (bytes == 0)
         break;
     sent+=bytes;
   } while (sent < total);

   /* receive the response */
   memset(response,0,sizeof(response));
   total = sizeof(response)-1;
   received = 0;
   do {
     bytes = read(sockfd,response+received,total-received);
     if (bytes < 0)
         error("ERROR reading response from socket");
     if (bytes == 0)
         break;
     received+=bytes;
   } while (received < total);

   if (received == total)
     error("ERROR storing complete response from socket");

   /* close the socket */
   close(sockfd);

   /* process response */
   printf("Response:\n%s\n",response);

   return 0;
}
