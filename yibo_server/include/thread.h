#pragma once

#include <iostream>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include "function_helper.h"
#include <thread>

//线程功能包括 
/*
  开始（start）
  暂停 (pause)
  终止 (stop)
*/

/*
  std::thread
*/
class Tthread{
public:
    Tthread() :
    m_stop(false), m_pause(false){}

    ~Tthread()
    {
        stop();
        if(m_thread.joinable())
        {
            std::cout << "join : tid:" << std::this_thread::get_id() << std::endl;
            m_thread.join();
            // std::cout << "join : tid:" << std::this_thread::get_id() << std::endl;
        }
    }
    
    template<typename function, typename... Args>
    Tthread(function&& func, Args&&... args)
        : m_binder(std::bind(std::forward<function>(func), std::forward<Args>(args)...)){}

    template<typename function, typename... Args>
    void reset_func(function&& func, Args&&... args)
    {
        m_binder = std::bind(std::forward<function>(func), std::forward<Args>(args)...);
    }

    void start()
    {
        m_thread = std::thread(&Tthread::run, this);
    }

    //暂停
    void pause()
    {
        if(!m_pause.load())
        {
            m_pause.store(true);
        }
        m_lock.notify_one();
    }

    //停止
    void stop()
    {
        if(!m_stop.load())
        {
            m_stop.store(true);
        }

        m_lock.notify_one();
    }

private:
    void run()
    {
std::cout << "run enter!\r\n";
        while(!m_stop.load())
        {
std::cout << "while enter!\r\n";
            {
                std::unique_lock<std::mutex> lock(m_mutex);
                m_lock.wait(lock, [this](){ return this->m_stop.load() || !this->m_pause.load(); });
                if(m_stop.load())
                {
                    std::cout << "m_stop : " << m_stop << std::endl;
                    return;
                }
                std::cout << "m_stop : " << m_stop << std::endl;
            }

            if(m_binder)
            {
std::cout << "m_binder enter\r\n";
                m_binder();
std::cout << "m_binder end\r\n";
            }
            // std::cout << "m_stop : " << m_stop << std::endl;
        }
        std::cout << "run end!\r\n";
    }

    std::function<int(void)> m_binder;
    std::thread m_thread;

    std::atomic<bool> m_stop  { false };    
    std::atomic<bool> m_pause { false };

    std::mutex m_mutex;
    std::condition_variable m_lock;
};