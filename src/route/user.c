#include <string.h>
#include <stdio.h>
#include "route/user.h"
#include "cJSON.h"

int register_user(char *request_body, User *users, int *user_index){
    cJSON *json = cJSON_Parse(request_body);
    if (!json) {
        return -1;
    }
    cJSON *email = cJSON_GetObjectItem(json, "email");
    cJSON *password = cJSON_GetObjectItem(json, "password");
    if (!email || !password) {
        cJSON_Delete(json);
        return -1;
    }
    printf("Registering user with email: %s and password: %s\n", email->valuestring, password->valuestring);

    // Check if user already exists
    for(int i = 0 ; i < *user_index; i++) {
        if (strcmp(users[i].email, email->valuestring) == 0) {
            cJSON_Delete(json);
            return -1; // User already exists
        }
    }

    users[*user_index].id = *user_index + 1;
    strcpy(users[*user_index].email, email->valuestring);
    strcpy(users[*user_index].password, password->valuestring);
    users[*user_index].index = *user_index;
    (*user_index)++;

    printf("User registered successfully with email: %s\n", email->valuestring);
    printf("User Id: %d\n", users[*user_index - 1].id);

    cJSON_Delete(json);
    return 0;
}

int login_user(char *request_body, User *users, int *user_index){
    cJSON *json = cJSON_Parse(request_body);
    if (!json) {
        return -1;
    }
    cJSON *email = cJSON_GetObjectItem(json, "email");
    cJSON *password = cJSON_GetObjectItem(json, "password");
    if (!email || !password) {
        cJSON_Delete(json);
        return -1;
    }
    // Process login logic here
    for (int i = 0; i < *user_index; i++) {
        if (strcmp(users[i].email, email->valuestring) == 0 && strcmp(users[i].password, password->valuestring) == 0) {
            cJSON_Delete(json);
            return 0;
        }
    }
    cJSON_Delete(json);
    return -1;
}

int get_user(int user_id, User *users, int *user_index) {
    for (int i = 0; i < *user_index; i++) {
        if (users[i].id == user_id) {
            return i;
        }
    }
    return -1;
}


