#pragma once
#include "function.h"
#include <thread>
#include <atomic>
#include <mutex>
#include <semaphore.h>
#include <memory>
#include <map>

// #include "server.h"
#include "epoll_func.h"
#include "socket.h"
#include "thread_pool.h"

void waiting_thread();
void notifying_thread();

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

    std::condition_variable cv_lock_;
    std::mutex cv_mutex_;
    std::atomic<bool> cv_wake_ = false;
    std::atomic<bool> cv_bool_ = false;
    std::thread m_test_thr;

    void bussiness_proc(socket_inet* sock)
    {
std::cout << __LINE__ << "enter bussiness_proc\r\n";
        bytes_buffer buffer(1024);
        // bytes_buffer& buf(std::string("23")); 
        sock->recv(buffer);
std::cout << "m thread : " << std::this_thread::get_id() << "  recv buffer : " << buffer << std::endl;
        std::string send_buff = "send: " + buffer;
        // send(socket, send_buff.data(), send_buff.size(), 0);
        sock->send(send_buff.data());

// std::cout << "hehlllljlj\r\n";
    }

    void test_thr_while()
    {
        while(!cv_bool_.load())
        {
std::cout << "test_thr_wake begin! \r\n";
            std::unique_lock<std::mutex> uni_que(cv_mutex_);
            cv_lock_.wait(uni_que, [this](){
std::cout << "line : " << __LINE__ << std::endl;
                return cv_wake_.load();
            });
            
            cv_wake_.store(false);
std::cout << __LINE__ << " " << "test_thr_wake !\r\n";
        }
    }

    // void waiting_thread();
    // void notifying_thread();

    client_proc_helper()
        : m_thr_add_client_stop_flag(false),
          m_thr_epoll_solver_stop_flag(false)
    {
        CHECK_ERROR(m_solver_epoll.create); 
    }
    

    virtual ~client_proc_helper() override {}

    void client_stop()
    {
        //test
        cv_bool_ = true;
        if(m_test_thr.joinable())
        {
            m_test_thr.join();
        }

// std::cout << "client_ stop\r\n";

        m_thr_add_client_stop_flag = true;
        m_thr_epoll_solver_stop_flag = true;

        if(m_bussiness_add_client.joinable())
        {
            m_bussiness_add_client.join();
        }
        else{std::cout << "line: "<< __LINE__  << " m_bussiness_add_client join failed!\r\n";}
    
        if(m_bussiness_epoll_solver.joinable())
        {
            m_bussiness_epoll_solver.join();
        }
        else{std::cout << "line: "<< __LINE__  << " m_bussiness_epoll_solver join failed!\r\n";}
    }

    int bussiness_proc_open(process_helper* process_helper, sem_t* sem_begin_end_, sem_t* sem_end_finish_)
    {
        
        // std::thread t1(&client_proc_helper::waiting_thread, this);
// std::cout << "1111\r\n";
        // std::thread t2(notifying_thread);

        // t2.join();
        
        
        m_proc_helper = process_helper;
        m_bussiness_add_client = std::thread(&client_proc_helper::thr_add_client_func, this);
        m_bussiness_epoll_solver = std::thread(&client_proc_helper::thr_epoll_solver_func, this);


        // t1.join();

        
        sem_wait(sem_begin_end_);

        client_stop();

        sem_post(sem_end_finish_);

        return 0;
    }

    void thr_add_client_func(void)
    {
        m_proc_helper->set_read_isblock(false);
        while(!m_thr_add_client_stop_flag)
        {
            //参照 server 创建 inet_client_socket
            //往epoll线程添加
            int recv_client_fd = m_proc_helper->recv_fd();
            if(recv_client_fd > 0)
            {
                clients[recv_client_fd] = std::make_unique<socket_inet>(recv_client_fd);
                clients[recv_client_fd]->m_inet_param.m_attr |= (SOCK_IS_IP_);

                // epoll event
                int recv_accept_epoll_event = EPOLLIN | EPOLLET;
                // struct epoll
                epoll_data_ recv_accept_epoll_data;
                recv_accept_epoll_data.m_data.fd = recv_client_fd;
                // recv_accept_epoll_data.m_data.ptr = clients[recv_client_fd].get();
                int rtn = m_solver_epoll.add_event(recv_client_fd, recv_accept_epoll_data, recv_accept_epoll_event);
            
            }
            else if(recv_client_fd < 0)  //接收错误！！！
            {
std::cout << __FILE__  <<  " : " << __LINE__ << " error !!!! \r\n";
            }
        }
        std::cout << "thr_client_func end!\r\n";
    }

    void thr_epoll_solver_func(void)
    {
        ssize_t epoll_rtn;
        // m_thr_pool_test.start();
        thread_pool::instance().start();
// std::cout << "enter thr_epoll_solver_func\r\n";
        while(!m_thr_epoll_solver_stop_flag)
        {
            //3、epoll 处理
            epoll_rtn = m_solver_epoll.wait_event(10);
            for(int i = 0; i < epoll_rtn; i++)
            {
                if (m_solver_epoll.epoll_events[i].events & EPOLLERR)
                {
                    std::cout << "events & EPOLLERR = 1" << std::endl;
                    break;
                }
                else if (m_solver_epoll.epoll_events[i].events & EPOLLIN)
                {
                    int solver_fd = m_solver_epoll.epoll_events[i].data.fd;
                    if(auto it = clients.find(solver_fd) != clients.end())
                    {

                        // thread_pool::instance().call_wake();

                        // char buffer[1024] = {0};
                        // read(clients[solver_fd]->m_inet_socket, buffer, sizeof(buffer));
// std::cout << __LINE__ << " " << "recv buffer : " << buffer << std::endl;
                        std::future<void> rtn(thread_pool::instance().submit(&client_proc_helper::bussiness_proc, this, clients[solver_fd].get()));
                        // rtn.get();
                        // m_thr_pool_test.wake();
                    }
                }
            }
        }
        thread_pool::instance().stop();
        std::cout << "thr_epoll_func end!\r\n";
    }


    //map   std::make_unique<socket_inet>
    std::map<int, std::unique_ptr<socket_inet>> clients;

    //epoll
    epoll_helper m_solver_epoll;

    //thread_1
    std::atomic<bool> m_thr_add_client_stop_flag;
    std::thread m_bussiness_add_client;

    //thread_2
    std::atomic<bool> m_thr_epoll_solver_stop_flag;
    std::thread m_bussiness_epoll_solver;




    //thread_pool
    //线程池-> 处理任务
    // thread_pool_test m_thr_pool_test;
    // thread_pool m_bussiness_pool;
};




