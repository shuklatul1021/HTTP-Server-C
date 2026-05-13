#ifndef TODO_ROUTE
#define TODO_ROUTE
#include <stdbool.h>

#include "route/todo.h"

typedef struct {
    int id;
    char title[256];
    char description[256];
    bool isdone;
    int userid;
    int index;
} Todo;

int add_todo(char *request_body, Todo *user_todo, int *index);
void get_all_todo(Todo *user_todo, int *index);
char *get_user_todo(int user_id, Todo *user_todo, int *index);
int update_todo(char *request_body, Todo *user_todo, int *index);
int delete_todo(char *request_body, Todo *user_todo, int *index);

#endif