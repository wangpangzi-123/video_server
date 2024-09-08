#pragma once
#include <fcntl.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string>
#include <iostream>
#include <memory>
#include <unistd.h>

struct bytes_buffer : public std::string
{
    bytes_buffer() : std::string() {}
	bytes_buffer(const char* data) : std::string(data){}
	bytes_buffer(size_t size) : std::string(size, '\0') {}
	
	operator char* () { return (char*)c_str(); }
	operator char* () const { return (char*)c_str(); }
	operator const char* () const { return c_str(); }
};

enum socket_attr_ {
	SOCK_IS_SERVER_ = 1,	//
	SOCK_IS_NONBLOCK_ = 2,
	SOCK_IS_UDP_	= 4,
	SOCK_IS_IP_  = 8,
};

/*
    socket_param_ 参数：
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

struct socket_param_
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
            memset(addr_un.sun_path, 0, sizeof(addr_un.sun_path));
            strcpy(addr_un.sun_path, that.addr_un.sun_path);
            addr_un.sun_family = that.addr_un.sun_family;
            return *this;
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
        socket_param_inet(const socket_param_inet& that)
        {
            addr_in.sin_addr.s_addr = that.addr_in.sin_addr.s_addr;
            addr_in.sin_port = that.addr_in.sin_port;
            addr_in.sin_family = that.addr_in.sin_family;
        }

        socket_param_inet& operator= (const socket_param_inet& that)
        {
            addr_in.sin_addr.s_addr = that.addr_in.sin_addr.s_addr;
            addr_in.sin_port = that.addr_in.sin_port;
            addr_in.sin_family = that.addr_in.sin_family;
            return *this;
        }

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

    socket_param_() : m_ip(""), m_port(-1), m_attr(0){}

    ~socket_param_(){}

    socket_param_(const bytes_buffer& path, int attr) : m_ip(path), m_port(-1), m_attr(attr)
    { init_local_param(path); }

    socket_param_(const bytes_buffer& ip, short port, int attr) : m_ip(ip), m_port(port), m_attr(attr)
    { init_inet_param(ip, port); }

    socket_param_(const socket_param_& that)
    {
        m_ip = that.m_ip;
        m_port = that.m_port;
        m_attr = that.m_attr;
        local_param = that.local_param;
        inet_param = that.inet_param;
    }

    socket_param_& operator= (const socket_param_& that)
    {
        m_ip = that.m_ip;
        m_port = that.m_port;
        m_attr = that.m_attr;

        local_param = that.local_param;
        inet_param = that.inet_param;

        return *this;
    }

    bytes_buffer    m_ip;
    short           m_port;
	int             m_attr;
    socket_param_local  local_param;
    socket_param_inet   inet_param;
};


struct socket_base_
{
    // socket_param_ m_param;
    // int m_socket;
    socket_base_() {}
    // socket_base_(int socket) : m_socket(socket){}
    virtual ~socket_base_(){}

    int base_init(int& socket_, socket_param_& param_)
    {
std::cout << "base _init \r\n";
        //1、确定 socket 类型（报文/流式）
        int ret = 0;
        int type = (param_.m_attr & SOCK_IS_UDP_) ? SOCK_DGRAM : SOCK_STREAM;

        if(param_.m_attr & SOCK_IS_IP_){ 
            socket_ = socket(PF_INET, type, 0);
std::cout << __LINE__ <<"socket!\r\n";
if(socket_ == -1){ std::cout << __FILE__<< " (" << __LINE__ << ") : " << socket_ <<"\r\n"; return -1;}
            }
        else{ 
            socket_ = socket(PF_LOCAL, type, 0); 
std::cout << __LINE__ <<"socket!\r\n";
if(socket_ == -1){ std::cout << __FILE__<< " (" << __LINE__ << ") : " << socket_ <<"\r\n"; return -1;}
            }

        //2、设置 socket 类型 (阻塞/非阻塞)
        if(param_.m_attr & SOCK_IS_NONBLOCK_)
        {
std::cout << __LINE__ <<"socket!\r\n";
            int option = fcntl(socket_, F_GETFL);
if(socket_ == -1){ std::cout << __FILE__<< " (" << __LINE__ << ") : " << option <<"\r\n"; return -2;}
            option |= O_NONBLOCK;
            ret = fcntl(socket_, F_SETFL, option);
if(ret == -1){ std::cout << __FILE__<< " (" << __LINE__ << ") : " << ret <<"\r\n"; return -3;}
        }

        //3、bind socket
        if(param_.m_attr & SOCK_IS_IP_){
 std::cout << "123\r\n";
            ret = bind(socket_, param_.get_in_address(), sizeof(sockaddr_in)); 
            if(ret == -1){ std::cout << __FILE__<< " (" << __LINE__ << ") : " << ret <<"\r\n"; return -4;}
        }
        else{ 
            ret = bind(socket_, param_.get_un_address(), sizeof(sockaddr_un));
if(ret == -1){ std::cout << __FILE__<< " (" << __LINE__ << ") : " << strerror(errno) <<"\r\n"; return -4;}
            }

std::cout << "111111111111111\r\n";
        //4、listen
        ret = listen(socket_, 32);
if(ret == -1){ std::cout << __FILE__<< " (" << __LINE__ << ") : " << ret <<"\r\n"; return -5;}
        return 0;
    }


    //如果 为 SERVER_SOCKET , 返回 accept 后的 fd
    //如果 为 CLIENT_SOCKET , 直接 connect
    int base_link(int& socket_, socket_param_& param_, int* fd_ = nullptr, socket_param_* client_param_ = nullptr)
    {
        int ret = 0;
        if(socket_ == -1) return -1;
if(socket_ == -1){ std::cout << "not init socket!\r\n"; }
        if(param_.m_attr & SOCK_IS_SERVER_)
        {
            // socket_param_ client_param;
            int client_fd = -1;
            socklen_t len = 0;
            if(param_.m_attr & SOCK_IS_IP_)
            {
                (*client_param_).m_attr |= SOCK_IS_IP_;
                len = sizeof(sockaddr_in);
                client_fd = accept(socket_, (*client_param_).get_in_address(), &len);
            }
            else
            {
                len = sizeof(sockaddr_un);
                client_fd = accept(socket_, (*client_param_).get_un_address(), &len);
            }
            *fd_ = client_fd;
        }
        else
        {
            if(param_.m_attr & SOCK_IS_IP_)
            {
                ret = connect(socket_, param_.get_in_address(), sizeof(sockaddr_in));
            }
            else
            {
                ret = connect(socket_, param_.get_un_address(), sizeof(sockaddr_un));
            }
            if(ret != 0) return -2;
        }
        return 0;
    }

    virtual ssize_t base_send(int& socket_, const bytes_buffer& send_buffer)
    {
        if(socket_ == -1) return -1;
        ssize_t alread_send_size = 0;
        ssize_t total_send_size = send_buffer.size();
        while(alread_send_size < total_send_size)
        {
            ssize_t index = write(socket_, (char*)send_buffer + alread_send_size, total_send_size - alread_send_size);
            if(index == 0) return -2;
            if(index < 0) return -3;
            alread_send_size += index;
        }
        return alread_send_size;
    }

    virtual ssize_t base_recv(int& socket_, const bytes_buffer& recv_buffer)
    {
        if(socket_ == -1) return -1;
        ssize_t recv_index = read(socket_, (char*)recv_buffer, sizeof(recv_buffer));
        return recv_index;
    }


    //init
        //socket
        //bind
        //listen
    virtual int init(socket_param_& param) = 0;

    //link
        //server: accept
        //client: connect
    // virtual int link(socket_base_** client_ptr = nullptr) = 0;
    virtual int link(std::unique_ptr<socket_base_>* client_ptr = nullptr) = 0;


    //send
    virtual ssize_t send(const bytes_buffer& send_buffer) = 0;

    //recv
    virtual ssize_t recv(const bytes_buffer& recv_buffer) = 0;

    //close
    virtual int close(void) = 0;
};

struct socket_local : public socket_base_
{
    socket_param_ m_local_param;
    int m_local_socket;

    // socket_local(const bytes_buffer& path) : 
    socket_local(int socket_) : m_local_socket(socket_){}

    virtual ~socket_local(){}
    socket_local(const socket_local& that){}
    socket_local& operator=(const socket_local& that) {}

    //init
        //socket
        //bind
        //listen
    virtual int init(socket_param_& param){ 
        // m_local_param = param;
        base_init(m_local_socket, m_local_param); }

    virtual int link(std::unique_ptr<socket_base_>* client_ptr = nullptr)
    {
        int ret = 0;
        if(m_local_param.m_attr & SOCK_IS_SERVER_)
        {
            int client_fd = -1;
            socket_param_ client_socket_param;
            ret = base_link(m_local_socket, m_local_param, &client_fd, &client_socket_param);
            if (client_fd > 0) {
                auto temp_ptr = std::make_unique<socket_local>(client_fd);
                ret = temp_ptr->init(client_socket_param);
                if (ret != 0) {
                    return -1;
                }
                if (client_ptr) {
                    *client_ptr = std::move(temp_ptr);
                }
            }
        }
        else
        {
            base_link(m_local_socket, m_local_param);
        }
        return ret;
    }


    virtual ssize_t send(const bytes_buffer& send_buffer){ return base_send(m_local_socket, send_buffer); }

    virtual ssize_t recv(const bytes_buffer& recv_buffer){ return base_recv(m_local_socket, recv_buffer); }


    virtual int close(void)
    {
        if(m_local_param.m_attr & SOCK_IS_SERVER_)
        {
            unlink(m_local_param.m_ip);
        }
        int fd = m_local_socket;
        m_local_socket = -1;
        ::close(fd);
    }

};

struct socket_inet : public socket_base_
{
    socket_param_ m_inet_param;
    int m_inet_socket;
    
    socket_inet() : socket_base_(), m_inet_socket(-1) {}
    socket_inet(int socket_) : m_inet_socket(socket_){}
    virtual ~socket_inet(){}
    socket_inet(const socket_inet& that){}
    socket_inet& operator=(const socket_inet& that) {}


    virtual int init(socket_param_& param){ 
        m_inet_param = param;
        int rtn = base_init(m_inet_socket, m_inet_param); 
        return rtn;
        }

    virtual int link(std::unique_ptr<socket_base_>* client_ptr = nullptr)
    {
        int ret = 0;
        if(m_inet_param.m_attr & SOCK_IS_SERVER_)
        {
            int client_fd = -1;
            socket_param_ client_socket_param;
            ret = base_link(m_inet_socket, m_inet_param, &client_fd, &client_socket_param);
            if (client_fd > 0) {
                auto temp_ptr = std::make_unique<socket_inet>(client_fd);
                ret = temp_ptr->init(client_socket_param);
                if (ret != 0) {
                    return -1;
                }
                if (client_ptr) {
                    *client_ptr = std::move(temp_ptr);
                }
            }
        }
        else
        {
            base_link(m_inet_socket, m_inet_param);
        }
        return ret;
    }

    virtual ssize_t send(const bytes_buffer& send_buffer){ return base_send(m_inet_socket, send_buffer); }

    virtual ssize_t recv(const bytes_buffer& recv_buffer){ return base_recv(m_inet_socket, recv_buffer); }


    virtual int close(void)
    {
        int fd = m_inet_socket;
        m_inet_socket = -1;
        ::close(fd);
    }
};


