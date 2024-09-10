//
// Created by lintao on 2024/9/9.
//

#include "thread_pool.h"
#include <thread>


// std::condition_variable cv_lock_;
// std::mutex cv_mt_;

//     void thread_pool::call_wake()
//     {
//         std::cout <<" call wake!\r\n";
//         {
//             std::lock_guard<std::mutex> lock(cv_mt_);
//             start_thread_bool = true;
//         }
//         std::cout << "call wake cv_lock_ addr : " << &cv_lock_ << std::endl;
//         cv_lock_.notify_all();
//         std::cout << "call wake cv_lock_ addr : " << &cv_lock_ << std::endl;
//     }
//     void thread_pool::start_thread()
//     {
//         test_thread = std::thread([this](){
//             while(1)
//             {
// std::cout << "start_thread start!\r\n, cv_lock addr : " << &cv_lock_<<std::endl;
//                 std::unique_lock<std::mutex> uni_lock(cv_mt_);
//                 cv_lock_.wait(uni_lock, [this](){
//                     return start_thread_bool;
//                 });
//                 // start_thread_bool = false;
//                 std::cout << "test_thread wake!\r\n";
//             }
//         });
//     }