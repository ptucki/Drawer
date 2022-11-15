#include <iostream>
#include <functional>

#ifdef __linux__
#include <time.h>
#endif

#include "timer.h"

Timer::Timer(std::string name) : 
    type_{ MeasureType::kWall },
    name_{ name },
    begin_{ time_point<high_resolution_clock>::min() },
    end_{ time_point<high_resolution_clock>::min() }
{
#ifdef _WIN64
    std::cout << "WINDOWS" << std::endl;
#endif

#ifdef __unix__
    std::cout << "UNIX" << std::endl;
#endif

#ifdef __linux__
    std::cout << "LINUX" << std::endl;
#endif
}

Timer::Timer(std::string name, MeasureType type) :
    type_{ type },
    name_{ name },
    begin_{ time_point<high_resolution_clock>::min() },
    end_{ time_point<high_resolution_clock>::min() }
{
#ifdef _WIN64
    std::cout << "WINDOWS" << std::endl;
#endif

#ifdef __unix__
    std::cout << "UNIX" << std::endl;
#endif

#ifdef __linux__
    std::cout << "LINUX" << std::endl;
#endif
}

Timer::~Timer() {
    this->Stop();
    //Log message
}

void Timer::Start() {
  using namespace std::chrono;
  
  std::function<void()> start_method = [&](){};
  
  // Set measure method according to type and system
  switch(type_) {
    // Valid for both WINDOWS and LINUX  
    case MeasureType::kWall:
      start_method = [&]() {
        begin_ = high_resolution_clock::now();
      };
      break;
    
    case MeasureType::kCPU:
#ifdef __linux__
      start_method = [&]() {
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin_linux_);
      };
      break; //Overflow intended if not LINUX
#endif
      
    default:
      start_method = [&]() {
        begin_ = time_point<high_resolution_clock>::max();
      };
      break;
  }
  // Set begin time point;
  start_method();
}

void Timer::Stop() {
  using namespace std::chrono;
  
  std::function<void()> stop_method;
  
  // Set measure method according to type and system
  switch(type_) {
    // Valid for both WINDOWS and LINUX
    case MeasureType::kWall:
      stop_method = [&]() {
        end_ = high_resolution_clock::now();
      };
      break;
    
    case MeasureType::kCPU:
#ifdef __linux__
      stop_method = [&]() {
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end_linux_);
      };
      break;  //Overflow intended if not LINUX
#endif
      
    default:
      stop_method = [&]() {
          end_ = time_point<high_resolution_clock>::max();
      };
      break;
  }
  // Set end time point;
  stop_method();
  
#ifdef __linux__
  // Cast nanoseconds in long to std::chrono::nanoseconds
  if(type_ == MeasureType::kCPU){
    nanoseconds begin_nano(begin_linux_.tv_nsec);
    nanoseconds end_nano(end_linux_.tv_nsec);
  
    begin_ = time_point<high_resolution_clock>(begin_nano);
    end_ = time_point<high_resolution_clock>(end_nano);
  }
#endif
}

std::string Timer::GetResult() const {
  using namespace std::chrono;
  auto elapsed = duration_cast<nanoseconds>(end_ - begin_).count();
  return std::to_string(elapsed);
}

std::string Timer::GetMessage() const {
  using namespace std::chrono;    
  auto elapsed = duration_cast<nanoseconds>(end_ - begin_).count();
  
  return std::string(
      name_ + "[" + TypeToString() + "]: " + std::to_string(elapsed)
  );
}

std::string Timer::TypeToString() const {
  std::string type_str;
  
  switch(type_) {
    case MeasureType::kWall:
      type_str = "Wall time";
      break;
    case MeasureType::kCPU:
      type_str = "CPU time";
      break;
    default:
      type_str = "Undefined";
      break;
  }
  
  return type_str;
}
