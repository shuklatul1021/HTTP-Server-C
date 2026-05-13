#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

#include "route/todo.h"
#include "route/user.h"
#include "route.h"
#include "cJSON.h"
#include "client.h"


int handle_get_route (client_info_t *client_state, User *users, Todo *todos, int *user_index, int *todo_index) {
    if (client_state ==  NULL){
        printf("More Argument Is Require");
        return -1;
    }
    int user_id = -1;
    for(int i = 0 ; i < client_state->request.header_count; i++){
        if(strcmp(client_state->request.headers[i][0], "User-ID") == 0){
            user_id = atoi(client_state->request.headers[i][1]);
            printf("User ID : %d\n", user_id);
        }
    }


    if(strcmp(client_state->request.path , "/api/v1/todo/get_todo") == 0){
        char *get_todo = get_user_todo(user_id, todos, todo_index);
        if(get_todo != NULL){
            send_data(client_state, get_todo, 200);
        } else {
            send_data(client_state, "Todo Not Found", 400);
        }
    }
    
    if(strcmp(client_state->request.path, "/api/v1/user/me") == 0){
        int get_user_index = get_user(user_id, users, user_index);
        if(get_user_index == 0){
            cJSON *root = cJSON_CreateObject();
            if(root == NULL){
                printf("Error While Creating JSON Object F0r User Data");
                return -1;
            }
            cJSON_AddNumberToObject(root, "id",  users[get_user_index].id);
            cJSON_AddStringToObject(root, "email", users[get_user_index].email);
            cJSON_AddStringToObject(root, "password", users[get_user_index].password);
            cJSON_AddNumberToObject(root, "index", users[get_user_index].index);

            char *user_deatils = cJSON_Print(root);
            send_data(client_state, user_deatils, 200);
        }else {
            send_data(client_state, "User Not Found", 401);
        }
    }

}

int handle_post_route(client_info_t *client_state, User *users, Todo *todos, int *user_index, int *todo_index){
    // Routing Logic For POST Request
    // This Is Most Brute Force Approch Better Can be Done    
    if (client_state ==  NULL){
        printf("More Argument Is Require");
        return -1;
    }
    int user_id = -1;
    for(int i = 0 ; i < client_state->request.header_count; i++){
        if(strcmp(client_state->request.headers[i][0], "User-ID") == 0){
            user_id = atoi(client_state->request.headers[i][1]);
            printf("User ID : %d\n", user_id);
        }
    }

    // User Auth for User 
    if(strcmp(client_state->request.path, "/api/v1/auth/register") == 0){
        int user_registration_status = register_user(client_state->request.body, users, user_index);
        if (user_registration_status == 0) {
            send_data(client_state, "User Registered Successfully", 200);
        } else {
            send_data(client_state, "User Registration Failed", 400);
        }
    }
    if(strcmp(client_state->request.path, "/api/v1/auth/login") == 0){
        int user_login_status = login_user(client_state->request.body, users, user_index);
        if (user_login_status == 0) {
            send_data(client_state, "User Logged In Successfully", 200);
        } else {
            send_data(client_state, "User Login Failed", 400);
        }
    }

    // Post Endpoint for The Adding Todo
    if(strcmp(client_state->request.path, "/api/v1/todo/add_todo") == 0){
        int add_todo_result = add_todo(client_state->request.body, todos, todo_index);
        if(add_todo_result == 0){
            send_data(client_state , "Todo Added Successfully", 200);
        }else {
            send_data(client_state , "Error While Adding Todo", 400);
        }
    }
    
    return 0;
}

int handle_put_route(client_info_t *client_state, User *users , Todo *todos, int *user_index, int *todo_index){
    if(strcmp(client_state->request.path, "/api/v1/todo/update_todo") == 0){
        int update_todo_result = update_todo(client_state->request.body, todos, todo_index);
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

int handle_delete_route(client_info_t *client_state, User *users, Todo *todos, int *user_index, int *todo_index){
    if(strcmp(client_state->request.path, "/api/v1/todo/delete_todo") == 0){
        int delete_todo_result = delete_todo(client_state->request.body, todos, todo_index);
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
