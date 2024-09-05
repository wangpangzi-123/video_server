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
        : m_serv_accept_stop_flag(false),
          m_sem_helper_begin_end("sem_begin_end"),
          m_sem_helper_end_finish("sem_end_finish")
    {
    }

    ~server()
    {
        //accept 线程结束
        m_serv_accept_stop_flag.store(true);
        if(m_serv_accept_thrd.joinable())
        {
            m_serv_accept_thrd.join();
// std::cout << "server accept thr end!\r\n";
        }
        else{ std::cout << "m_serv_accept_thrd joinable failed!" << std::endl;}
        
        //子进程结束
        // if(m_bussiness != nullptr)
        // {
            // m_serv_proc_helper.send_msg(m_serv_proc_helper.pipes[0], "e");
            // close(m_serv_proc_helper.pipes[0]);
// sem_post(sem);
            // m_bussiness->m_proc_self_stop_flag.store(true);
std::cout << "mmmmmmmmmm\r\n";
            m_sem_helper_begin_end.sem_helper_post();
            m_sem_helper_end_finish.sem_helper_wait();

            // bussiness* bussiness_tmp = m_bussiness;
// std::cout << "no delete!\r\n";
            // delete m_bussiness;
            // m_bussiness = nullptr;
            wait(NULL);
        // }
// sem_close(sem);
// sem_unlink(sem_name);
    }

    //
    void server_client_proc_open()
    {
        
        m_serv_proc_helper.set_process_func(&client_proc_helper::bussiness_proc_open, &m_bussiness, 
                                            (sem_t* )m_sem_helper_begin_end, (sem_t* )m_sem_helper_end_finish);

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

   
    //子进程 信号量

    sem_helper m_sem_helper_begin_end;
    sem_helper m_sem_helper_end_finish;
    //TODO: ip socket
    
    //
    process_helper m_serv_proc_helper;

    //业务类
    client_proc_helper m_bussiness;

    //thread_1
    std::atomic<bool> m_serv_accept_stop_flag;
    std::thread m_serv_accept_thrd;
};