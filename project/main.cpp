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

int main() {
    // 创建一个进程,传入一个 lambda 函数和参数
    process_helper process;

    process.set_process_func(hello, 1);
    process.create_sub_process();
    

    


    return 0;
}

