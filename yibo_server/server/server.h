#pragma once

#include "bussiness.h"
#include "function.h"
#include <thread>
#include <atomic>
#include <sys/types.h>
#include <sys/wait.h>

struct server
{
    //首先这个 server 需要能够单独 开启一个线程、还要能够单独开启一个进程
    server()
        : m_serv_accept_stop_flag(false)
    {
        //IP地址 与 port 初始化
        m_bussiness = new client_proc_helper(&m_serv_proc_helper);
        
    }

    ~server()
    {        
        //accept 线程结束
        m_serv_accept_stop_flag.store(true);
        if(m_serv_accept_thrd.joinable())
        {
            m_serv_accept_thrd.join();
        }
        else{ std::cout << "m_serv_accept_thrd joinable failed!" << std::endl;}
        
        //子进程结束
        m_bussiness->m_proc_self_stop_flag.store(true);
        bussiness* bussiness_tmp = m_bussiness;
        delete bussiness_tmp;
        m_bussiness = nullptr;
        wait(NULL);
    }

    //
    void server_client_proc_open()
    {
        m_serv_proc_helper.set_process_func(&client_proc_helper::bussiness_proc_open, m_bussiness);
        m_serv_proc_helper.start_process_func();
    }

    void server_accept_open()
    {
        m_serv_accept_thrd = std::thread(&server::server_accept_thr_func, this);
    }

    //
    void server_accept_thr_func()
    {
        while(!m_serv_accept_stop_flag.load())
        {
            


            //TODO: epoll
        }
    }

   
    //TODO: ip socket
    
    //
    process_helper m_serv_proc_helper;

    //业务类
    client_proc_helper* m_bussiness;

    //thread_1
    std::atomic<bool> m_serv_accept_stop_flag;
    std::thread m_serv_accept_thrd;
};