#ifndef PARSE_H
#define PARSE_H

#include "client.h"

int parse_http_request(const char *request_data, int data_len, http_request_t *request);


#endif