#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "cJSON.h"
#include "route/todo.h"

int add_todo(char *request_body, Todo *user_todo, int *index) {
    cJSON *json = cJSON_Parse(request_body);
    if(!json){
        return -1;
    }
    cJSON *title = cJSON_GetObjectItem(json, "title");
    cJSON *description = cJSON_GetObjectItem(json, "description");
    cJSON *isdone = cJSON_GetObjectItem(json, "isdone");
    cJSON *userid = cJSON_GetObjectItem(json, "userid");
    if(!title && !description && !isdone && !userid){
        printf("Require More Argumnet In Body");
        return -1;
    }
    printf("User ID When Adding Todo : %d\n", userid->valueint);
    user_todo[*index].id = *index + 1;
    strcpy(user_todo[*index].title , title->valuestring);
    strcpy(user_todo[*index].description , description->valuestring);
    user_todo[*index].userid = userid->valueint;
    if(strcmp(isdone->valuestring , "true")){
        user_todo[*index].isdone = true;   
    } else {
        user_todo[*index].isdone = false;
    }
    (*index)++;
    return 0;
}

void get_all_todo(Todo *user_todo, int *index){
    printf("These Details Of All Todo");
    for(int i = 0; i < *index; i++){
        printf("Index %d\n:",i);
        printf("Id: %d\n", user_todo[i].id);
        printf("Title: %s\n", user_todo[i].title);
        printf("Description: %s\n", user_todo[i].description);
        printf("IsBoolen: %d\n", user_todo[i].isdone);
        printf("UserId: %d\n", user_todo[i].userid);
        printf("---------------------------------------");
        
    }
}

char *get_user_todo(int user_id, Todo *user_todo, int *index){
    printf("These Details Of All Todo For User %d\n:",user_id);
    get_all_todo(user_todo, index);
    cJSON *root = cJSON_CreateArray();
    for(int i = 0; i < *index; i++){
        if(user_todo[i].userid == user_id){
            cJSON *object = cJSON_CreateObject();
            cJSON_AddNumberToObject(object, "id" , user_todo[i].id);
            cJSON_AddStringToObject(object, "title" , user_todo[i].title);
            cJSON_AddStringToObject(object, "description" , user_todo[i].description);
            cJSON_AddBoolToObject(object, "isdone" , user_todo[i].isdone ? true : false );
            cJSON_AddNumberToObject(object, "userId", user_todo[i].userid);

            cJSON_AddItemToArray(root, object);
        }
    }

    printf("The Todo Are : %s\n", cJSON_Print(root));

    return cJSON_Print(root);
    return 0;
}

int update_todo(char *request_body, Todo *user_todo, int *index) {
    cJSON *json = cJSON_Parse(request_body);
    if(!json){
        return -1;
    }
    cJSON *title = cJSON_GetObjectItem(json, "title");
    cJSON *description = cJSON_GetObjectItem(json, "description");
    cJSON *isdone = cJSON_GetObjectItem(json, "isdone");
    cJSON *userid = cJSON_GetObjectItem(json, "userid");
    if(!title && !description && !isdone && !userid){
        printf("Require More Argumnet In Body");
        return -1;
    }

    for(int i = 0; i < *index; i++){
        if(user_todo[i].userid == userid->valueint){
            strcpy(user_todo[i].title , title->valuestring);
            strcpy(user_todo[i].description , description->valuestring);
            if(strcmp(isdone->valuestring , "true")){
                user_todo[i].isdone = true;   
            } else {
                user_todo[i].isdone = false;
            }
        }
    }
    return 0;
}

int delete_todo(char *request_body, Todo *user_todo, int *index) {
    cJSON *json = cJSON_Parse(request_body);
    if(!json){
        return -1;
    }
    cJSON *userid = cJSON_GetObjectItem(json, "userid");
    if(!userid){
        printf("Require UserId In Body");
        return -1;
    }
    for(int i = 0; i < *index; i++){
        if(user_todo[i].userid == userid->valueint){
            user_todo[i].id = 0;
            strcpy(user_todo[i].title , "");
            strcpy(user_todo[i].description , "");
            user_todo[i].isdone = false;
        }
    }
    return 0;
}