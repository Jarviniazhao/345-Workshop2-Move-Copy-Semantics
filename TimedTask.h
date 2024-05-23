#ifndef SENECA_TIMEDTASK_H
#define SENECA_TIMEDTASK_H

#include <chrono>
namespace seneca
{
	struct Task
	{
		std::string taskName {};
		std::string unitsTime {};
		std::chrono::steady_clock::duration taskDuration {};
	};

	class TimedTask
	{
		static constexpr int m_maxTasks = 10;
		Task m_task[m_maxTasks] {};
		int m_numRecords {};
		std::chrono::steady_clock::time_point m_start {};
		std::chrono::steady_clock::time_point m_end {};


	public:
		TimedTask(){};
		void startClock();
		void stopClock();
		void addTask(const char*);

		int getNumRecords() const;
		Task getTask(int) const;
		
	};

	std::ostream& operator<<(std::ostream&, const TimedTask&);
}


#endif
