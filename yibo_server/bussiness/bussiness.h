#pragma once
#include "function.h"
#include <thread>
#include <atomic>
#include <mutex>
#include <semaphore.h>
struct bussiness
{
    bussiness()
    : m_proc_helper(nullptr),
      m_proc_self_stop_flag(false){}

    virtual ~bussiness(){};
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
        {
            std::lock_guard<std::mutex> lock(mtx);
            m_thr_add_client_stop_flag = true;
            m_thr_epoll_solver_stop_flag = true;
        }


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

    int bussiness_proc_open(process_helper* proc_helper, sem_t* m_sem)
    {
        m_bussiness_add_client = std::thread(&client_proc_helper::thr_add_client_func, this);
        m_bussiness_epoll_solver = std::thread(&client_proc_helper::thr_epoll_solver_func, this);
        
//         while(!m_proc_self_stop_flag.load())
//         {
//             char buffer[1024] = {0};
//             proc_helper->recv_msg(proc_helper->pipes[1], buffer, sizeof(buffer));
// std::cout << "proc recv buffer : " << buffer << std::endl;
//             if(buffer[0] == 'e')
//             {
// std::cout << "ready exit!\r\n";
//                 break;
//             }

//         }

        sem_wait(m_sem);

std::cout << "bussiness_proc_end!\r\n";
            m_thr_add_client_stop_flag = true;
            m_thr_epoll_solver_stop_flag = true;
std::cout << "-------------------------------pro\r\n";
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

        return 0;
    }

    void thr_add_client_func(void)
    {
        while(!m_thr_add_client_stop_flag)
        {
            //1、接收
            //int client_accpet_socket = m_proc_helper->recv_fd(m_proc_helper->pipes[1]);
            //2、添加 link
            sleep(1);
// std::cout << "add flag " << m_thr_add_client_stop_flag << std::endl;
        }
        std::cout << "thr_client_func end!\r\n";
    }

    void thr_epoll_solver_func(void)
    {

        while(!m_thr_epoll_solver_stop_flag)
        {
            //3、epoll 处理
            sleep(1);
// std::cout << "epoll flag " << m_thr_epoll_solver_stop_flag << std::endl;
        }
        std::cout << "thr_epoll_func end!\r\n";
    }



    std::mutex mtx;

    //thread_1
    std::atomic<bool> m_thr_add_client_stop_flag;
    std::thread m_bussiness_add_client;

    //thread_2
    std::atomic<bool> m_thr_epoll_solver_stop_flag;
    std::thread m_bussiness_epoll_solver;

    //thread_pool
    //线程池-> 处理任务
};




