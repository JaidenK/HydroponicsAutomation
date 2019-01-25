#include <stdio.h> /* printf, sprintf */
#include <stdlib.h> /* exit */
#include <unistd.h> /* read, write, close */
#include <string.h> /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h> /* struct hostent, gethostbyname */


#include "sensor_data.h"
#include "http.h"

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
