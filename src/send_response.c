#include <stdio.h>
#include <string.h>
#include "client.h"
#include "cJSON.h"

char *get_status_message(int status_code) {
    switch (status_code) {
        case 200:
            return "OK";
        case 400:
            return "Bad Request";
        case 404:
            return "Not Found";
        case 500:
            return "Internal Server Error";
        default:
            return "Unknown Status";
    }
}


cJSON *get_json_status_message(char *response_body, int status_code){
    cJSON *root = cJSON_CreateObject();
    if(root == NULL){
        return NULL;
    }
    if(status_code >= 200 && status_code < 300) {
        cJSON_AddStringToObject(root, "message" , "Successfully Abstracted Data");
        cJSON_AddStringToObject(root, "data" , response_body);
        cJSON_AddBoolToObject(root, "success" , true);
    } else {
        cJSON_AddStringToObject(root, "message" , response_body);
        cJSON_AddBoolToObject(root, "success" , false);
    }
    return root;
}

int send_data(client_info_t *client_state, char *response_body , int status_code) {
    if (client_state == NULL || response_body == NULL) return;
    char response[2048];

    char *json_string = cJSON_Print(get_json_status_message(response_body, status_code));

    sprintf(response,
        "HTTP/1.1 %d %s\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: %ld\r\n"
        "\r\n"
        "%s",
        status_code,
        get_status_message(status_code),
        strlen(json_string),
        json_string
    );

    send(client_state->client_fd, response, strlen(response), 0);
    return 0;
}
