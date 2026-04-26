#include <stdio.h>
#include <string.h>
#include "server.h"
#include "client.h"
#include "parse.h"
#include "route.h"
#include "utils.h"
#include "response.h"

void handle_route (client_info_t *client_state) {
    if (client_state == NULL) return;
    char *method = client_state->request.method;
    if (strcmp(method, "GET") == 0) {
        int get_result = handle_get_route(client_state);
        if (get_result == -1)
        {
            printf("Error While Handling The GET Route\n");
            return;
        }
    }
    else if (strcmp(method, "POST") == 0) {
        int post_result = handle_post_route(client_state);
        if (post_result == -1) {
            printf("Error While Handling The POST Route\n");
            return;
        }
    }
    else if (strcmp(method, "PUT") == 0) {
        int put_result = handle_put_route(client_state);
        if (put_result == -1) {
            printf("Error While Handling The PUT Route\n");
            return;
        }
    }
    else if (strcmp(method, "DELETE") == 0) {
        int delete_result = handle_delete_route(client_state);
        if (delete_result == -1) {
            printf("Error While Handling The DELETE Route\n");
            return;
        }
    }
    else {
        printf("Invalid Method\n");
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

    handle_route(client_state);
}