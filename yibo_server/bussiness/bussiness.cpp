#include "bussiness.h"
#include "server.h"

#include <thread>
#include <condition_variable>
#include <mutex>


// std::mutex mtx;
// std::condition_variable cv;
// bool ready = false;


// void client_proc_helper::waiting_thread() {
    
// std::cout << "waiting thread\r\n";
//     std::unique_lock<std::mutex> u_lock_(mtx);
//     cv.wait(u_lock_, [] { return ready; });  // 在等待时锁定互斥量
//     std::cout << "Thread awakened!\n";
// }

// void client_proc_helper::notifying_thread() 
// {
//     {
// std::cout << "notify thread\r\n";
//         std::lock_guard<std::mutex> lock(cv_mutex_);
//         ready = true;
//     }  // 先改变条件后释放锁
//     cv.notify_one();  // 唤醒一个等待线程
// }

// void client_proc_helper::waiting_thread() 
// {
// std::cout << "waiting thread\r\n";
//     while(1)
//     {
//         std::unique_lock<std::mutex> u_lock_(cv_mutex_);
//         cv_lock_.wait(u_lock_, [this](){ return cv_wake_.load(); });  // 在等待时锁定互斥量
//         cv_wake_.store(false);
//         std::cout << "Thread awakened!\n";
//     }
// }

// void client_proc_helper::notifying_thread() 
// {
//     {
// std::cout << "notify thread\r\n";
//         std::lock_guard<std::mutex> lock(cv_mutex_);
//         cv_wake_.store(true);
//     }  // 先改变条件后释放锁
//     cv_lock_.notify_one();  // 唤醒一个等待线程
// }