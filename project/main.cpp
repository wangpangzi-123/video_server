#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <functional>

#include "function.h"


int hello(int a)
{
    std::cout << "hello\r\n";
    return 0;
}

#include<sys/socket.h>
int main() {
    // 创建一个进程,传入一个 lambda 函数和参数
    process_helper process;

    process.set_process_func(hello, 1);
    process.create_sub_process();
    

    char buf[2][10] = { "a", "b" };
    std::cout << sizeof(buf[0]) << std::endl;;

    int fd_array[5] = { 1, 2, 3, 4, 5 };
    std::cout << "fd_array : " << sizeof(fd_array) << std::endl;
    
    int a = 0;


    return 0;
}

