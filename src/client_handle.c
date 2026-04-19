#include <stdio.h>

#include "server.h"
#include "client.h"
#include "parse.h"
#include "utils.h"
#include "response.h"

// void handle_route(client_info_t *client_state)
// {
//     // pass
// }

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


    // handle_route(&client_state);
}