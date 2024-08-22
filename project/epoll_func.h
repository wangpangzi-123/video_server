#pragma once
#include <sys/epoll.h>
#include <vector>
#include <cerrno>
#include <unistd.h>
struct epoll_data
{
	epoll_data() { m_data.u64 = 0; }

	epoll_data(void* ptr) { m_data.ptr = ptr; }

	explicit epoll_data(int fd) { m_data.fd = fd; }

	explicit epoll_data(uint32_t u32) { m_data.u32 = u32; }

	explicit epoll_data(uint64_t u64) { m_data.u64 = u64; }

	epoll_data(const epoll_data& that)
	{
		m_data.fd = that.m_data.fd;
		m_data.ptr = that.m_data.ptr;
		m_data.u64 = that.m_data.u64;
		m_data.u32 = that.m_data.u32;
	}

	epoll_data& operator= (const epoll_data& that)
	{
		if (this != &that)
		{
			m_data.fd = that.m_data.fd;
			m_data.ptr = that.m_data.ptr;
			m_data.u64 = that.m_data.u64;
			m_data.u32 = that.m_data.u32;
		}
		return *this;
	}

	operator epoll_data_t() { return m_data; }
	operator epoll_data_t() const { return m_data; }
	operator epoll_data_t* () { return &m_data; }

	epoll_data_t m_data;
};

struct epoll_helper
{
	using epoll_events = std::vector<epoll_event>;

	epoll_helper() {}

	~epoll_helper() {}

	epoll_helper(const epoll_helper&) = delete;
	epoll_helper& operator= (const epoll_helper&) = delete;

	//epoll_helper(const epoll_helper&& that)
	//{
	//	if (this != &that)
	//	{
	//		
	//	}
	//}

	//epoll_helper& operator= (const epoll_helper&& that)
	//{
	//	if (this != &that)
	//	{

	//	}
	//}


	int create(unsigned count)
	{
		if (m_epoll != -1)
			return -1;
		m_epoll = epoll_create1(0);
		if (m_epoll < 0)
		{
			return -2;
		}
		return 0;
	}

	ssize_t wait_event(epoll_events& events, int timeout = 10)
	{
		
		/*int ret = epoll_wait(m_epoll, )*/
		if (m_epoll == -1)
			return -1;
		ssize_t ret = epoll_wait(m_epoll, events.data(), events.size(), 10);
		if (ret == -1)
		{
			if (errno == EINTR || errno == EAGAIN)
			{
				return 0;
			}
			return -2;
		}
		return ret;
	}


	int add_event(int fd, const epoll_data& data = epoll_data((void*)0), uint32_t events = EPOLLIN)
	{
		if (m_epoll == -1) 
			return -1;
		struct epoll_event ev {events, data};
		int ret = epoll_ctl(m_epoll, EPOLL_CTL_ADD, fd, &ev);
		if (ret == -1)
			return -2;
		return 0;
	}

	int modify_event(int fd, uint32_t events = EPOLLIN, const epoll_data& data = epoll_data((void*)0))
	{
		if (m_epoll == -1)
			return -1;
		struct epoll_event ev { events, data };
		int ret = epoll_ctl(m_epoll, EPOLL_CTL_MOD, fd, &ev);
		if (ret == -1)
			return -2;
		return 0;
	}

	int delete_event(int fd)
	{
		if (m_epoll == -1)
			return -1;
		int ret = epoll_ctl(m_epoll, EPOLL_CTL_DEL, fd, NULL);
		if (ret == -1)
			return -2;
		return 0;
	}

	int close_epoll()
	{
		if (m_epoll != -1)
		{
			int fd = m_epoll;
			m_epoll = -1;
			close(fd);
		}
	}

	int m_epoll = -1;
	
};