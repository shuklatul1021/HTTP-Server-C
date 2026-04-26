#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

#include "client.h"


int handle_get_route (client_info_t *client_state) {
    if (client_state ==  NULL || response_body == NULL || !status_code){
        printf("More Argument Is Require");
        return -1;
    }
    if(strcmp(client_state->request.path , "/api/v1/todo/get_todo") == 0){
        
    }

}

int handle_post_route(client_info_t *client_state){
    // Routing Logic For POST Request
    // This Is Most Brute Force Approch Better Can be Done 

    // User Auth for User 
    if(strcmp(client_state->request.path, "/api/v1/auth/register") == 0){
        int user_registration_status = register_user(client_state->request.body);
        if (user_registration_status == 0) {
            send_data(client_state, "User Registered Successfully", 200);
        } else {
            send_data(client_state, "User Registration Failed", 400);
        }
    }
    if(strcmp(client_state->request.path, "/api/v1/auth/login") == 0){
        int user_login_status = login_user(client_state->request.body);
        if (user_login_status == 0) {
            send_data(client_state, "User Logged In Successfully", 200);
        } else {
            send_data(client_state, "User Login Failed", 400);
        }
    }
    if(strcmp(client_state->request.path, "/api/v1/auth/user") == 0){
        int get_user_status = get_user();
        if(get_user_status == 0){
            // Handle 
        }else {
            // Handle
        }
    }


    // Post Endpoint for The Adding Todo
    if(strcmp(client_state->request.path, "/api/v1/todo/add_todo") == 0){
        int add_todo_result = add_todo(client_state->request.body);
        if(add_todo_result == 0){
            send_data(client_state , "Todo Added Successfully", 200);
        }else {
            send_data(client_state , "Error While Adding Todo", 400);
        }
    }
    
    return 0;
}

int handle_put_route(client_info_t *client_state){
    if(strcmp(client_state->request.path, "/api/v1/todo/update_todo") == 0){
        int update_todo_result = update_todo(client_state->request.body);
        if(update_todo_result == 0){
            int send_resposne = send_data(client_state , "Todo Updeated Successfully", 200);
            if(send_resposne == -1){
                printf("Error While Send Data For Updating The Todo");
                return -1;
            }
        } else {
            int send_resposne = send_data(client_state , "Error While updating Todo", 400);
            if(send_resposne == -1){
                printf("Error While Send Data For Updating The Todo Form Error Endpoint");
                return -1;
            }
        }
    }

    return 0;
}

int handle_delete_route(client_info_t *client_state){
    if(strcmp(client_state->request.path, "/api/v1/todo/delete_todo") == 0){
        int delete_todo_result = delete_todo(client_state->request.body);
        if(delete_todo_result == 0){
            int send_resposne_result = send_data(client_state , "Todo Deleted Successfully" , 200);
            if (send_resposne_result == 0) {
                printf("Send Response is Successfully And Data is Send To Client");
                return 0;
            }else{
                printf("Error While Sending Response");
                return -1;
            }
        } else {
            int send_resposne = send_data(client_state , "Error While Deleting Todo", 400);
            if(send_resposne == -1){
                printf("Error While Send Data For Updating The Todo Form Error Endpoint");
                return -1;
            }
        }
    }
    return 0;
}
