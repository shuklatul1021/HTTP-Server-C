#include <stdio.h>
#include <string.h>
#include "server.h"
#include "client.h"
#include "parse.h"
#include "utils.h"
#include "response.h"

void handle_route(client_info_t *client_state)
{
    if (client_state == NULL) return;
    const char *method = client_state->request.method;
    if (strcmp(method , "GET")) {
        int get_result = handle_get_route(client_info_t *client_state);
        if(get_result == -1){
            printf("Error While Handling The GET Route\n");
            return;
        }
    } else if(strcmp(method , "POST")) {  
        int post_result = handle_post_route(client_info_t *client_state);
        if(post_result == -1){
            printf("Error While Handling The POST Route\n");
            return;
        }
    }
    else if (strcmp(method , "PUT")) {
        int put_result = handle_put_route(client_info_t *client_state);
        if (put_result == -1) {
            printf("Error While Handling The PUT Route\n");
            return;
        }
    }
    else if (strcmp(method , "DELETE")) {
        int delete_result = handle_delete_route(client_info_t *client_state);
        if (delete_result == -1) {
            printf("Error While Handling The DELETE Route\n");
            return;
        }
    }else {
        printf("Invalid Method\n")
        return;
    }
}

void handle_client(int client_fd, char *client_data, int data_len, client_info_t *client_state)
{
    printf("Client %d says: %.*s\n", client_fd, data_len, client_data);
    printf("This is The Client FD : %d\n", client_state->client_fd);
    int parse_result = parse_http_request(client_data, data_len, &client_state->request);
    if (parse_result == -1)
    {
        printf("Error While Parsing The String\n");
        return;
    }

    printf("Parsed Request:\n");
    printf("Method: %s\n", client_state->request.method);
    printf("Path: %s\n", client_state->request.path);
    printf("Version: %s\n", client_state->request.version);
    printf("Headers:\n");
    for (int i = 0; i < client_state->request.header_count; i++)
    {
        printf("  %s: %s\n", client_state->request.headers[i][0], client_state->request.headers[i][1]);
    }
    printf("Body: %s\n", client_state->request.body);


    handle_route(&client_state);
}