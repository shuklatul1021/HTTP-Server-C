#define _GNU_SOURCE  
#include <stdio.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAX_CLIENTS 256

client_info_t client_state[MAX_CLIENTS];

int main(){
    initialize_client_state(client_state, MAX_CLIENTS);

    int server_socket_fd, client_socket_fd , nfds, free_server_slot;
    struct sockaddr_in server_info , client_info;
    
    int client_size = 0;

    server_info.sin_family = AF_INET;
    server_info.sin_addr.s_addr = 0;
    server_info.sin_port = htons(5555);

    if((server_socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        perror("socket");
        close(server_socket_fd);
        return 1;
    }

    int server_bind = bind(server_socket_fd, (struct sockaddr *)&server_info, sizeof(server_info));
    if(server_bind == -1){
        perror("bind");
        printf("Bind Error");
        close(server_socket_fd);
        return -1;
    }

    int server_listen = listen(server_socket_fd, 0);
    if(server_listen == -1){
        perror("listen");
        printf("Listen Error");
        close(server_socket_fd);
        return -1;
    }

    printf("Server is listening on port 5555\n");

    while(1){
        // Server Accept Retune Client file descriptor
        int server_accept = accept(server_socket_fd, (struct sockaddr *)&client_info, &client_size);
        if(server_accept == -1){
            perror("accept");
            printf("Accept Error");
            close(server_socket_fd);
            return -1;
        }
    }
}