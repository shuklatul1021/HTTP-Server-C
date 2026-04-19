#define _GNU_SOURCE
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <poll.h>

#include "server.h"
#include "client.h"
#include "utils.h"
#include "response.h"

#define MAX_CLIENTS 256

client_info_t client_state[MAX_CLIENTS];


int main() {
  int server_socket_fd, client_socket_fd, free_server_slot;
  struct sockaddr_in server_info, client_info;

  socklen_t client_len = sizeof(client_info);
  struct pollfd pool_fds[MAX_CLIENTS + 1];
  // Number of file descriptors currently in the pool
  int num_fds = 0;
  int opt = 1;

  initialize_client_state(client_state, MAX_CLIENTS);

  memset(&server_info, 0, sizeof(server_info));
  server_info.sin_family = AF_INET;
  server_info.sin_addr.s_addr = htonl(INADDR_ANY);
  server_info.sin_port = htons(5555);

  int socket_t = socket_object_init(&server_info, &opt, sizeof(server_info));
  if(socket_t == -1){
    printf("Failed To Create Socket Object");
    exit(EXIT_FAILURE);
  }

  printf("Server is listening on port 5555\n");

  // Setting up the pollfd structure for the server socket
  memset(pool_fds, 0, sizeof(pool_fds));
  pool_fds[0].fd = socket_t;
  pool_fds[0].events = POLLIN;
  num_fds = 1;

  while (1) {
    // Adding All The Active Client for pool_fd
    int ii = 1;
    for(int i = 0; i < MAX_CLIENTS; i++){
      if(client_state[i].client_fd != -1){
        pool_fds[ii].fd = client_state[i].client_fd;
        pool_fds[ii].events = POLLIN;
        ii++;
      }
    }

    int n_event_t = poll(pool_fds, num_fds, -1);
    if(n_event_t == -1){
      perror("poll");
      exit(EXIT_FAILURE);
    }

    // Checking for An New Event 
    if(pool_fds[0].revents & POLLIN){
      if((client_socket_fd = accept(socket_t, (struct sockaddr *)&client_info , &client_len)) == -1){
        perror("accept");
        continue;
      }

      printf("New Connection Connected : %s:%d\n", inet_ntoa(client_info.sin_addr), ntohs(client_info.sin_port));

      free_server_slot = find_empty_slot(client_state, MAX_CLIENTS);
      if(free_server_slot == -1){
        printf("Server Is Full : Closing New Connection");
        close(client_socket_fd);
      }else {
        client_state[free_server_slot].client_fd = client_socket_fd;
        client_state[free_server_slot].client_state = NEW_CONNECTION;
        num_fds++;
        printf("Slot : %d has fd %d\n", free_server_slot, client_state[free_server_slot].client_fd);        
      }
      n_event_t--;
    }

    // Check Each Client For Read/write Activity
    for(int i = 1 ; i <= num_fds && n_event_t > 0 ; i++){
        if(pool_fds[i].revents & POLLIN){
          n_event_t--;
 
          int temp_fd = pool_fds[i].fd;
          int find_slot = find_empty_slot_fd(client_state, MAX_CLIENTS, temp_fd);
          ssize_t byte_read = read(temp_fd, client_state[find_slot].client_data, sizeof(client_state[find_slot].client_data));
          if(byte_read <= 0){
            close(temp_fd);
            if(find_slot == -1){
              printf("Tried to close the FD\n");
            }else {
              client_state[find_slot].client_fd = -1;
              client_state[find_slot].client_state = DISCONNECTED;
              printf("Client Disconnected Error\n");
              num_fds--;
            }
          }else{
            handle_client(temp_fd , client_state[find_slot].client_data, (int)byte_read, &client_state[find_slot]);
          }
        }
    }

  }
}
