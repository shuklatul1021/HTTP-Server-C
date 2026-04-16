#ifndef SERVER_UTILS
#define SERVER_UTILS
#include <sys/socket.h>

int socket_object_init(sockaddr_in *server_info, int *opt);
int initialize_client_state(client_info_t *client_state_machine, int MAX_CLIENTS);
int find_empty_slot(client_info_t *client_state_machine, int MAX_CLIENTS);

#endif