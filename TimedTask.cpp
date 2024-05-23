#include <iostream>
#include <chrono>
#include "TimedTask.h"

using namespace std;
namespace seneca
{
	void TimedTask::startClock()
	{
		m_start = chrono::steady_clock::now();
	}

	void TimedTask::stopClock()
	{
		m_end = chrono::steady_clock::now();
	}

	void TimedTask::addTask(const char* task)
	{
		m_task[m_numRecords].taskName = task;
		m_task[m_numRecords].unitsTime = "nanoseconds";
		m_task[m_numRecords].taskDuration = std::chrono::duration_cast<std::chrono::nanoseconds>( m_end - m_start);
		m_numRecords++;
	}

	int TimedTask::getNumRecords() const
	{
		return m_numRecords;
	}

	Task TimedTask::getTask(int i) const
	{
		return m_task[i];
	}

;
	ostream& operator<<(ostream& os, const TimedTask& task)
	{
		os << "--------------------------" << endl;
		os << "Execution Times:" << endl;
		os << "--------------------------" << endl;
		if(task.getNumRecords() != 0)
		{
			for(int i = 0; i < task.getNumRecords(); i++)
			{
				os.setf(ios::left);
				os.width(21);
				os << task.getTask(i).taskName;
				os.unsetf(ios::left);
				os.setf(ios::right);
				os.width(13);
				os << task.getTask(i).taskDuration.count() << " " << task.getTask(i).unitsTime << endl;
				os.unsetf(ios::right);
			}
		}
		os << "--------------------------" << endl;
		return os;
	}
}

