#pragma once
#include "http_parser.h"
#include <iostream>
#include <string>

struct Http_parser
{
    Http_parser()
    {
        m_parser.data = this;

        http_parser_init(&m_parser, HTTP_REQUEST);
        
        m_parser_setting.on_message_begin       = on_message_begin;
        m_parser_setting.on_url                 = on_url;
        m_parser_setting.on_status              = on_status;
        m_parser_setting.on_header_field        = on_header_field;
        m_parser_setting.on_header_value        = on_header_value;
        m_parser_setting.on_headers_complete    = on_headers_complete;
        m_parser_setting.on_body                = on_body;
        m_parser_setting.on_message_complete    = on_message_complete;

        
    }

    ~Http_parser();
    Http_parser(const Http_parser& that);
    Http_parser& operator= (const Http_parser& that);

    http_parser m_parser;
    http_parser_settings m_parser_setting;

    //http
    std::string m_body;

    //static callback :
    static int on_message_begin(http_parser* parser);
    static int on_url(http_parser*, const char *at, size_t length);
    static int on_status(http_parser*, const char *at, size_t length);
    static int on_header_field(http_parser*, const char *at, size_t length);
    static int on_header_value(http_parser*, const char *at, size_t length);
    static int on_headers_complete(http_parser* parser);
    static int on_body(http_parser*, const char *at, size_t length);
    static int on_message_complete(http_parser* parser);
    // static int on_chunk_header(http_parser* parser);
    // static int on_chunk_complete(http_parser* parser);

    int on_message_begin_callback(void)
    {
        return 0;
    }

    int on_url_callback(const char *at, size_t length)
    {
        return 0;
    }

    int on_status_callback(const char *at, size_t length)
    {

    }

    int on_header_field_callback(const char *at, size_t length)
    {

    }

    int on_header_value(const char *at, size_t length)
    {

    }

    int on_headers_complete()
    {
        return 0;
    }

    int on_body_callback(const char *at, size_t length)
    {
        m_body = std::string(at, length);
        return 0;
    }

    int on_message_complete(void)
    {
        return 0;
    }

    

};