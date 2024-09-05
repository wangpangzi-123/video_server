#pragma once
#include <iostream>

#include "epoll_func.h"
#include "local_socket.h"
#include <string>
#include <sys/stat.h>
#include "thread.h"
#include <sys/timeb.h>
#include <sstream>
#include <stdarg.h>
#include <filesystem>
//1、完成 Logger 和 local_socket 的连接， 
//2、先完成 Logger 和 epoll 的 串联

enum LogLevel {
	LOG_INFO,
	LOG_DEBUG,
	LOG_WARNING,
	LOG_ERROR,
	LOG_FATAL
};

struct LogInfo {
public:
	LogInfo(){}

	LogInfo(
		const char* file, int line, const char* func,
		pid_t pid, pthread_t tid, int level,
		const char* fmt, ...);
	LogInfo(
		const char* file, int line, const char* func,
		pid_t pid, pthread_t tid, int level);

	LogInfo(const char* file, int line, const char* func,
		pid_t pid, pthread_t tid, int level,
		void* pData, size_t nSize);

	~LogInfo();

	operator buffer()const {
		return m_buf;
	}

	template<typename T>
	LogInfo& operator<<(const T& data) {
		std::stringstream stream_;
		stream_ << data;
		printf("%s(%d):[%s][%s]\n", __FILE__, __LINE__, __FUNCTION__, stream_.str().c_str());
		m_buf += stream_.str().c_str();
		printf("%s(%d):[%s][%s]\n", __FILE__, __LINE__, __FUNCTION__, (char*)m_buf);
		return *this;
	}
private:
	bool bAuto;//默认是false 流式日志，则为true
	buffer m_buf;
};


class Logger
{
public:
    Logger()
    {
        //0、创建日志文件路径
        create_log_file();


        //1、本地 socket 需要先有 log 文件夹
        if(access("log", W_OK | R_OK) != 0)
        { 
            mkdir("log", S_IRUSR | S_IWUSR | 
                         S_IRGRP | S_IWGRP | 
                         S_IROTH);
        }

        //2、在本地 log 文件夹下 创建 server.sock 
        socket_ = new local_socket();
        // buffer path = "./log/server.sock";
        // socket_param param_("./log/server.sock", SOCK_IS_SERVER);


        if(access("./log/server.sock", W_OK | R_OK) == 0)
        {
            if(remove("./log/server.sock") == 0)
            {
std::cout << "./log/server.sock delete success!\r\n";
            }
        }
        m_file = fopen(m_path, "w+");
		
        int init_rtn = socket_->init(socket_param ("./log/server.sock", SOCK_IS_SERVER));
        
        //3、创建 epoll fd
        m_epoll_helper.create();

        //4、将 本地 socket_ 添加至 epoll_
        int add_event = m_epoll_helper.add_event(*socket_, (void*)(socket_), EPOLLIN | EPOLLERR);
std::cout << __LINE__ << "  add event : " << add_event << std::endl;
        //5、m_thread 加载 线程函数
        m_thread.reset_func(&Logger::thread_epoll_fun, this);


        std::cout << "init_rtn " << init_rtn << std::endl;
    }

    virtual ~Logger()
    {
        m_epoll_helper.close_epoll();
        if(socket_ != nullptr)
        {
            socket_base* socket_temp_ = socket_;
            socket_ = nullptr;
            delete socket_temp_;
        }
    }

    void start()
    {
        m_thread.start();
std::cout << "m_thread start!\r\n";
    }

    void WriteLog(const buffer& data) 
    {
		if (m_file != NULL) 
        {
			FILE* pFile = m_file;
			fwrite((char*)data, 1, data.size(), pFile);
			fflush(pFile);
#ifdef _DEBUG
			printf("%s", (char*)data);
#endif
		}
        else{
            std::cout << "m_file == empty!\r\n";
        }
	}

    void create_log_file()
    {
        char curpath[256] = "";
		getcwd(curpath, sizeof(curpath));
		m_path = curpath;
        m_path += "/log/" + GetTimeStr() + ".log";
		printf("%s(%d):[%s]path=%s\n", __FILE__, __LINE__, __FUNCTION__, (char*)m_path);
    }

        //给其他线程 或 进程 调用的 向日志服务器写
    static void Trace(const LogInfo& info)
    {
        int ret = 0;
        static thread_local local_socket client;
        if(client == -1)
        {
            ret = client.init(socket_param ("./log/server.sock", 0));
            if (ret != 0)
            {
#ifdef _DEBUG
                printf("%s(%d):[%s]ret=%d\n", __FILE__, __LINE__, __FUNCTION__, ret);
#endif
                return;
            }
printf("%s(%d):[%s]ret=%d client=%d\n", __FILE__, __LINE__, __FUNCTION__, ret, (int)client);
            ret = client.link();
printf("%s(%d):[%s]ret=%d client=%d status=%d\n", __FILE__, __LINE__, __FUNCTION__, ret, (int)client, client.get_status());

        }
        ret = client.send_buffer(info);
		printf("%s(%d):[%s]ret=%d client=%d\n", __FILE__, __LINE__, __FUNCTION__, ret, (int)client);
    }

    static buffer GetTimeStr() 
    {
		buffer result(128);
		timeb tmb;
		ftime(&tmb);
		tm* pTm = localtime(&tmb.time);
		int nSize = snprintf(result, result.size(),
			"%04d-%02d-%02d_%02d-%02d-%02d.%03d",
			pTm->tm_year + 1900, pTm->tm_mon + 1, pTm->tm_mday,
			pTm->tm_hour, pTm->tm_min, pTm->tm_sec,
			tmb.millitm
		);
		result.resize(nSize);
		return result;
	}

private:
    int thread_epoll_fun()
    {
        while(1)
        {
            printf("epoll_thread_epoll_fun eter!\r\n");
            ssize_t epoll_rtn = m_epoll_helper.wait_event(-1);
            printf("epoll_rtn = %d\r\n", epoll_rtn);
            std::cout << "(" << __LINE__ << ") : " << __FUNCTION__ << " epoll_rtn: " << epoll_rtn << std::endl;
            ssize_t i = 0;
            for (; i < epoll_rtn; i++)
            {
                std::cout << __LINE__ << "EPOLLIN\r\n";

                if (m_epoll_helper.epoll_events[i].events & EPOLLERR)
                {
                    std::cout << "events & EPOLLERR = 1" << std::endl;
                    m_thread.stop();
                    break;
                }
                else if (m_epoll_helper.epoll_events[i].events & EPOLLIN)
                {
                    std::cout << __LINE__ << "EPOLLIN\r\n";
                    if (m_epoll_helper.epoll_events[i].data.ptr == socket_)
                    {
                        socket_base *ptr_client = nullptr;
                        int r = socket_->link(&ptr_client);
                        printf("%s(%d):[%s]ret=%d \n", __FILE__, __LINE__, __FUNCTION__, r);
                        if (r < 0)
                            continue;

                        r = m_epoll_helper.add_event(*ptr_client, (void *)(ptr_client), EPOLLIN | EPOLLERR);
                        printf("%s(%d):[%s]ret=%d \n", __FILE__, __LINE__, __FUNCTION__, r);
                        if (r < 0)
                        {
                            delete ptr_client;
                            continue;
                        }
                    }
                    else
                    {
std::cout << __LINE__ << "EPOLLIN\r\n";
                        socket_base *ptr_client = (socket_base *)m_epoll_helper.epoll_events[i].data.ptr;
                        if (ptr_client != NULL)
                        {
                            buffer data(1024 * 1024);
                            int r = ptr_client->recv_buffer(data);
printf("%s(%d):[%s]ret=%d \n", __FILE__, __LINE__, __FUNCTION__, r);
printf("%s(%d):[%s]ret=%d client=%d status=%d\n", __FILE__, __LINE__, __FUNCTION__, r, (int)(*ptr_client), ptr_client->get_status());

                            if (r <= 0)
                            {
                                delete ptr_client;
                            }
                            else
                            {
                                printf("%s(%d):[%s]data=%s \n", __FILE__, __LINE__, __FUNCTION__, (char *)data);
                                WriteLog(data);
                            }
                        }
                    }
                }
                std::cout << __LINE__ << " epoll events : " << m_epoll_helper.epoll_events[i].events << std::endl;
            }
        }

    }



	FILE* m_file;
    buffer        m_path;
    Tthread       m_thread;
    epoll_helper  m_epoll_helper;
    socket_base*  socket_; 
};

#define TRACEI(...) Logger::Trace(LogInfo(__FILE__, __LINE__, __FUNCTION__, getpid(), pthread_self(), LOG_INFO, __VA_ARGS__))

