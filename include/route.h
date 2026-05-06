#ifndef ROUTE_H
#define ROUTE_H
#include "client.h"
#include "route/todo.h"
#include "route/user.h"

int handle_get_route(client_info_t *client_state, User *users , Todo *todos, int *user_index, int *todo_index);
int handle_post_route(client_info_t *client_state, User *users , Todo *todos, int *user_index, int *todo_index);
int handle_put_route(client_info_t *client_state, User *users , Todo *todos, int *user_index, int *todo_index);
int handle_delete_route(client_info_t *client_state, User *users , Todo *todos, int *user_index, int *todo_index);

#endif