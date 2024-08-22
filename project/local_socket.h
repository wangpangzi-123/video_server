#pragma once
#include <unistd.h>
#include <string>
#include <fcntl.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/un.h>

struct buffer : public std::string
{
	buffer() : std::string() {}
	buffer(size_t size) : std::string(size, '\0') {}
	
	operator char* () { return (char*)c_str(); }
	operator char* () const { return (char*)c_str(); }
	operator const char* () const { return c_str(); }
};

enum socket_attr {
	SOCK_IS_SERVER = 1,	//
	SOCK_IS_NONBLOCK = 2,
	SOCK_IS_UDP	= 4
};

struct socket_param
{
public:
	socket_param()
	{
		bzero(&addr_in, sizeof(addr_in));
		bzero(&addr_un, sizeof(addr_un));
		m_port = -1;
		m_attr = 0;
	}

	~socket_param() {}

	socket_param(const buffer& ip, short port, int attr)
	{
		m_ip = ip;
		m_port = port;
		m_attr = attr;
		addr_in.sin_family = AF_INET;
		addr_in.sin_port = m_port;
		addr_in.sin_addr.s_addr = inet_addr(ip);
	}

	socket_param(const buffer& path, int attr)
	{
		m_ip = path;
		addr_un.sun_family = AF_UNIX;
		strcpy(addr_un.sun_path, path);
		m_attr = attr;
	}

	socket_param(const socket_param& that)
	{
		m_ip = that.m_ip;
		m_port = that.m_port;
		m_attr = that.m_attr;
		memcpy(&addr_in, &that.addr_in, sizeof(sockaddr_in));
		memcpy(&addr_un, &that.addr_un, sizeof(sockaddr_un));
	}

	socket_param& operator=(const socket_param& that)
	{
		if (this != &that)
		{
			m_ip = that.m_ip;
			m_port = that.m_port;
			m_attr = that.m_attr;
			memcpy(&addr_in, &that.addr_in, sizeof(sockaddr_in));
			memcpy(&addr_un, &that.addr_un, sizeof(sockaddr_un));
		}
		return *this;
	}

	sockaddr* get_in_address()  { return (sockaddr*)&addr_in; }
	sockaddr* get_un_address()  { return (sockaddr*)&addr_un; }

	sockaddr_in addr_in;
	sockaddr_un addr_un;

	buffer m_ip;
	short  m_port;
	int	   m_attr;
};

struct socket_base
{
	socket_base() 
		: m_socket(-1), status(0){}

	virtual ~socket_base() { close_socket(); }
	
	//初始化套接字, bind, listen
	virtual int init(const socket_param& param) = 0;
	//连接服务器, accept, connect
	virtual int link(socket_base** pClient) = 0;
	//接收消息
	virtual int recv_buffer(buffer& recv_buffer) = 0;
	//发送消息
	virtual int send_buffer(const buffer& send_buffer) = 0;

	virtual int close_socket()
	{
		if (m_socket != -1)
		{
			status = 3;
			int fd = m_socket;
			m_socket = -1;
			close(fd);
		}
	}

protected:
	int m_socket;
	int status;	//
	socket_param m_socket_param;
};


struct local_socket : public socket_base
{
	local_socket() : socket_base() {}
	
	local_socket(int socket)
	{
		m_socket = socket;
	}
	
	virtual ~local_socket() { close_socket(); }

	virtual int init(const socket_param& param) override
	{
		if (status != 0) return -1;
		m_socket_param = param;
		int type = (m_socket_param.m_attr & socket_attr::SOCK_IS_UDP) ? SOCK_DGRAM : SOCK_STREAM;
		if (m_socket == -1)
			m_socket = socket(PF_LOCAL, type, 0);
		if (m_socket == -1)
			return -2;

		int ret = 0;
		if (m_socket_param.m_attr & socket_attr::SOCK_IS_SERVER)	//如果是服务器需要绑定 socket 和 listen
		{
			ret = bind(m_socket, m_socket_param.get_un_address(), sizeof(sockaddr_un));
			if (ret == -1)
				return -3;
			ret = listen(m_socket, 32);
			if (ret == -1)
				return -4;
		}
		if (m_socket_param.m_attr & socket_attr::SOCK_IS_NONBLOCK)
		{
			int option = fcntl(m_socket, F_GETFL);
			if (option == -1)
				return -5;
			option |= O_NONBLOCK;
			option = fcntl(m_socket, F_SETFL, option);
			if (option == -1)
				return -6;
		}
		status = 1;
		return 0;
	}

	virtual int link(socket_base** pClient) override
	{
		if (status <= 0 || status == -1)
			return -1;

		int ret = 0;
		if (m_socket_param.m_attr & socket_attr::SOCK_IS_SERVER)
		{
			if (pClient == NULL)
				return -2;
			//如果是服务器，则进行accept操作
			socket_param param;
			socklen_t len = sizeof(sockaddr_un);
			int fd = accept(m_socket, param.get_un_address(), &len);
			if (fd == -1)
				return -3;
			*pClient = new local_socket(fd);
			if (pClient == NULL)
				return -4;
			ret = (*pClient)->init(param);
			if (ret != 0)
			{
				delete pClient;
				pClient = NULL;
				return -5;
			}
		}
		else
		{
			//如果是客户端，则进行connect操作
			ret = connect(m_socket, m_socket_param.get_un_address(), sizeof(sockaddr_un));
			if (ret < 0)
			{
				return -6;
			}
		}
		status = 2;
		return 0;
	}

	virtual int recv_buffer(buffer& recv_buffer) override
	{
		if (status < 2 || status == -1)
			return -1;
		ssize_t recv_len = read(m_socket, (char*)recv_buffer, sizeof(recv_buffer));
		if (recv_len > 0)
		{
			recv_buffer.resize(recv_len);
			return (int)recv_len;
		}
		if (recv_len < 0)
		{
			if (errno == EINTR || errno == EAGAIN)
			{
				recv_buffer.clear();
				return 0;	//数据没有收到
			}
			return -2;	//发送失败
		}
		return -3;
	}
	//发送消息
	virtual int send_buffer(const buffer& send_buffer) override
	{
		if (status < 2 || status == -1)
			return -1;
		ssize_t index = 0;
		while (index < (ssize_t)(send_buffer.size()))
		{
			ssize_t send_len = write(m_socket, (char*)send_buffer + index, send_buffer.size() - index);
			if (send_len == 0)
				return -2;
			if (send_len < 0)
				return -3;
			index += send_len;
		}
		return 0;
	}
};











