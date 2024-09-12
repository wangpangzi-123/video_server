// #include <cstdio>
// #include <iostream>
// #include <unistd.h>
// #include <functional>
// #include<sys/socket.h>
// #include <fcntl.h>
// #include <sys/wait.h>

// #include "function.h"
// #include "Logger.h"
// #include "thread.h"
// #include "server.h"
// #include "http_parser.h"
// #include <cassert>

// int sub_process_recv(process_helper* helper)
// {
//     char buff[1024] = {0};
//     // int recv_fd = helper->recv_msg(helper->pipes[1], buff, sizeof(buff));
//     helper->recv_msg(helper->pipes[1], buff, sizeof(buff));
// std::cout << "recv : " << buff << std::endl;

//     // std::cout << "sub process recv fd = " << recv_fd << std::endl;

//     // char buf[100] = {0};

//     // int read_len = read(recv_fd, buf, sizeof(buf));

//     // std::cout << "buf : " << buf << std::endl;

//     // std::cout << "buf len : " << read_len << std::endl;

//     // if(close(recv_fd))
//     // {
//     //     std::cout << "sub process success exit!\r\n";
//     // }

//     return 0;
// }


// int LogTest()
// {
// 	char buffer[] = "hello edoyun! 冯老师";
// 	usleep(1000 * 100);
// 	TRACEI("here is log %d %c %f %g %s 哈哈 嘻嘻 易道云", 10, 'A', 1.0f, 2.0, buffer);
// std::cout << __LINE__ << "SECOND TRACE !\r\n";
// 	TRACEI("here is log %d %c %f %g %s 哈哈 嘻嘻 易道云", 10, 'A', 1.0f, 2.0, buffer);

// 	//DUMPD((void*)buffer, (size_t)sizeof(buffer));
// 	//LOGE << 100 << " " << 'S' << " " << 0.12345f << " " << 1.23456789 << " " << buffer << " 易道云编程";
// 	return 0;
// }


// int sub_process_log(process_helper* helper)
// {
//     // std::cout << "sub_process : pid = " << getpid() << std::endl;
//     Logger log_server;
//     log_server.start();
// std::cout << "log_server _ !\r\n";

//     while(1)
//     {

//     }
// }

// static http_parser_settings *current_pause_parser;

// static http_parser_settings settings_null =
//   {.on_message_begin = 0
//   ,.on_url = 0
//   ,.on_status = 0
//   ,.on_header_field = 0
//   ,.on_header_value = 0
//   ,.on_headers_complete = 0
//   ,.on_body = 0
//   ,.on_message_complete = 0
//   ,.on_chunk_header = 0
//   ,.on_chunk_complete = 0
//   };


// void
// test_header_overflow_error (int req)
// {
//   http_parser parser;
//   http_parser_init(&parser, req ? HTTP_REQUEST : HTTP_RESPONSE);
//   size_t parsed;
//   const char *buf;
//   buf = req ? "GET / HTTP/1.1\r\n" : "HTTP/1.0 200 OK\r\n";
//   parsed = http_parser_execute(&parser, &settings_null, buf, strlen(buf));
//   assert(parsed == strlen(buf));

//   buf = "header-key: header-value\r\n";
//   size_t buflen = strlen(buf);

//   int i;
//   for (i = 0; i < 10000; i++) {
//     parsed = http_parser_execute(&parser, &settings_null, buf, buflen);
//     if (parsed != buflen) {
//       //fprintf(stderr, "error found on iter %d\n", i);
//       assert(HTTP_PARSER_ERRNO(&parser) == HPE_HEADER_OVERFLOW);
//       return;
//     }
//   }

//   fprintf(stderr, "\n*** Error expected but none in header overflow test ***\n");
//   abort();
// }


// int main() {

// //test_server
//     // server  ser;
//     // ser.server_accept_open();
//     // ser.server_client_proc_open();


//     // // sleep(5);

//     // while(1)
//     // {

//     // }

// //-------------http parser---------------
//     test_header_overflow_error(HTTP_REQUEST);

//     return 0;
// }





// //test_func_1
// /*

//     // 创建一个进程,传入一个 lambda 函数和参数
//     process_helper process;

//     process.set_process_func(sub_process_recv, &process);
    
//     process.start_process_func();
    
//     int fd = open("example.txt", O_CREAT | O_RDWR, 0777);

//     if(fd > 0)
//         std::cout << "fd open !\r\n";
    
//     process.send_fd(process.pipes[0], fd);


//     wait(NULL);

//     close(fd);

//     close(process.pipes[0]);

// */



#include "http_parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <string>

#include "Http_parser.h"

static http_parser *parser;
 
int on_message_begin(http_parser* _) {
  (void)_;
  printf("\n***MESSAGE BEGIN***\n\n");
  return 0;
}
 
int on_headers_complete(http_parser* _) {
  (void)_;
  printf("\n***HEADERS COMPLETE***\n\n");
  return 0;
}
 
int on_message_complete(http_parser* _) {
  (void)_;
  printf("\n***MESSAGE COMPLETE***\n\n");
  return 0;
}
 
 
int on_url(http_parser* _, const char* at, size_t length) {
  (void)_;
  printf("Url: %.*s\n", (int)length, at);
  // printf("---  %s   ---\r\n", at);
 
 
  return 0;
}
 
int on_header_field(http_parser* _, const char* at, size_t length) {
  (void)_;
  printf("Header field: %.*s\n", (int)length, at);
  return 0;
}
 
int on_header_value(http_parser* _, const char* at, size_t length) {
  (void)_;
  printf("Header value: %.*s\n", (int)length, at);
  return 0;
}
 
int on_body(http_parser* _, const char* at, size_t length) {
  (void)_;
  printf("Body: %.*s\n", (int)length, at);
  return 0;
}

int main() {
    http_parser_settings parser_set;
 
    // http_parser的回调函数，需要获取HEADER后者BODY信息，可以在这里面处理。
    parser_set.on_message_begin = on_message_begin;
    parser_set.on_header_field = on_header_field;
    parser_set.on_header_value = on_header_value;
    parser_set.on_url = on_url;
    parser_set.on_body = on_body;
    parser_set.on_headers_complete = on_headers_complete;
    parser_set.on_message_complete = on_message_complete;
 
 
  std::string	str = "GET /favicon.ico HTTP/1.1\r\n"
		"Host: 0.0.0.0=5000\r\n"
		"User-Agent: Mozilla/5.0 (X11; U; Linux i686; en-US; rv:1.9) Gecko/2008061015 Firefox/3.0\r\n"
		"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n";

  // std::string	str = "GET /favicon.ico HTTP/1.1\r\n"
	// 	"Host: 0.0.0.0=5000\r\n"
	// 	"User-Agent: Mozilla/5.0 (X11; U; Linux i686; en-US; rv:1.9) Gecko/2008061015 Firefox/3.0\r\n"
	// 	"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*; q = 0.8\r\n"
	// 	"Accept-Language: en-us,en;q=0.5\r\n"
	// 	"Accept-Encoding: gzip,deflate\r\n"
	// 	"Accept-Charset: ISO-8859-1,utf-8;q=0.7,*;q=0.7\r\n"
	// 	"Keep-Alive: 300\r\n"
	// 	"Connection: keep-alive\r\n"
	// 	"\r\n";
 
	// size_t parsed;
	// parser = (http_parser*)malloc(sizeof(http_parser)); // 分配一个http_parser
			 
	// http_parser_init(parser, HTTP_REQUEST); // 初始化parser为Request类型
	// parsed = http_parser_execute(parser, &parser_set, str.c_str(), str.size()); // 执行解析过程
	
	// http_parser_execute(parser, &parser_set, str.c_str(), 0); // 信息读取完毕
 
	// free(parser);
	// parser = NULL;


  Http_parser parser;


  parser.parser_execute(str.c_str(), str.size());
  std::cout << "url:" << parser.url() << std::endl;
  std::cout << "header_field :" <<parser.header_field() << std::endl;
  std::cout << "header_value :" << parser.header_value() << std::endl;
  std::cout << "body : " << parser.body() << std::endl;


  Http_parser parser1(parser);

  parser1.parser_execute(str.c_str(), str.size());


  return 0;
}