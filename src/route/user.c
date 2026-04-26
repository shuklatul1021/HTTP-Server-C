#include <string.h>
#include <stdio.h>
#include "route/user.h"
#include "cJSON.h"

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
    // Process registration logic here
    /**
     * Database Logic for Registering User
     */
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
    cJSON_Delete(json);
    return 0;
}

int get_user(){
    return 0;
}




