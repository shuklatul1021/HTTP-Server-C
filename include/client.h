#ifndef CLIENT_INFO
#define CLIENT_INFO

typedef enum
{
    CONNECTED,
    DISCONNECTED,
    NEW_CONNECTION,
    CONNECTION_FAIL
} client_state_t;

typedef struct
{
    int client_fd;
    char client_data[1040];
    client_state_t client_state;
} client_info_t;

int handle_client (int client_fd);

#endif