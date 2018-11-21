#if !defined(TIMER_CLASS_H)
#define TIMER_CLASS_H 1

#include <chrono>

typedef std::chrono::high_resolution_clock HR_Clock;
typedef std::chrono::milliseconds millisec;
typedef std::chrono::duration<double> raw_duration;

class Timer {
	private:
		HR_Clock::time_point start_time;
		int target_duration;
	public:
		Timer();
		Timer(int target_duration);
		void start(int target_duration);
		bool at_target_duration();
};

#endif