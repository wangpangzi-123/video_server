#pragma once
#include "http_parser.h"
#include <string>
#include <iostream>
struct Url_parser
{
    explicit Url_parser(std::string url);
    
    int parser_execute(std::string url);
    


    std::string m_protocol;
    std::string m_host;
    std::string m_port;
};
