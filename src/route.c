#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

#include "client.h"

void send_data(client_info_t *client_state){
     char response[2048];

    sprintf(response,
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: %ld\r\n"
        "\r\n"
        "%s",
        strlen(client_state->request.body),
        client_state->request.body
    );

    send(client_state->client_fd, response, strlen(response), 0);
}

int handle_get_route(client_info_t *client_state){
    printf("Inside The Get Route Handler\n");
    send_data(client_state);
}

int handle_post_route(client_info_t *client_state){
    return 0;
}

int handle_put_route(client_info_t *client_state){
    return 0;
}

int handle_delete_route(client_info_t *client_state){
    return 0;
}
