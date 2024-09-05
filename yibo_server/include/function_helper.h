#pragma once
#include <iostream>
#include <functional>


class TFunction
{
    public:
        TFunction(){}

        template<typename function_, typename... Args>
        TFunction(function_&& func, Args&&... args)
            : m_binder(std::bind(std::forward<function_>(func), std::forward<Args>(args)...)){}
        
        virtual ~TFunction() {}

        int operator()()
        { 
            if(m_binder)
            { 
                m_binder();
            }
            else
            { 
                return -1;
            }
        }

    private:
        std::function<int(void)> m_binder;
};