//
// Created by lintao on 2024/9/9.
//
#pragma once
#include <iostream>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <vector>
#include <functional>
#include <future>
#include <queue>
#include <memory>
#include <atomic>


struct thread_pool_test
{
    std::mutex                  m_thr_pool_mutex;
    std::condition_variable     m_thr_pool_condition_var;
    std::atomic<bool>           m_stop;
    
    //测试用
    std::atomic<bool>           m_wake;
    std::thread                 thr;

    thread_pool_test() : m_stop(false), m_wake(false){}

    ~thread_pool_test()
    {
        stop();
        if(thr.joinable())
        {
            thr.join();
        }
    }

    void stop()
    {
        m_stop = true;
        m_wake = true;
        m_thr_pool_condition_var.notify_one();
    }
    
    void start()
    {

        thr = std::thread([this]()
        {
std::cout << __FILE__ << "  " << "thr start!\r\n";
            while(!m_stop)
            {
                std::unique_lock<std::mutex> unique_lock_(m_thr_pool_mutex);
                m_thr_pool_condition_var.wait(unique_lock_, [&]()
                { 
                    return this->m_wake.load(); 
                });
                
                m_wake.store(false);

std::cout << __FILE__ << "  " << "thr wake!\r\n";
            }
        });
    }

    void wake()
    {
        m_wake.store(true);
        m_thr_pool_condition_var.notify_one();
    }
};





//set pool default thread num
inline size_t set_default_thread() noexcept
{
    size_t thread_num = std::thread::hardware_concurrency();
    if(thread_num > 4) { thread_num = 2; }
    return thread_num == 0 ? 2 : thread_num;
}

struct thread_pool {
    using TASK = std::packaged_task<void()>;

    std::atomic<size_t> thread_num;
    std::mutex m_mutex;
    std::condition_variable m_condition_var;
    std::vector<std::thread> m_pools;
    std::queue<TASK> m_queue;
    std::atomic<bool> m_stop_;
    std::atomic<int>  m_is_init;



    std::thread test_thread;
    bool start_thread_bool = false;


    // void start_thread();

    // void call_wake();


    static thread_pool& instance()
    {
        static thread_pool ins;
        return ins;
    }

    thread_pool(const thread_pool& that) = delete;
    thread_pool& operator= (const thread_pool&) = delete;

    ~thread_pool()
    {
        stop();
    }

    void stop()
    {
        m_stop_.store(true);
        m_condition_var.notify_all();
        for (auto &it : m_pools)
        {
            if (it.joinable())
            {
                it.join();
            }
        }
    }

    template<class Func, class... Args>
    std::future<std::invoke_result_t<std::decay_t<Func>, std::decay_t<Args>...>>
    submit(Func&& f, Args&&... args)
    {
        using task_rtn_type = std::invoke_result_t<std::decay_t<Func>, std::decay_t<Args>...>;

        auto new_task = std::make_shared<std::packaged_task<task_rtn_type()>>(
                std::bind(std::forward<Func>(f), std::forward<Args>(args)...));

        std::future<task_rtn_type> rtn = new_task->get_future();

        {
            std::lock_guard<std::mutex> lock(m_mutex);
            m_queue.emplace([new_task](){
                (*new_task)();
            });
        }

        m_condition_var.notify_one();

        return rtn;
    }

    void start()
    {
        m_is_init = 5;
std::cout << __FILE__ << " " << __LINE__ <<  "thread pool start!\r\n";

        for(int i = 0; i < thread_num; i++)
        {
             m_pools.emplace_back([this](){
                while(!m_stop_.load()) {
                    TASK task;
                    {
                        std::unique_lock<std::mutex> lock(m_mutex);
                        m_condition_var.wait(lock, [this]() {
// std::cout << "m condition : wake " << m_stop_ << std::endl;
std::cout << "!m_queue.empty() " << !m_queue.empty() << std::endl;
                            return m_stop_ || !m_queue.empty();
                        });

std::cout  << __LINE__ <<  "thread pool wake!\r\n";
                        if (m_queue.empty()) {
                            return;
                        }
std::cout  << __LINE__ <<  "thread pool run!\r\n" << "m_queue size = " << m_queue.size() << std::endl;
                        task = std::move(m_queue.front());
std::cout  << __LINE__ <<  "thread pool task!\r\n";          
                        m_queue.pop();
std::cout  << __LINE__ <<  "thread pool task!\r\n";
                    }
                    task();
std::cout  << __LINE__ <<  "thread pool task!\r\n";
                }
            });
        }
    }

private:
    thread_pool(size_t thread_num_ = set_default_thread())
    : thread_num(thread_num_),
      m_stop_(false),
      m_is_init(0)
      {
std::cout << "thread_num_ : " << thread_num_ << std::endl;
      }
};

