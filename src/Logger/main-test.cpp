#include <cmath>
#include "logger.h"
#include <ctime>
#include <iostream>

bool IsPrimeNumber(int num);

int main()
{
    Logger* logger = Logger::GetInstance();

    for(int i = 1; i <= 10; ++i) {
        std::string message = "number: " + std::to_string(i);
        if(i > 3) logger->SetLevel(LogLevel::kTrace);
        if(IsPrimeNumber(i)) logger->Trace(message); //zrobic moze jak printf (think)
    }


    int a = static_cast<int>(LogLevel::kWarn);

    std::cout << a << std::endl;
    return 0;
}

bool IsPrimeNumber(int num) {
    if (num < 1)
        return false;
 
    for (int i = 2; i <= sqrt(num); i++)
        if (num % i == 0)
            return false;
 
    return true;
}