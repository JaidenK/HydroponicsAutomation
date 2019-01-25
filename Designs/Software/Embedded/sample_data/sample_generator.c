#include <stdio.h> /* printf, sprintf */
#include <stdlib.h> /* exit */
#include <unistd.h> /* read, write, close */
#include <string.h> /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h> /* struct hostent, gethostbyname */
#include <time.h> // for random

void error(const char *msg) { perror(msg); exit(0); }


void parseResponse(char *response) {
   //printf("Parsing response:\n");
   char *tok; 
   tok = strtok(response,"\n");
   while(tok != NULL) {
      if(strncmp(tok,"new_record",10) == 0) {
         if(strcmp(tok+11,"success")==0) {
            printf("Record created successfully.\n");
         }else{
            printf("Error logging data:\n\t%s\n", tok+11);
         }
      }
      tok = strtok(NULL,"\n");
   }
}

void setRandomData(struct SensorData *sd) {
   time_t t;
   srand((unsigned)time(&t));
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

void randomWalk(struct SensorData *sd) {
   sd->h2o_level +=       (double)rand()/RAND_MAX*2.0-1.0;
   sd->h2o_stored +=      (double)rand()/RAND_MAX*2.0-1.0;
   sd->ph_level +=        (double)rand()/RAND_MAX*2.0-1.0;
   sd->ph_up_stored +=    (double)rand()/RAND_MAX*2.0-1.0;
   sd->ph_down_stored +=  (double)rand()/RAND_MAX*2.0-1.0;
   sd->ec_level +=        (double)rand()/RAND_MAX*2.0-1.0;
   sd->ec_stored +=       (double)rand()/RAND_MAX*2.0-1.0;
   sd->temp_measured +=   (double)rand()/RAND_MAX*2.0-1.0;
   sd->flow_measured +=   (double)rand()/RAND_MAX*2.0-1.0;
   sd->flow_target +=     (double)rand()/RAND_MAX*2.0-1.0;
   sd->ph_target +=       (double)rand()/RAND_MAX*2.0-1.0;
   sd->ec_target +=       (double)rand()/RAND_MAX*2.0-1.0;
}

int logData(struct SensorData *sd) {

   char httpGETdata[2048];
   getGETstr(httpGETdata,sd);
   //printf("%s\n",httpGETdata);
   //https://stackoverflow.com/questions/22077802/simple-c-example-of-doing-an-http-post-and-consuming-the-response
   /* first what are we going to send and where are we going to send it? */
   int portno =        80;
   char *host =        "sdp.ballistaline.com";
   char *message_fmt = "GET http://sdp.ballistaline.com/dataReceiver.php?%s HTTP/1.0\r\n\r\n";

   struct hostent *server;
   struct sockaddr_in serv_addr;
   int sockfd, bytes, sent, received, total;
   char message[1024],response[4096];

   /* fill in the parameters */
   sprintf(message,message_fmt,httpGETdata);
   //printf("Request:\n%s\n",message);

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
   //printf("Response:\n%s\n",response);
   parseResponse(response);

   return 0;
}

int main(int argc,char *argv[])
{
   int logCount = 60;
   int delaySeconds = 1;
   if(argc > 1) {
      logCount = atoi(argv[1]);
   }
   if(argc > 2) {
      delaySeconds = atoi(argv[2]);
      if(delaySeconds<1) {
         delaySeconds = 1;
      }
   }
   printf("Generating %d logs every %d seconds.\n",logCount,delaySeconds);

   struct SensorData *sd = malloc(sizeof(*sd));
   setRandomData(sd);

   for (int i = 0; i < logCount; i++) {
      sleep(delaySeconds);
      randomWalk(sd);
      logData(sd);
   }
}
