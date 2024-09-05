#pragma once
#include <functional>
#include <optional>
#include <sys/socket.h>
#include <string.h>
#include <errno.h>
#include <iostream>
#include <unistd.h>
#include <check_error.h>

#include <semaphore.h>
#include <fcntl.h>

struct sem_helper
{
	sem_helper() = delete;
	
	sem_helper(char* sem_name)
		: m_sem_name(sem_name)
	{
		m_sem = sem_open(sem_name, O_CREAT | O_EXCL, 0644, 0);  // 初始化为0
        if (m_sem == SEM_FAILED) {
			if (errno == EEXIST){
				// 可以选择打开现有信号量
				m_sem = sem_open(sem_name, 0);
				if (m_sem == SEM_FAILED){
					perror("sem_open");
				}
			}
		}
	}

	sem_helper(const sem_helper& that) = delete;
	sem_helper& operator= (const sem_helper& that) = delete;

	~sem_helper()
	{
		sem_close(m_sem);
        sem_unlink(m_sem_name);
	}

	operator sem_t*(){ return m_sem; }
	operator const char*() { return m_sem_name; }

	void sem_helper_wait() { sem_wait(m_sem); }
	void sem_helper_post() { sem_post(m_sem); }

	sem_t* m_sem;
    const char* m_sem_name;
};


class process_helper
{
public:
	process_helper() 
	{

		int ret = socketpair(AF_UNIX, SOCK_DGRAM, 0, pipes);
		if(ret == -1)
		{
std::cout << "create pipes failed, error_code = " << strerror(errno) << std::endl;
		}
	}

	virtual ~process_helper() {
	}

	template<typename function, typename... Args>
	process_helper(function&& func, Args&&... args)
		: m_binder(std::bind(std::forward<function>(func), std::forward<Args>(args)...))
	{
		int ret = socketpair(AF_UNIX, SOCK_DGRAM, 0, pipes);
		if(ret == -1){
std::cout << "create pipes failed, error_code = " << strerror(errno) << std::endl;
		}
	}

	template<typename function, typename... Args>
	void set_process_func(function&& func, Args&&... args)
	{
		m_binder = std::bind(std::forward<function>(func), std::forward<Args>(args)...);
	}

	void close_pipe_1(){ close(pipes[1]); }

	void close_pipe_0(){ close(pipes[0]); }

	int run_bind_func()
	{
		if (m_binder){ return m_binder();}
		else{ return -1; }
	}

	bool is_bind() const 
	{
		return static_cast<bool>(m_binder);
	}

	void start_process_func()
	{
		if(is_bind() == false) return;

		pid_t pid;
		if((pid = fork()) < 0){
std::cout << "create sub process failed, error_code = " << strerror(errno) << std::endl;
		}
		if(pid == 0)
		{
			//子进程， 接收_Recv， pipes[1]
			close(pipes[0]);
			//执行 子进程函数 
			run_bind_func();
			close(pipes[1]);
std::cout << " sub process end, pid = " << getpid() << std::endl;
			exit(0);
		}else{
			//主进程， 发送_Send, pipes[0]
			close(pipes[1]);
			m_pid = getpid();
// std::cout << " main process, pid = " <<  m_pid << "  " << getpid() << std::endl;
			return;
		}
	}

	int send_fd(int socket, int fd_to_send)
	{
		struct msghdr message;
		struct iovec iov;
		char buffer[1];
		struct cmsghdr *control_message = NULL;
		char control_buffer[CMSG_SPACE(sizeof(int))];
		
		buffer[0] = 'F';
		iov.iov_base = buffer;
		iov.iov_len = sizeof(buffer);
		
		memset(&message, 0, sizeof(message));
		message.msg_name = NULL;
		message.msg_namelen = 0;
		message.msg_iov = &iov;
		message.msg_iovlen = 1;
		
		memset(control_buffer, 0, sizeof(control_buffer));
		message.msg_control = control_buffer;
		message.msg_controllen = sizeof(control_buffer);
		
		control_message = CMSG_FIRSTHDR(&message);
		control_message->cmsg_level = SOL_SOCKET;
		control_message->cmsg_type = SCM_RIGHTS;
		control_message->cmsg_len = CMSG_LEN(sizeof(int));
		
		*((int *) CMSG_DATA(control_message)) = fd_to_send;

		int send_ret = sendmsg(socket, &message, 0);
        // perror("sendmsg");
		if(send_ret < 0)
		{
			std::cout << "send fd failed = " << strerror(errno) << std::endl;
			// exit(1);
		}
		else
		{
			std::cout << "sendmsg ret = " << send_ret << std::endl;
		}
        return 0;
    }

	ssize_t send_msg(int socket, const char* msg)
	{
		struct msghdr message;
		struct iovec iov;

		iov.iov_base = (void*)msg;
		iov.iov_len = strlen(msg) + 1;
		
		memset(&message, 0, sizeof(message));
		message.msg_name = NULL;
		message.msg_namelen = 0;
		message.msg_iov = &iov;
		message.msg_iovlen = 1;
		
		ssize_t send_ret = 0;
		if((send_ret = sendmsg(socket, &message, 0)) < 0)
		{
std::cout << "send msg failed123 = " << strerror(errno) << std::endl;
		}
        return send_ret;
	}
	
	int recv_fd(int socket)
	{
		struct msghdr message;
		struct iovec iov;
		char buffer[1];
		struct cmsghdr *control_message = NULL;
		char control_buffer[CMSG_SPACE(sizeof(int))];
		int received_fd;
		
		buffer[0] = ' ';
		iov.iov_base = buffer;
		iov.iov_len = sizeof(buffer);
		
		memset(&message, 0, sizeof(message));
		message.msg_name = NULL;
		message.msg_namelen = 0;
		message.msg_iov = &iov;
		message.msg_iovlen = 1;
		
		memset(control_buffer, 0, sizeof(control_buffer));
		message.msg_control = control_buffer;
		message.msg_controllen = sizeof(control_buffer);
		
		if (recvmsg(socket, &message, 0) < 0) {
			perror("recvmsg");
			exit(1);
		}
		
		control_message = CMSG_FIRSTHDR(&message);
		if (control_message && control_message->cmsg_level == SOL_SOCKET && control_message->cmsg_type == SCM_RIGHTS) {
			received_fd = *((int *) CMSG_DATA(control_message));
std::cout << "received_fd = " << received_fd << std::endl;
			return received_fd;
		}
		return -1;
	}

	void recv_msg(int socket, char* msg, size_t msg_len)
	{
		struct msghdr message;
		struct iovec iov;

		iov.iov_base = msg;
		iov.iov_len = msg_len;
		
		memset(&message, 0, sizeof(message));
		message.msg_name = NULL;
		message.msg_namelen = 0;
		message.msg_iov = &iov;
		message.msg_iovlen = 1;
		

		if (recvmsg(socket, &message, 0) < 0) 
		{
			perror("recvmsg");
		}
		else
		{
std::cout << "buffer : " << msg << std::endl;
		}
		return;
	}



	int pipes[2];

private:
	std::function<int(void)> m_binder;
	pid_t m_pid;
};
