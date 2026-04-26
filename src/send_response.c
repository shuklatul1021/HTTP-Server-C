#include <stdio.h>
#include "client.h"

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

int send_data(client_info_t *client_state, char *response_body , int status_code) {
    if (client_state == NULL || response_body == NULL) return;
    char response[2048];

    sprintf(response,
        "HTTP/1.1 %d %s\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: %ld\r\n"
        "\r\n"
        "%s",
        status_code,
        get_status_message(status_code),
        strlen(response_body),
        response_body
    );

    send(client_state->client_fd, response, strlen(response), 0);
    return 0;
}
