/** @file http.h
    @brief HTTP service
    @author Jaiden King

Descriptions

*/

#ifndef _HTTP_H
#define _HTTP_H

#include "sensor_data.h"

typedef enum {
    HTTP_INIT,
    HTTP_IDLE,
    HTTP_OPENING_SOCKET,
    HTTP_CONNECTING,
    HTTP_SENDING_MESSAGE,
    HTTP_RECEIVING_MESSAGE,
    HTTP_CLOSING_SOCKET,
    HTTP_ERROR,
    HTTP_NUMBER_OF_STATUSES,
} HTTPStatus_t;

static const char *HTTP_StatusNames[] = {
    "HTTP_INIT",
    "HTTP_IDLE",
    "HTTP_OPENING_SOCKET",
    "HTTP_CONNECTING",
    "HTTP_SENDING_MESSAGE",
    "HTTP_RECEIVING_MESSAGE",
    "HTTP_CLOSING_SOCKET",
    "HTTP_ERROR",
    "HTTP_NUMBER_OF_STATUSES",
};

/** Initializes the HTTP library with a particular host and automatically 
    sets the message format to a GET with that site.
    @note This function should be called before any other HTTP library functions
          or no host will be set.

    @param host A string containing the base url of the website. (e.g. "www.example.com")
    @return 0 on success, 1 otherwise.

*/
int HTTP_Init(char *host);

/** Updates the host. Does not change message format.
    @param host String specifying the new host.
    @return 0 on success, 1 otherwise.
*/
int HTTP_SetHost(char *host);

/** Update the message format.
    @param message_format String of the new message format. 
    @return 0 on success, 1 otherwise.

    @warning Changing the message format will likely break the system.
*/
int HTTP_SetMessageFormat(char *message_format);

/** Sends a GET request and stores the response.
    @param[in] page String URL of the page you're sending the message too.
                This will be appended to the host.
    @param[in] data String of the data to be appended to the response. (e.g. "key1=val1&key2=val2")
    @param[out] response String where the complete HTTP reponse will be stored.
    @param[in] size Maximum number of bytes to store in response.
*/
int HTTP_Get(char *page, char *data);

/** If data is ready, copies it into response. 
    @return 1 If data was ready and read, 0 otherwise.
*/
int HTTP_GetResponse(char *response);

HTTPStatus_t HTTP_getStatus();
void HTTP_setStatus(HTTPStatus_t newStatus);
const char *HTTP_getStatusString();

#endif

