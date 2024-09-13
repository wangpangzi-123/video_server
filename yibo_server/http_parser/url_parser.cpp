#include "url_parser.h"

int Url_parser::parser_execute()
{
    int parser_index = 0;
    //解析协议
    int protocal_end_index = m_url.find("://", 0);
    if(protocal_end_index == -1){ 
      return -1; 
    }
    m_protocol = m_url.substr(parser_index, protocal_end_index);
    //解析域名 和 端口

    // 协议 + ://(3)
    parser_index = protocal_end_index + 3;
    int address_end = m_url.find('/', parser_index);
    if(address_end == -1){ return -2; }

    int uri_end = m_url.find('?', parser_index);
    if(uri_end == -1) { return -3; }

    m_uri = m_url.substr(address_end, uri_end - address_end);
    m_host = m_url.substr(parser_index, address_end - parser_index);
    if((address_end = m_host.find(':', 0)) != -1)
    {
        m_port = atoi(m_host.substr(address_end + 1, m_host.size() - address_end).c_str());
        m_host = m_host.substr(0, address_end);
    }

    parser_index = uri_end + 1;
    int map_value_end = 0;
    int map_equal_end = 0;

    //先找 = , 再找 &
    while((map_equal_end = m_url.find('=', parser_index)) != -1)
    {
        map_value_end = m_url.find('&', parser_index);
        if(map_value_end != -1)
        {
          if(map_value_end > map_equal_end)
          {
            m_values[m_url.substr(parser_index, map_equal_end - parser_index)] 
                   = m_url.substr(map_equal_end + 1, map_value_end - (map_equal_end + 1));
          }
        }
        else
        {
          map_value_end = m_url.size();
          m_values[m_url.substr(parser_index, map_equal_end - parser_index)] 
                 = m_url.substr(map_equal_end + 1, map_value_end - (map_equal_end + 1));
          break;
        }
        parser_index = map_value_end + 1;
    }

    return 0;
}

void Url_parser::SetUrl(const std::string& url)
{
    m_url = url;
    m_values.clear();
    m_uri.clear();
    m_port = 0;
    m_host.clear();
    m_protocol.clear();
}

std::string Url_parser::operator[](const std::string& name)const
{
    auto i = m_values.find(name);
    if(i != m_values.end()){ return i->second; }
    return {};
}