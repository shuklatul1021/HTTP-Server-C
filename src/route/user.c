#include <string.h>
#include <stdio.h>
#include "route/user.h"
#include "cJSON.h"

typedef struct  
{
    int id;
    char email[256];
    char password[256];
} User;

User users[100]; // Simple in-memory user storage
int index = 0;


int register_user(char *request_body){
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
    for(int i = 0 ; i < index; i++) {
        if (strcmp(users[i].email, email->valuestring) == 0) {
            cJSON_Delete(json);
            return -1; // User already exists
        }
    }

    users[index].id = index + 1;
    strcpy(users[index].email, email->valuestring);
    strcpy(users[index].password, password->valuestring);
    index++;
    cJSON_Delete(json);
    return 0;
}

int login_user(char *request_body){
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
    for (int i = 0; i < index; i++) {
        if (strcmp(users[i].email, email->valuestring) == 0 && strcmp(users[i].password, password->valuestring) == 0) {
            cJSON_Delete(json);
            return 0;
        }
    }
    cJSON_Delete(json);
    return -1;
}

int get_user(int user_id){
    for (int i = 0; i < index; i++) {
        if (users[i].id == user_id) {
            return i;
        }
    }
    return -1;
}




