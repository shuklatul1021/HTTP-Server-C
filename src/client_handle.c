#include <stdio.h>

#include "server.h"
#include "client.h"
#include "utils.h"
#include "response.h"

void handle_client(int client_fd, char *client_data, int data_len) {
    printf("Client %d says: %.*s\n", client_fd, data_len, client_data);
}