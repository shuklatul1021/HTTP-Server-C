#ifndef SERVER_UTILS
#define SERVER_UTILS

#include <netinet/in.h>

#include "client.h"

int socket_object_init(struct sockaddr_in *server_info, int *opt, int server_info_len);
void initialize_client_state(client_info_t *client_state_machine, int MAX_CLIENTS);
int find_empty_slot(client_info_t *client_state_machine, int MAX_CLIENTS);
int find_empty_slot_fd(client_info_t *client_state_machine, int MAX_CLIENTS, int match_fd);

#endif