#include <stdio.h>
#include <string.h>
#include "notifications.h"
#include "sensor_data.h"

// Used to send the "startup" notification.
static int isNotifcationsRunning = 0;

typedef enum {
   LOW, HIGH
} StorageState_t;

typedef struct {
   int high;
   int low;
   StorageState_t state;
} Thresholds;

Thresholds h2o_stored_thresh = {
   20,
   10,
   HIGH
};

Thresholds pH_Up_thresh = {
   20,
   10,
   HIGH
};

Thresholds pH_Down_thresh = {
   20,
   10,
   HIGH
};

Thresholds ec_stored_thresh = {
   20,
   10,
   HIGH
};



int getNotification(SensorData *sd, char *notificationStr) {
   /*switch(flow_thresh.state) {
      case LOW:
         if(sd->flow_measured > flow_thresh.high) {
            flow_thresh.state = HIGH;
            printf("Flow normal.\n");
         }
         break;
      case HIGH:
         if(sd->flow_measured < flow_thresh.low) {
            flow_thresh.state = LOW;
            printf("Flow low.\n");
         }
         break;
   }*/
   int numberOfNotifications = 0;
   if(!isNotifcationsRunning) {
      isNotifcationsRunning = 1;
      printf("Your controller has restarted.\n");
      sprintf(notificationStr,"Your%%20hydroponics%%20controller%%20has%%20restarted.");
      numberOfNotifications++;
   }
   switch(h2o_stored_thresh.state) {
      case LOW:
         if(sd->h2o_stored > h2o_stored_thresh.high) {
            h2o_stored_thresh.state = HIGH;
            printf("Water storage low.\n");
            sprintf(notificationStr,"Water%%20storage%%20low.");
            numberOfNotifications++;
         }
         break;
      case HIGH:
         if(sd->h2o_stored < h2o_stored_thresh.low) {
            h2o_stored_thresh.state = LOW;
            printf("Water storage normal.\n");
            sprintf(notificationStr,"Water%%20storage%%20normal.");
            numberOfNotifications++;
         }
         break;
   }
   switch(pH_Down_thresh.state) {
      case LOW:
         if(sd->ph_down_stored > pH_Down_thresh.high) {
            pH_Down_thresh.state = HIGH;
            printf("pH Down storage low.\n");
            sprintf(notificationStr,"pH%%20Down%%20storage%%20low.");
            numberOfNotifications++;
         }
         break;
      case HIGH:
         if(sd->ph_down_stored < pH_Down_thresh.low) {
            pH_Down_thresh.state = LOW;
            printf("pH Down storage normal.\n");
            sprintf(notificationStr,"pH%%20Down%%20storage%%20normal.");
            numberOfNotifications++;
         }
         break;
   }
   switch(pH_Up_thresh.state) {
      case LOW:
         if(sd->ph_up_stored > pH_Up_thresh.high) {
            pH_Up_thresh.state = HIGH;
            printf("pH Up storage low.\n");
            sprintf(notificationStr,"pH%%20Up%%20storage%%20low.");
            numberOfNotifications++;
         }
         break;
      case HIGH:
         if(sd->ph_up_stored < pH_Up_thresh.low) {
            pH_Up_thresh.state = LOW;
            printf("pH Up storage normal.\n");
            sprintf(notificationStr,"pH%%20Up%%20storage%%20normal.");
            numberOfNotifications++;
         }
         break;
   }
   switch(ec_stored_thresh.state) {
      case LOW:
         if(sd->ec_stored > ec_stored_thresh.high) {
            ec_stored_thresh.state = HIGH;
            printf("Nutrient storage low.\n");
            sprintf(notificationStr,"Nutrient%%20storage%%20low.");
            numberOfNotifications++;
         }
         break;
      case HIGH:
         if(sd->ec_stored < ec_stored_thresh.low) {
            ec_stored_thresh.state = LOW;
            printf("Nutrient storage normal.\n");
            sprintf(notificationStr,"Nutrient%%20storage%%20normal.");
            numberOfNotifications++;
         }
         break;
   }
   if(numberOfNotifications==0) {
      // Clear the notification string if no new notifications
      memset(notificationStr,0,strlen(notificationStr));
   }
   return numberOfNotifications;
}
