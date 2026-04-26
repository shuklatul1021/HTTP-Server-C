#ifndef CLIENT_INFO
#define CLIENT_INFO

typedef enum
{
    CONNECTED,
    DISCONNECTED,
    NEW_CONNECTION,
    CONNECTION_FAIL
} client_state_t;

typedef struct {
    char method[10];
    char path[256];
    char version[16];
    char headers[20][2][256]; // key-value
    int header_count;
    char body[1024];
} http_request_t;

typedef struct
{
    int client_fd;
    char client_data[1040];
    client_state_t client_state;
    http_request_t request;
} client_info_t;



void handle_client(int client_fd, char *client_data, int data_len, client_info_t *client_state);
void handle_route(client_info_t *client_state);

#endif