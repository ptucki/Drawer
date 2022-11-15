#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <string>

/*
  TO-DO:
  - CPU time measure for Windows.
  - Randomize name in default constructor.
  
  https://levelup.gitconnected.com/8-ways-to-measure-execution-time-in-c-c-48634458d0f9
*/

class Timer {
  using TimePoint = std::chrono::high_resolution_clock::time_point;

public:

  enum class MeasureType {
    kWall,
    kCPU
  };
    
  Timer(std::string name);
  Timer(std::string name, MeasureType type);
  ~Timer();
  
  void Start();
  void Stop();
  
  std::string GetResult() const;
  std::string GetMessage() const;
  
private:

  std::string TypeToString() const;

  std::string name_;
  MeasureType type_;
  TimePoint begin_;
  TimePoint end_;

#ifdef __linux__
  struct timespec begin_linux_;
  struct timespec end_linux_;
#endif
};

#endif // !TIMER_H