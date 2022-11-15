#include <iostream>
#include "timer.h"

int main()
{
  double sum = 0;
  double add = 1;
  
  Timer count = Timer("Test", Timer::MeasureType::kCPU);
  
  count.Start();
  
  int iterations = 1000*1000*500;
  
  for(int i = 0; i < iterations; ++i) {
      sum += add;
      add /= 2.0;
  }
  
  count.Stop();
  
  
  std::cout << count.GetMessage() << std::endl;
  
  return 0;
}
