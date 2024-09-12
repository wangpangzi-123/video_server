#pragma once
#include <iostream>
#include <string>
#include <string.h>
#include <map>
#include "http_parser.h"

struct Http_parser
{
    explicit Http_parser()
    {
        memset(&m_parser, 0, sizeof(m_parser));
        memset(&m_parser_setting, 0, sizeof(m_parser_setting));

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

        m_parser_setting.on_chunk_header        = 0;
        m_parser_setting.on_chunk_complete      = 0;
    }

    ~Http_parser(){};

    Http_parser(const Http_parser& that);
    Http_parser& operator= (const Http_parser& that);



public:
    size_t parser_execute(const char* str, size_t str_len);
    unsigned method()                   { return m_parser.method; }
    inline std::string url()            { return m_url;   }
    inline std::string status()         { return m_status;}
    inline std::string header_field()   { return m_header_field; }
    inline std::string header_value()   { return m_header[m_header_field]; }
    inline std::string header_value(std::string header_filed)
    {
        if(m_header.find(header_filed) != m_header.end())
        {
            return m_header[header_filed];
        }
        return {};
    }

    inline std::string body()           { return m_body; } 
    unsigned Errno() const { return m_parser.http_errno; }

protected:
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
        m_url = std::string(at, length);
        return 0;
    }

    int on_status_callback(const char *at, size_t length)
    {
        m_status = std::string(at, length);
        return 0;
    }

    int on_header_field_callback(const char *at, size_t length)
    {
        m_header_field = std::string(at, length);
        return 0;
    }

    int on_header_value(const char *at, size_t length)
    {
        m_header[m_header_field] = std::string(at, length);
        return 0;
    }

    int on_headers_complete(void)
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
        m_parser_complete = true;
        return 0;
    }

private:
    http_parser m_parser;
    http_parser_settings m_parser_setting;

    //http
    bool m_parser_complete = false;
    std::string m_url;
    std::string m_status;
    std::string m_header_field;
    std::map<std::string, std::string> m_header;
    std::string m_body;
};