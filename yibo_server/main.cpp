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


int sub_process_recv(process_helper* helper)
{
    int recv_fd = helper->recv_fd(helper->pipes[1]);

    std::cout << "sub process recv fd = " << recv_fd << std::endl;

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

    // // test test1;

    // // test1.t_start();

    // // std::this_thread::sleep_for(std::chrono::seconds(3)); // 避免占用过多 CPU
    // // std::cout << " 11main process, pid = " << getpid() << std::endl;
    // process_helper sub_log_process;
    // sub_log_process.set_process_func(sub_process_log, &sub_log_process);
    // sub_log_process.start_process_func();
    // // std::cout << "main_process : pid = " << getpid() << std::endl;

    // LogTest();

    // // for(int i = 0; i < 100000; i++)
    // // {
    // //     ;
    // // }


    // // LogTest();

    // while(1)
    // {

    // }


    // ---------------------------
    process_helper process;

    process.set_process_func(sub_process_recv, &process);
    
    process.start_process_func();
    
    // int fd = open("example.txt", O_CREAT | O_RDWR, 0777);

    // if(fd > 0)
    //     std::cout << "fd open !\r\n";
    
    process.SendFD(process.pipes[0], -1);


    wait(NULL);

    // close(fd);

    close(process.pipes[0]);

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