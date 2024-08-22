#pragma once
#include <functional>
#include <optional>
class process_helper
{
public:
	process_helper() {}

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
			return -2;
		if (pid == 0)
		{
			printf("m_pid = %d\r\n", pid);
			return run_bind_func();
		}
		
		m_pid = pid;
		printf("m_pid = %d\r\n", pid);
		return 0;
	}


private:
	std::function<int(void)> m_binder;
	pid_t m_pid;
};
