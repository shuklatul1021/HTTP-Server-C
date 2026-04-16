#ifndef SERVER_INFO
#define SERVER_INFO

typedef enum {
    SERVER_ACTIVE,
    SERVER_INACTIVE
}server_state_t;

typedef struct
{
    server_state_t client_state;
}server_info_t;

#endif