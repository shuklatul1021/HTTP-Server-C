#include <stdio.h>
#include "client.h"

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
