#pragma once
#include <string.h>
#include <errno.h>
// #include <stdio.h>
#include <iostream>

// int check_error(const char* msg, int res)
// {
//     if(res < 0)
//     {
//         std::cout << msg << "  error: " << strerror(errno) << std::endl;
//     }
//     return res;
// }

// #define CHECK_ERROR(func, ...) check_error(#func, func(__VA_ARGS__))


#define SOURCE_INFO_IMPL_2(file, line) "In " file ":" #line ": "
#define SOURCE_INFO_IMPL(file, line) SOURCE_INFO_IMPL_2(file, line)
#define SOURCE_INFO(...) SOURCE_INFO_IMPL(__FILE__, __LINE__) __VA_ARGS__
#define CHECK_ERROR(func, ...) check_error(SOURCE_INFO(#func), func(__VA_ARGS__))

int check_error(const char* source, int result);


	// struct MSG_HDR
	// {
	// 	// struct MSG_HDR_HELPER
	// 	// {
	// 	// 	struct msghdr message;
	// 	// 	struct cmsghdr* control_message = NULL;
	// 	// 	std::vector<char> buffer;
	// 	// 	std::vector<char> control_buffer;
	// 	// };

	// 	explicit MSG_HDR(char* buffer, const size_t control_buffer_size)
	// 	{
	// 		m_buffer.assign(buffer, buffer + strlen(buffer));
	// 		iov.iov_base = m_buffer.data();
	// 		iov.iov_len = m_buffer.size();

	// 		memset(&message, 0, sizeof(message));
	// 		message.msg_name = NULL;
	// 		message.msg_namelen = 0;
	// 		message.msg_iov = &iov;
	// 		message.msg_iovlen = 1;
			
	// 		m_control_buffer.resize(CMSG_SPACE(control_buffer_size));
	// 		message.msg_control = m_control_buffer.data();
	// 		message.msg_controllen = m_control_buffer.size();
			
	// 		control_message = CMSG_FIRSTHDR(&message);
	// 		control_message->cmsg_level = SOL_SOCKET;
	// 		control_message->cmsg_type = SCM_RIGHTS;

	// 		// //sender init
	// 		// memset(&m_msg_sender.message, 0, sizeof(m_msg_sender.message));
	// 		// m_msg_sender.message.msg_name = NULL;
	// 		// m_msg_sender.message.msg_namelen = 0;

	// 		// //sender iover init
	// 		// struct iovec  iov_sender;
	// 		// m_msg_sender.buffer.assign(buffer, buffer + strlen(buffer));
	// 		// iov_sender.iov_base = m_msg_sender.buffer.data();
	// 		// iov_sender.iov_len = m_msg_sender.buffer.size();

	// 		// m_msg_sender.message.msg_iov = &iov_sender;
	// 		// m_msg_sender.message.msg_iovlen = 1;
			

	// 	}

	// 	int msghdr_send_fd(int send_socket, int* fd_val, size_t fd_size)
	// 	{
	// 		control_message->cmsg_len = CMSG_LEN(fd_size);
	// 		int* CMSG_DATA_PTR = (int *)CMSG_DATA(control_message);
	// 		CMSG_DATA_PTR = fd_val;

	// 		int send_ret = sendmsg(send_socket, &message, 0);

	// 		if(send_ret < 0){ std::cout << "send msg failed = " << strerror(errno) << std::endl; }
	// 		else{ std::cout << "sendmsg ret = " << send_ret << std::endl; }

	// 		return send_ret;
	// 	}

	// 	int msghdr_recv_fd(int recv_socket, const size_t buffer_size)
	// 	{
			
	// 	}

	// 	struct msghdr message;
	// 	struct cmsghdr* control_message = NULL;
	// 	std::vector<char> buffer;
	// 	std::vector<char> control_buffer;
	// 	// MSG_HDR_HELPER m_msg_sender;
	// 	// MSG_HDR_HELPER m_msg_recver;
	// };