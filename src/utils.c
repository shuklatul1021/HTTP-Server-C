#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>

#include "server.h"
#include "client.h"
#include "utils.h"
#include "response.h"

int socket_object_init(struct sockaddr_in *server_info, int *opt, int server_info_len)
{
    int server_socket_fd, set_sock_opt_t, server_bind_t, server_listen;
    if ((server_socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        printf("Socket Creation Failed");
        close(server_socket_fd);
        return -1;
    }
    if ((set_sock_opt_t = setsockopt(server_socket_fd, SOL_SOCKET, SO_REUSEADDR, opt, sizeof(*opt))) == -1)
    {
        perror("setsockopt");
        printf("Setsockopt Failed");
        close(server_socket_fd);
        return -1;
    }

    if ((server_bind_t = bind(server_socket_fd, (struct sockaddr *)server_info, server_info_len)) == -1)
    {
        perror("bind");
        printf("Bind Error");
        close(server_socket_fd);
        return -1;
    }
    if ((server_listen = listen(server_socket_fd, 10)) == -1)
    {
        perror("listen");
        printf("Listen Error");
        close(server_socket_fd);
        return -1;
    }

    return server_socket_fd;
}

void initialize_client_state(client_info_t *client_state_machine, int MAX_CLIENTS)
{
    for (int i = 0; i < MAX_CLIENTS; i++)
    {
        client_state_machine[i].client_fd = -1;
        client_state_machine[i].client_state = NEW_CONNECTION;
        memset(client_state_machine[i].client_data, 0, sizeof(client_state_machine[i].client_data));
    }
}

int find_empty_slot(client_info_t *client_state_machine, int MAX_CLIENTS)
{
    for (int i = 0; i < MAX_CLIENTS; i++)
    {
        if (client_state_machine[i].client_fd == -1)
        {
            return i;
        }
    }
    return -1;
}

int find_empty_slot_fd(client_info_t *client_state_machine, int MAX_CLIENTS, int match_fd)
{
    for (int i = 0; i < MAX_CLIENTS; i++)
    {
        if (client_state_machine[i].client_fd == match_fd)
        {
            return i;
        }
    }
    return -1;
}