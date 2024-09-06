#pragma once
#include <fcntl.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string>

struct bytes_buffer : public std::string
{
    bytes_buffer() : std::string() {}
	bytes_buffer(const char* data) : std::string(data){}
	bytes_buffer(size_t size) : std::string(size, '\0') {}
	
	operator char* () { return (char*)c_str(); }
	operator char* () const { return (char*)c_str(); }
	operator const char* () const { return c_str(); }
};

enum socket_attr {
	SOCK_IS_SERVER = 1,	//
	SOCK_IS_NONBLOCK = 2,
	SOCK_IS_UDP	= 4,
	SOCK_IS_IP  = 8
};

/*
    socket_param 参数：
            bytes_buffer    m_ip;
            short           m_port;
	        int             m_attr;

    socket_param_local  local_param:
            addr_un.sun_path:   本地socket 通信地址
            addr_un.sun_family: 本地socket family
    
    socket_param_inet   inet_param:
            addr_in.sin_addr.s_addr:  inet_addr(ip);
            addr_in.sin_port:         port;
            addr_in.sin_family:       sin_family;

*/
struct socket_param
{
    //本地 socket 连接参数
    struct socket_param_local
    {
        socket_param_local(){ bzero(&addr_un, sizeof(sockaddr_un)); }
        ~socket_param_local(){}
        socket_param_local(const socket_param_local& that){
            strcpy(addr_un.sun_path, that.addr_un.sun_path);
            addr_un.sun_family = that.addr_un.sun_family;
        }
        socket_param_local& operator= (const socket_param_local& that){
            strcpy(addr_un.sun_path, that.addr_un.sun_path);
            addr_un.sun_family = that.addr_un.sun_family;
        }
        void init_param(const bytes_buffer& path, unsigned short int sin_family = AF_UNIX)
        { 
            strcpy(addr_un.sun_path, path);
            addr_un.sun_family = sin_family;
        }
        sockaddr_un addr_un;
    };

    //inet socket 连接参数
    struct socket_param_inet
    {
        socket_param_inet(){ bzero(&addr_in, sizeof(sockaddr_in)); }
        void init_param(const bytes_buffer& ip, short port, unsigned short int sin_family = AF_INET)
        {
            addr_in.sin_addr.s_addr = inet_addr(ip);
            addr_in.sin_port = port;
            addr_in.sin_family = sin_family;
        }
        sockaddr_in addr_in;
    };

    void init_inet_param(const bytes_buffer& ip, short port){ inet_param.init_param(ip, port); }
    void init_local_param(const bytes_buffer& path) { local_param.init_param(path); }

    sockaddr* get_in_address()  { return (sockaddr*)&(inet_param.addr_in); }
	sockaddr* get_un_address()  { return (sockaddr*)&(local_param.addr_un); }

    socket_param() : m_ip(""), m_port(-1), m_attr(0){}

    ~socket_param(){}

    socket_param(const bytes_buffer& path, int attr) : m_ip(path), m_port(-1), m_attr(attr)
    { init_local_param(path); }

    socket_param(const bytes_buffer& ip, short port, int attr) : m_ip(ip), m_port(port), m_attr(attr)
    { init_inet_param(ip, port); }

    socket_param(const socket_param& that)
    {
        m_ip = that.m_ip;
        m_port = that.m_port;
        m_attr = that.m_attr;
        local_param = that.local_param;
        inet_param = that.inet_param;
    }

    socket_param& operator= (const socket_param& that)
    {
        m_ip = that.m_ip;
        m_port = that.m_port;
        m_attr = that.m_attr;
        local_param = that.local_param;
        inet_param = that.inet_param;
    }

    bytes_buffer    m_ip;
    short           m_port;
	int             m_attr;
    socket_param_local  local_param;
    socket_param_inet   inet_param;
};


struct socket_base
{
    socket_base(){}
    ~socket_base(){}

    //init
        //socket
        //bind
        //listen
    virtual int init(socket_param& param) = 0;

    //link
        //server: accept
        //client: connect
    virtual int link(socket_base** client_ptr = nullptr) = 0;

    //send
    virtual int send(const bytes_buffer& send_buffer) = 0;

    //recv
    virtual int recv(const bytes_buffer& recv_buffer) = 0;

    //close
    virtual int close(void) = 0;
};

struct socket_local : public socket_base
{
    socket_param m_local_param;
    int m_local_socket;

    socket_local(){}
};

struct socket_inet : public socket_base
{
    socket_param m_inet_param;
    int m_inet_socket;
    
};


