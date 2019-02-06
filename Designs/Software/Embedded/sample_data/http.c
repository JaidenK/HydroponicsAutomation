#include "http.h"
#include "sensor_data.h"

#include <stdio.h> /* printf, sprintf */
#include <stdlib.h> /* exit */
#include <unistd.h> /* read, write, close */
#include <string.h> /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h> /* struct hostent, gethostbyname */

#include <ctype.h> // isspace()

// Data received during the HTTP request
char httpGETdata[2048];

// The port on the server to connect to. 80 for HTTP traffic.
int portno = 80;
// host ip
char *host;// =        "sdp.ballistaline.com";
// The format of the http message to be sent. A simple GET request.
char *message_fmt;// = "GET http://sdp.ballistaline.com/dataReceiver.php?%s HTTP/1.0\r\n\r\n";

// Will store the details about the server, like it's IP, given a URL
struct hostent *server;

struct sockaddr_in serv_addr;
int sockfd;

int sendMessage();
int receiveResponse();

void error(const char *msg) { perror(msg); exit(0); }

int HTTP_Init(char *host_) {
   host = host_;
   sprintf(message_fmt,"GET http://%s/%%s?%%s HTTP/1.0\r\n\r\n",host);
   return 0;
}

int HTTP_SetHost(char *host_) {
   host = host_;
   return 0;
}

int HTTP_SetMessageFormat(char *message_fmt_) {
   message_fmt = message_fmt_;
   return 0;
}

int HTTP_Get(char *page, char *data, char *response, unsigned int size) {
   /* create the socket */
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   if (sockfd < 0) error("ERROR opening socket");

   /* lookup the ip address */
   server = gethostbyname(host);
   if (server == NULL) error("ERROR, no such host");

   /* fill in the parameters */
   // Clear the message so that garbage doesn't go on the end.
   char message[4096];
   memset(message,0,sizeof(message));
   sprintf(message,message_fmt,page,data);
   //printf("Request:\n%s\n",message);

   /* fill in the structure */
   memset(&serv_addr,0,sizeof(serv_addr));
   serv_addr.sin_family = AF_INET; // Address Family
   serv_addr.sin_port = htons(portno);
   memcpy(&serv_addr.sin_addr.s_addr,server->h_addr,server->h_length);

   /* connect the socket */
   if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
   error("ERROR connecting");

   sendMessage(message);

   receiveResponse(response, size);

   /* close the socket */
   close(sockfd);

   return 0;
}


int sendMessage(char *message) {
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

int receiveResponse(char *response, unsigned int size) {
   /* receive the response */
   // Bytes received
   int received = 0;
   int bytes = 0;
   do {
      bytes = read(sockfd,response+received,size-received);
      if (bytes < 0) {
         error("ERROR reading response from socket");
      }
      if (bytes == 0) {
         break;
      }
      received+=bytes;
   } while (received < size);

   // Receive buffer full
   if (received == size) {
      error("ERROR storing complete response from socket");
   }

   return 0;
}


// int httpGET(char *message) {

//    getGETstr(httpGETdata,sd);
//    //printf("%s\n",httpGETdata);
//    //https://stackoverflow.com/questions/22077802/simple-c-example-of-doing-an-http-post-and-consuming-the-response
//    /* first what are we going to send and where are we going to send it? */

//    /* create the socket */
//    sockfd = socket(AF_INET, SOCK_STREAM, 0);
//    if (sockfd < 0) error("ERROR opening socket");

//    /* lookup the ip address */
//    server = gethostbyname(host);
//    if (server == NULL) error("ERROR, no such host");

//    /* fill in the parameters */
//    sprintf(message,message_fmt,httpGETdata);
//    //printf("Request:\n%s\n",message);

//    /* fill in the structure */
//    memset(&serv_addr,0,sizeof(serv_addr));
//    serv_addr.sin_family = AF_INET; // Address Family
//    serv_addr.sin_port = htons(portno);
//    memcpy(&serv_addr.sin_addr.s_addr,server->h_addr,server->h_length);

//    /* connect the socket */
//    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
//    error("ERROR connecting");

//    sendMessage();

//    receiveResponse();

//    /* close the socket */
//    close(sockfd);

//    /* process response */
//    //printf("Response:\n%s\n",response);
//    parseResponse(response,sd);

//    return 0;
// }
