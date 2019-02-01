#include "http.h"
#include "sensor_data.h"

#include <stdio.h> /* printf, sprintf */
#include <stdlib.h> /* exit */
#include <unistd.h> /* read, write, close */
#include <string.h> /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h> /* struct hostent, gethostbyname */

// Data received during the HTTP request
char httpGETdata[2048];

// The port on the server to connect to. 80 for HTTP traffic.
int portno = 80;
// host ip
char *host =        "sdp.ballistaline.com";
// The format of the http message to be sent. A simple GET request.
char *message_fmt = "GET http://sdp.ballistaline.com/dataReceiver.php?%s HTTP/1.0\r\n\r\n";

// Will store the details about the server, like it's IP, given a URL
struct hostent *server;

struct sockaddr_in serv_addr;
int sockfd;
char message[1024],response[4096];

void error(const char *msg) { perror(msg); exit(0); }

int sendMessage() {
   /* send the request */
   // Total number of bytes in the message
   int total = strlen(message);
   // Bytes sent
   int sent = 0;
   int bytes = 0;
   do {
      bytes = write(sockfd,message+sent,total-sent);
      if (bytes < 0) {
         error("ERROR writing message to socket");
      }
      if (bytes == 0) {
         break;
      }
      sent += bytes;
   } while (sent < total);

   return 0;
}

int receiveResponse() {
   /* receive the response */
   // Clear the response string
   memset(response,0,sizeof(response));
   // Max bytes possible to receive 
   int total = sizeof(response)-1;
   // Bytes received
   int received = 0;
   int bytes = 0;
   do {
      bytes = read(sockfd,response+received,total-received);
      if (bytes < 0) {
         error("ERROR reading response from socket");
      }
      if (bytes == 0) {
         break;
      }
      received+=bytes;
   } while (received < total);

   // Receive buffer full
   if (received == total) {
      error("ERROR storing complete response from socket");
   }

   return 0;
}

// TODO something more useful than a print satement
void parseResponse(char *response) {
   //printf("Parsing response:\n");
   // printf("%s\n",response);
   char *tok; 
   tok = strtok(response,"\n");
   while(tok != NULL) {
      char *val;
      val = strchr(tok,'=');
      if(val != NULL) {
         // If val was null then no '=' was found and this isn't a line
         // with a key=value pair
         val++;
         char arg[256];
         memset(arg,'\0',256);
         strncpy(arg,tok,val-tok-1);
         printf("arg: %s\nval: %s\n", arg, val);


         if(strcmp(arg,"new_record") == 0) {
            if(strcmp(val,"success")==0) {
               printf("Record created successfully.\n");
            }else{
               printf("Error logging data:\n\t%s\n", val);
            }
         }

         if(strncmp(tok,"water_target",12) == 0) {
            printf("Water\n");
         }
      }

      // Move to the next line of the response
      tok = strtok(NULL,"\n");
   }
}

int logData(struct SensorData *sd) {

   getGETstr(httpGETdata,sd);
   //printf("%s\n",httpGETdata);
   //https://stackoverflow.com/questions/22077802/simple-c-example-of-doing-an-http-post-and-consuming-the-response
   /* first what are we going to send and where are we going to send it? */

   /* create the socket */
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   if (sockfd < 0) error("ERROR opening socket");

   /* lookup the ip address */
   server = gethostbyname(host);
   if (server == NULL) error("ERROR, no such host");

   /* fill in the parameters */
   sprintf(message,message_fmt,httpGETdata);
   //printf("Request:\n%s\n",message);

   /* fill in the structure */
   memset(&serv_addr,0,sizeof(serv_addr));
   serv_addr.sin_family = AF_INET; // Address Family
   serv_addr.sin_port = htons(portno);
   memcpy(&serv_addr.sin_addr.s_addr,server->h_addr,server->h_length);

   /* connect the socket */
   if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
   error("ERROR connecting");

   sendMessage();

   receiveResponse();

   /* close the socket */
   close(sockfd);

   /* process response */
   //printf("Response:\n%s\n",response);
   parseResponse(response);

   return 0;
}
