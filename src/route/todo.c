#include "route/todo.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "cJSON.h"



Todo user_todo[100];
int index = 0;

int add_todo(char *request_body) {
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
    user_todo[index].id = index + 1;
    strcpy(user_todo[index].title , title->valuestring);
    strcpy(user_todo[index].description , description->valuestring);
    if(strcmp(isdone->valuestring , "true")){
        user_todo[index].isdone = true;   
    } else {
        user_todo[index].isdone = false;
    }
  
    return 0;
}

void get_all_todo(){
    printf("These Details Of All Todo");
    for(int i = 0; i < 100; i++){
        printf("Index %d\n:",i);
        printf("Id: %d\n", user_todo[i].id);
        printf("Title: %s\n", user_todo[i].title);
        printf("Description: %s\n", user_todo[i].description);
        printf("IsBoolen: %d\n", user_todo[i].isdone);
        printf("UserId: %d\n", user_todo[i].userid);
        printf("---------------------------------------");
        
    }
}

void get_all_todo_userid(int user_id){
    printf("These Details Of All Todo For User %d\n:",user_id);
    for(int i = 0; i < 100; i++){
        if(user_todo[i].userid == user_id){
            printf("Index %d\n:",i);
            printf("Id: %d\n", user_todo[i].id);
            printf("Title: %s\n", user_todo[i].title);
            printf("Description: %s\n", user_todo[i].description);
            printf("IsBoolen: %d\n", user_todo[i].isdone);
            printf("UserId: %d\n", user_todo[i].userid);
            printf("---------------------------------------");
        }
    }
}

int update_todo(char *request_body) {
    return 0;
}

int delete_todo(char *request_body) {
    return 0;
}