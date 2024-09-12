#include "Http_parser.h"

int Http_parser::on_message_begin(http_parser* parser)
{
    return ((Http_parser*)(parser->data))->on_message_begin_callback();
}

int Http_parser::on_url(http_parser* parser, const char *at, size_t length)
{
    return ((Http_parser*)(parser->data))->on_url_callback(at, length);
}

int Http_parser::on_status(http_parser* parser, const char *at, size_t length)
{
    return ((Http_parser*)(parser->data))->on_url_callback(at, length);
}

int Http_parser::on_header_field(http_parser* parser, const char *at, size_t length)
{
    return ((Http_parser*)(parser->data))->on_header_field_callback(at, length);
}

int Http_parser::on_header_value(http_parser* parser, const char *at, size_t length)
{
    return ((Http_parser*)(parser->data))->on_header_value(at, length);
}

int Http_parser::on_headers_complete(http_parser* parser)
{
    return ((Http_parser*)(parser->data))->on_headers_complete();
}

int Http_parser::on_body(http_parser* parser, const char *at, size_t length)
{
    return ((Http_parser*)(parser->data))->on_body_callback(at, length);
}

int Http_parser::on_message_complete(http_parser* parser)
{
    return ((Http_parser*)(parser->data))->on_message_complete();
}

Http_parser::Http_parser(const Http_parser& that)
{
    memcpy(&m_parser, &that.m_parser, sizeof(http_parser));
    m_parser.data = this;
    memcpy(&m_parser_setting, &that.m_parser_setting, sizeof(http_parser_settings));

    m_url = that.m_url;
    m_status = that.m_status;
    m_header_field = that.m_header_field;
    m_header = that.m_header;
    m_body = that.m_body;
}

Http_parser& Http_parser::operator= (const Http_parser& that)
{
    memcpy(&m_parser, &that.m_parser, sizeof(http_parser));
    m_parser.data = this;
    memcpy(&m_parser_setting, &that.m_parser_setting, sizeof(http_parser_settings));

    m_url = that.m_url;
    m_status = that.m_status;
    m_header_field = that.m_header_field;
    m_header = that.m_header;
    m_body = that.m_body;
    
    return *this;
}

size_t Http_parser::parser_execute(const char* str, size_t str_len)
{
    m_parser_complete = false;
    size_t ret = http_parser_execute(&m_parser, &m_parser_setting, str, str_len);
    if(m_parser_complete == false)
    {
        m_parser.http_errno = 0x7f;
        return 0;
    }
    return ret;
}


