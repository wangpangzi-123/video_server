#pragma once
#include "http_parser.h"
#include <string>
#include <iostream>
#include <unordered_map>

struct Url_parser
{
    Url_parser(const std::string& url){ m_url = url; }
    Url_parser(const Url_parser& that) 
    {
        m_url = that.m_url;
        m_protocol = that.m_protocol;
        m_host = that.m_host;
        m_port = that.m_port;
        m_uri = that.m_uri;
        m_values = that.m_values;
    }

    Url_parser& operator= (const Url_parser& that)
    {
        if(&that != this)
        {
            m_url = that.m_url;
            m_protocol = that.m_protocol;
            m_host = that.m_host;
            m_port = that.m_port;
            m_uri = that.m_uri;
            m_values = that.m_values;
        }
        return *this;
    }
    
    ~Url_parser() {}
    
    int parser_execute();
    std::string operator[](const std::string& name)const;
	std::string Protocol()const { return m_protocol; }
	std::string Host()const { return m_host; }
	//默认返回80
	int Port()const { return m_port; }
	void SetUrl(const std::string& url);

    std::string m_url;
    std::string m_protocol;
    std::string m_host;
    int m_port;
    std::string m_uri;
    std::unordered_map<std::string, std::string> m_values;
};
