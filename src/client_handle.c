
#include "server.h"
#include "client.h"
#include "utils.h"
#include "response.h"

void handle_client(int client_fd , char *client_data){
    printf("Data From Client: %s\n", client_data);
    return;
}