#pragma once
#include <functional>
#include <optional>
#include <sys/socket.h>




class process_helper
{
public:
	process_helper() {}

	virtual ~process_helper() {}

	template<typename function, typename... Args>
	process_helper(function&& func, Args&&... args)
		: m_binder(std::bind(std::forward<function>(func), std::forward<Args>(args)...)){}

	template<typename function, typename... Args>
	void set_process_func(function&& func, Args&&... args)
	{
		m_binder = std::bind(std::forward<function>(func), std::forward<Args>(args)...);
	}

	int run_bind_func()
	{
		if (m_binder)
		{
			return m_binder();
		}
		else
		{
			return -1;
		}
	}

	bool is_bind() const {
		return static_cast<bool>(m_binder);
	}

	int create_sub_process()
	{
		if (is_bind() == false)
			return -1;
		pid_t pid = fork();
		if (pid == -1)
			return -2;	//�ӽ��̴���ʧ��

		if (pid == 0)	
		{
			//�ӽ���
			printf("m_pid = %d\r\n", pid);
			return run_bind_func();
		}
		
		m_pid = pid;
		printf("m_pid = %d\r\n", pid);
		return 0;
	}

	//����-> 
	int send_fd(int& fd)
	{
		//
		struct msghdr	msg;
		struct cmsghdr* p_cmsg;
		struct iovec	vec;

		
		//���贫�͵����� �� int �������飬ģ�⴫�Ͷ�� �ļ�������
		int fd_array[5] = { 1, 2, 3, 4, 5 };
		
		//1����� msg
		msg.msg_name = NULL;
		msg.msg_namelen = 0;
		msg.msg_iov = &vec;
		msg.msg_iovlen = 1;
		msg.msg_flags = 0;

		
		//2�����ٸ��� 1 bytes ����ʵ����
		char real_data = 'a';
		vec.iov_base = &real_data;
		vec.iov_len = sizeof(real_data);


		//3����丽�����ݣ����ļ����������� ��������
		p_cmsg = CMSG_FIRSTHDR(&msg);	// ��������ָ��
		p_cmsg->cmsg_level = SOL_SOCKET;
		p_cmsg->cmsg_type = SCM_RIGHTS;
		p_cmsg->cmsg_len = CMSG_LEN(sizeof(fd_array));
		int* p_fds = (int*)CMSG_DATA(p_cmsg);
		p_fds = fd_array;
		
	
		//
	}

private:
	std::function<int(void)> m_binder;
	pid_t m_pid;
};
