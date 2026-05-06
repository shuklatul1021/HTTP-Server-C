#ifndef USER_ROUTE
#define USER_ROUTE

typedef struct  
{
    int id;
    char email[256];
    char password[256];
    int index;
} User;

int register_user(char *request_body, User *users, int *user_index);
int login_user(char *request_body, User *users, int *user_index);
int get_user(int user_id, User *users, int *user_index);

#endif