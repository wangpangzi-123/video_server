#pragma once
#include "function.h"
#include <thread>
#include <atomic>

struct bussiness
{
    bussiness()
    : m_proc_helper(nullptr),
      m_proc_self_stop_flag(false){}

    virtual ~bussiness() = 0;
    // virtual int bussiness_proc(process_helper* helper) = 0;
    
    std::atomic<bool> m_proc_self_stop_flag;
    process_helper* m_proc_helper;
};

struct client_proc_helper : public bussiness
{
    client_proc_helper()
        : m_thr_add_client_stop_flag(false),
          m_thr_epoll_solver_stop_flag(false){}
    
    client_proc_helper(process_helper* proc_helper)
        : m_thr_add_client_stop_flag(false),
          m_thr_epoll_solver_stop_flag(false){}


    virtual ~client_proc_helper() override
    {
        m_thr_add_client_stop_flag.store(true);
        m_thr_epoll_solver_stop_flag.store(true);
        if(m_bussiness_add_client.joinable())
        {
            m_bussiness_add_client.join();
        }
        else{std::cout << "m_bussiness_add_client join failed!\r\n";}
    
        if(m_bussiness_epoll_solver.joinable())
        {
            m_bussiness_epoll_solver.join();
        }
        else{std::cout << "m_bussiness_epoll_solver join failed!\r\n";}
    }

    int bussiness_proc_open()
    {
        m_bussiness_add_client = std::thread(&client_proc_helper::thr_add_client_func, this);
        m_bussiness_epoll_solver = std::thread(&client_proc_helper::thr_epoll_solver_func, this);
        
        while(!m_proc_self_stop_flag.load())
        {

        }
        return 0;
    }

    void thr_add_client_func(void)
    {
        while(!m_thr_add_client_stop_flag.load())
        {
            //1、接收
            //int client_accpet_socket = m_proc_helper->recv_fd(m_proc_helper->pipes[1]);
            //2、添加 link
        }
    }

    void thr_epoll_solver_func(void)
    {
        while(!m_thr_epoll_solver_stop_flag.load())
        {
            //3、epoll 处理
        }
    }

    //thread_1
    std::atomic<bool> m_thr_add_client_stop_flag;
    std::thread m_bussiness_add_client;

    //thread_2
    std::atomic<bool> m_thr_epoll_solver_stop_flag;
    std::thread m_bussiness_epoll_solver;

    //thread_pool
    //线程池-> 处理任务
};




