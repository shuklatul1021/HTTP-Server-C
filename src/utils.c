#include <stdio.h>
#include "utils.h"
#include "client.h"


void initialize_client_state(client_info_t *client_state_machine, int MAX_CLIENTS){
    for(int i = 0; i < MAX_CLIENTS; i++){
        client_state_machine[i].client_fd = -1;
        client_state_machine[i].client_state = NEW_CONNECTION;
        memset(client_state_machine[i].client_data , 0, 1040);
    }
}

int find_empty_slot(client_info_t *client_state_machine, int MAX_CLIENTS){
    for(int i = 0; i < MAX_CLIENTS; i++){
        if(client_state_machine[i].client_fd == -1){
            return i;
        }
    }
    return -1;
}

int find_empty_slot_fd(client_info_t *client_state_machine, int MAX_CLIENTS, int match_fd){
    for(int i = 0; i < MAX_CLIENTS; i++){
        if(client_state_machine[i].client_fd == match_fd){
            return i;
        }
    }
    return -1;
}