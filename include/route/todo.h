#ifndef TODO_ROUTE
#define TODO_ROUTE
#include <stdbool.h>

typedef struct {
    int id;
    char title[256];
    char description[256];
    bool isdone;
    int userid;
    int index;
} Todo;


int add_todo(char *request_body);
int update_todo(char *request_body);
int delete_todo(char *request_body);


#endif