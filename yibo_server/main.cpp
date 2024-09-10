#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <functional>
#include<sys/socket.h>
#include <fcntl.h>
#include <sys/wait.h>

#include "function.h"
#include "Logger.h"
#include "thread.h"
#include "server.h"

int sub_process_recv(process_helper* helper)
{
    char buff[1024] = {0};
    // int recv_fd = helper->recv_msg(helper->pipes[1], buff, sizeof(buff));
    helper->recv_msg(helper->pipes[1], buff, sizeof(buff));
std::cout << "recv : " << buff << std::endl;

    // std::cout << "sub process recv fd = " << recv_fd << std::endl;

    // char buf[100] = {0};

    // int read_len = read(recv_fd, buf, sizeof(buf));

    // std::cout << "buf : " << buf << std::endl;

    // std::cout << "buf len : " << read_len << std::endl;

    // if(close(recv_fd))
    // {
    //     std::cout << "sub process success exit!\r\n";
    // }

    return 0;
}


int LogTest()
{
	char buffer[] = "hello edoyun! 冯老师";
	usleep(1000 * 100);
	TRACEI("here is log %d %c %f %g %s 哈哈 嘻嘻 易道云", 10, 'A', 1.0f, 2.0, buffer);
std::cout << __LINE__ << "SECOND TRACE !\r\n";
	TRACEI("here is log %d %c %f %g %s 哈哈 嘻嘻 易道云", 10, 'A', 1.0f, 2.0, buffer);

	//DUMPD((void*)buffer, (size_t)sizeof(buffer));
	//LOGE << 100 << " " << 'S' << " " << 0.12345f << " " << 1.23456789 << " " << buffer << " 易道云编程";
	return 0;
}


int sub_process_log(process_helper* helper)
{
    // std::cout << "sub_process : pid = " << getpid() << std::endl;
    Logger log_server;
    log_server.start();
std::cout << "log_server _ !\r\n";

    while(1)
    {

    }
}




int main() {

//test_server
    server  ser;
    ser.server_accept_open();
    ser.server_client_proc_open();


    // sleep(5);


    // socket_param_ param1;
    // socket_param_ param2 = param1;

    // param2
    while(1)
    {

    }


    return 0;
}





//test_func_1
/*

    // 创建一个进程,传入一个 lambda 函数和参数
    process_helper process;

    process.set_process_func(sub_process_recv, &process);
    
    process.start_process_func();
    
    int fd = open("example.txt", O_CREAT | O_RDWR, 0777);

    if(fd > 0)
        std::cout << "fd open !\r\n";
    
    process.send_fd(process.pipes[0], fd);


    wait(NULL);

    close(fd);

    close(process.pipes[0]);

*/




// #include <iostream>
// #include <condition_variable>
// #include <mutex>
// #include <thread>
// #include <vector>
// #include <functional>
// #include <future>
// #include <queue>
// #include <memory>
// #include <atomic>
// #include <stdlib.h>

// struct thread_pool_test
// {
//     std::mutex                  m_thr_pool_mutex;
//     std::condition_variable     m_thr_pool_condition_var;
//     std::atomic<bool>           m_stop;

//     //测试用
//     std::atomic<bool>           m_wake;
//     std::thread                 thr;

//     thread_pool_test() : m_stop(false), m_wake(false){}

//     ~thread_pool_test()
//     {
//         stop();
//         if(thr.joinable())
//         {
//             thr.join();
//         }
//     }

//     void stop()
//     {
//         m_stop = true;
//         m_wake = true;
//         m_thr_pool_condition_var.notify_one();
//     }

//     void start()
//     {

//         thr = std::thread([this]()
//                           {
//                               std::cout << __FILE__ << "  " << "thr start!\r\n";
//                               while(!m_stop)
//                               {
//                                   std::unique_lock<std::mutex> unique_lock_(m_thr_pool_mutex);
//                                   m_thr_pool_condition_var.wait(unique_lock_, [&]()
//                                   {
//                                       return this->m_wake.load();
//                                   });

//                                   m_wake.store(false);

//                                   std::cout << __FILE__ << "  " << "thr wake!\r\n";
//                               }
//                           });
//     }

//     void wake()
//     {
//         m_wake.store(true);
//         m_thr_pool_condition_var.notify_one();
//     }
// };



// int main() {


//     thread_pool_test t;

//     t.start();

//     t.wake();

//     while(1)
//     {
//         t.wake();
//         int i = 100000;
//         while(i != 0) {
//             i--;
//         }
//     }


//     return 0;
// }