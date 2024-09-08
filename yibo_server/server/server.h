#pragma once

//self
#include "bussiness.h"
#include "function.h"
#include "epoll_func.h"
#include "check_error.h"

#include <thread>
#include <atomic>
#include <sys/types.h>
#include <sys/wait.h>

#include "socket.h"



struct server
{
    //首先这个 server 需要能够单独 开启一个线程、还要能够单独开启一个进程
    server()
        : m_serv_accept_stop_flag(false),
          m_sem_helper_begin_end("sem_begin_end"),
          m_sem_helper_end_finish("sem_end_finish")
    {
        // m_accept_epoll.create();
        
        //1、epoll create
        CHECK_ERROR(m_accept_epoll.create);
        //2、创建本地 socket 套接字
        
        
        // int attr |= (SOCK_IS_SERVER_ | SOCK_IS_IP_);

        m_server_param.m_attr |= (SOCK_IS_SERVER_);
        // m_server_param.m_attr |= (SOCK_IS_IP_);
        m_server_param.init_local_param("./log/server.sock");

std::cout << m_server_param.m_attr << std::endl;

        m_server_socket.init(m_server_param);

        // socket_param_ x("./log/server.sock", (SOCK_IS_SERVER_ | SOCK_IS_IP_));


    }

    ~server()
    {
        //accept 线程结束
        // m_serv_accept_stop_flag.store(true);
        // if(m_serv_accept_thrd.joinable())
        // {
        //     m_serv_accept_thrd.join();
        // }
        // else{ std::cout << "m_serv_accept_thrd joinable failed!" << std::endl;}
        
        // //子进程结束
        // m_sem_helper_begin_end.sem_helper_post();
        // m_sem_helper_end_finish.sem_helper_wait();

         wait(NULL);
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
        ssize_t epoll_rtn = 0;
        while(!m_serv_accept_stop_flag.load())
        {
            //设置 epoll wait
            epoll_rtn = m_accept_epoll.wait_event(10);
            for(int i = 0; i < epoll_rtn; i++)
            {
                if (m_accept_epoll.epoll_events[i].events & EPOLLERR)
                {
                    std::cout << "events & EPOLLERR = 1" << std::endl;
                    // m_thread.stop();
                    break;
                }
                else if (m_accept_epoll.epoll_events[i].events & EPOLLIN)
                {
                    // if (m_accept_epoll.epoll_events[i].data.ptr == socket_)
                    // {
                    //     socket_base *ptr_client = nullptr;
                    //     int r = socket_->link(&ptr_client);
                    //     printf("%s(%d):[%s]ret=%d \n", __FILE__, __LINE__, __FUNCTION__, r);
                    //     if (r < 0)
                    //         continue;

                    //     r = m_accept_epoll.add_event(*ptr_client, (void *)(ptr_client), EPOLLIN | EPOLLERR);
                    //     printf("%s(%d):[%s]ret=%d \n", __FILE__, __LINE__, __FUNCTION__, r);
                    //     if (r < 0)
                    //     {
                    //         delete ptr_client;
                    //         continue;
                    //     }
                    // }
                }
                std::cout << __LINE__ << " epoll events : " << m_accept_epoll.epoll_events[i].events << std::endl;
            }
        }
    }

   
    //子进程结束 信号量
    sem_helper m_sem_helper_begin_end;
    sem_helper m_sem_helper_end_finish;
    
    //TODO: ip socket
    socket_param_   m_server_param;
    socket_inet    m_server_socket;
    
    //
    process_helper m_serv_proc_helper;

    //业务类
    client_proc_helper m_bussiness;

    //thread_1
    std::atomic<bool> m_serv_accept_stop_flag;
    std::thread m_serv_accept_thrd;

    //epoll
    epoll_helper m_accept_epoll;
};