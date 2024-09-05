#pragma once

#include "bussiness.h"
#include "function.h"
#include <thread>
#include <atomic>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <fcntl.h>

struct server
{
    //首先这个 server 需要能够单独 开启一个线程、还要能够单独开启一个进程
    server()
        : m_serv_accept_stop_flag(false),
          m_bussiness(nullptr)
    {
        //IP地址 与 port 初始化
            sem_name = "/my_semaphore";
            sem = sem_open(sem_name, O_CREAT | O_EXCL, 0644, 0);  // 初始化为0
            if (sem == SEM_FAILED) {
            if (errno == EEXIST) {
            // 信号量已经存在
            std::cout << "Semaphore already exists.\n";
            // 可以选择打开现有信号量
            sem = sem_open(sem_name, 0);
            if (sem == SEM_FAILED) {
                perror("sem_open");
                
                }
            } 
        }
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
        if(m_bussiness != nullptr)
        {
            // m_serv_proc_helper.send_msg(m_serv_proc_helper.pipes[0], "e");
            // close(m_serv_proc_helper.pipes[0]);

            sem_post(sem);
            // m_bussiness->m_proc_self_stop_flag.store(true);
            bussiness* bussiness_tmp = m_bussiness;
// std::cout << "no delete!\r\n";
            delete m_bussiness;
            m_bussiness = nullptr;
            wait(NULL);
        }

        sem_close(sem);
        sem_unlink(sem_name);
    }

    //
    void server_client_proc_open()
    {
        m_bussiness = new client_proc_helper(&m_serv_proc_helper);
        m_serv_proc_helper.set_process_func(&client_proc_helper::bussiness_proc_open, m_bussiness, &m_serv_proc_helper, sem);
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

   
    sem_t *sem;
    const char *sem_name;
    //TODO: ip socket
    
    //
    process_helper m_serv_proc_helper;

    //业务类
    client_proc_helper* m_bussiness;

    //thread_1
    std::atomic<bool> m_serv_accept_stop_flag;
    std::thread m_serv_accept_thrd;
};