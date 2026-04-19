#ifndef ROUTE_H
#define ROUTE_H
#include "client.h"

int handle_get_route(client_info_t *client_state);
int handle_post_route(client_info_t *client_state);
int handle_put_route(client_info_t *client_state);
int handle_delete_route(client_info_t *client_state);

#endif