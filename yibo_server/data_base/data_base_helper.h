#pragma once
#include <map>
#include <string>
#include <iostream>

using key_value = std::map<std::string, std::string>;

class data_base_helper
{
public:
    data_base_helper(){}
    data_base_helper(const data_base_helper& ) = delete;
    data_base_helper& operator= (const data_base_helper&) = delete;

public:
    data_base_helper
}