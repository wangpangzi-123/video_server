#include "url_parser.h"

Url_parser::Url_parser(std::string url)
{
    int parser_index = 0;
    //解析协议
    int protocal_end_index = url.find("://", 0);
    m_protocol = url.substr();

};

int Url_parser::parser_execute(std::string url)
{
    int parser_index = 0;
    //解析协议
    int protocal_end_index = url.find("://", 0);
    if(protocal_end_index == -1){ 
std::cout << "protocol not exisied\r\n";    
    return -1; }
    m_protocol = url.substr(parser_index, protocal_end_index);
std::cout << "m_protocol : " << m_protocol << std::endl;
    
    //解析域名 和 端口

    // 协议 + ://(3)
    parser_index = protocal_end_index + 3;
    int address_end = url.find("/", parser_index);
    if(address_end == -1){ return -2; }
    m_host = url.substr(parser_index, address_end);
    if(int port_begin_index = m_host.find(':', 0) != -1)
    {
        m_port = m_host.substr(port_begin_index, m_host.size() - 1);
        m_host = m_host.substr(0, port_begin_index);
    }
std::cout << "m_host = " << m_host << std::endl;
std::cout << "m_port = " << m_port << std::endl;
    return 0;
}

