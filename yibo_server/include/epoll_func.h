#pragma once
#include <sys/epoll.h>
#include <vector>
#include <cerrno>
#include <unistd.h>
#include <array>

struct epoll_data_
{
	epoll_data_() { m_data.u64 = 0; }

	epoll_data_(void* ptr) { m_data.ptr = ptr; }

	explicit epoll_data_(int fd) { m_data.fd = fd; }

	explicit epoll_data_(uint32_t u32) { m_data.u32 = u32; }

	explicit epoll_data_(uint64_t u64) { m_data.u64 = u64; }

	epoll_data_(const epoll_data_& that)
	{
		m_data.fd  = that.m_data.fd;
		m_data.ptr = that.m_data.ptr;
		m_data.u64 = that.m_data.u64;
		m_data.u32 = that.m_data.u32;
	}

	epoll_data_& operator= (const epoll_data_& that)
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
	// using epoll_events = std::vector<epoll_event>;
	std::array<epoll_event, 128> epoll_events;

	epoll_helper() {}

	~epoll_helper() {}

	epoll_helper(const epoll_helper&) = delete;
	epoll_helper& operator= (const epoll_helper&) = delete;

	int create(void)
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

	ssize_t wait_event(int timeout = 10)
	{
		/*int ret = epoll_wait(m_epoll, )*/
		if (m_epoll == -1)
			return -1;
		ssize_t ret = epoll_wait(m_epoll, epoll_events.data(), epoll_events.size(), timeout);
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


	int add_event(int fd, const epoll_data_& data = epoll_data_((void*)0), uint32_t events = EPOLLIN)
	{
		if (m_epoll == -1) 
			return -1;
		struct epoll_event ev {events, data};
		int ret = epoll_ctl(m_epoll, EPOLL_CTL_ADD, fd, &ev);
		if (ret == -1)
			return -2;
		return 0;
	}

	int modify_event(int fd, uint32_t events = EPOLLIN, const epoll_data_& data = epoll_data_((void*)0))
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
		return 0;
	}

	int m_epoll = -1;
};