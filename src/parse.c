#include <stddef.h>
#include <string.h>

#include "parse.h"

static const char *find_crlf(const char *start, const char *end)
{
    for (const char *p = start; p + 1 < end; ++p)
    {
        if (p[0] == '\r' && p[1] == '\n')
        {
            return p;
        }
    }
    return NULL;
}

static void copy_slice(char *dst, size_t dst_size, const char *start, size_t len)
{
    if (dst_size == 0)
    {
        return;
    }

    if (len >= dst_size)
    {
        len = dst_size - 1;
    }

    memcpy(dst, start, len);
    dst[len] = '\0';
}

static void trim_spaces(const char **start, const char **end)
{
    while (*start < *end && (**start == ' ' || **start == '\t'))
    {
        (*start)++;
    }

    while (*end > *start && ((*(*end - 1) == ' ') || (*(*end - 1) == '\t')))
    {
        (*end)--;
    }
}

int parse_http_request(const char *request_data, int data_len, http_request_t *request)
{
    if (request_data == NULL || request == NULL || data_len <= 0)
    {
        return -1;
    }

    memset(request, 0, sizeof(*request));
    // First Char = Address
    // Ex - 0xdf434dfd
    const char *cursor = request_data;
    // End Address
    // Ex - 0xdf434dgc
    const char *end = request_data + data_len;

    const char *request_line_end = find_crlf(cursor, end);
    if (request_line_end == NULL)
    {
        return -1;
    }

    const char *space_1 = NULL;
    const char *space_2 = NULL;

    for (const char *p = cursor; p < request_line_end; ++p)
    {
        if (*p == ' ')
        {
            if (space_1 == NULL)
            {
                space_1 = p;
            }
            else
            {
                space_2 = p;
                break;
            }
        }
    }

    if (space_1 == NULL || space_2 == NULL || space_1 == cursor || space_2 <= space_1 + 1 || space_2 + 1 >= request_line_end)
    {
        return -1;
    }

    copy_slice(request->method, sizeof(request->method), cursor, (size_t)(space_1 - cursor));
    copy_slice(request->path, sizeof(request->path), space_1 + 1, (size_t)(space_2 - (space_1 + 1)));
    copy_slice(request->version, sizeof(request->version), space_2 + 1, (size_t)(request_line_end - (space_2 + 1)));

    cursor = request_line_end + 2;

    while (cursor < end)
    {
        if (cursor + 1 < end && cursor[0] == '\r' && cursor[1] == '\n')
        {
            cursor += 2;
            break;
        }

        const char *header_line_end = find_crlf(cursor, end);
        if (header_line_end == NULL)
        {
            return -1;
        }

        const char *colon = NULL;
        for (const char *p = cursor; p < header_line_end; ++p)
        {
            if (*p == ':')
            {
                colon = p;
                break;
            }
        }

        if (colon == NULL)
        {
            return -1;
        }

        const char *key_start = cursor;
        const char *key_end = colon;
        const char *value_start = colon + 1;
        const char *value_end = header_line_end;

        trim_spaces(&key_start, &key_end);
        trim_spaces(&value_start, &value_end);

        if (request->header_count < 20 && key_start < key_end)
        {
            copy_slice(request->headers[request->header_count][0], sizeof(request->headers[0][0]), key_start, (size_t)(key_end - key_start));
            copy_slice(request->headers[request->header_count][1], sizeof(request->headers[0][1]), value_start, (size_t)(value_end - value_start));
            request->header_count++;
        }

        cursor = header_line_end + 2;
    }

    if (cursor < end)
    {
        copy_slice(request->body, sizeof(request->body), cursor, (size_t)(end - cursor));
    }

    return 0;
}