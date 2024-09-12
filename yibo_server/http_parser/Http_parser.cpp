#include "Http_parser.h"

static int on_message_begin(http_parser* parser)
{
    return ((Http_parser*)(parser->data))->on_message_begin_callback();
}

static int on_url(http_parser* parser, const char *at, size_t length)
{
    return ((Http_parser*)(parser->data))->on_url_callback(at, length);
}

static int on_status(http_parser* parser, const char *at, size_t length)
{
    return ((Http_parser*)(parser->data))->on_url_callback(at, length);
}

static int on_header_field(http_parser* parser, const char *at, size_t length)
{
    return 0;
}

static int on_header_value(http_parser* parser, const char *at, size_t length)
{
    return 0;
}

static int on_headers_complete(http_parser* parser)
{
    return 0;
}

static int on_body(http_parser* parser, const char *at, size_t length)
{
    return 0;
}

static int on_message_complete(http_parser* parser)
{
    return 0;
}

static int on_chunk_header(http_parser* parser)
{
return 0;
}

static int on_chunk_complete(http_parser* parser)
{
    return 0;
}