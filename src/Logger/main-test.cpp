#include "logger.h"


bool IsPrimeNumber(int num);

int main()
{
    Logger* logger = Logger::GetInstance();

    for(int i = 1; i <= 10; ++i) {
        if(IsPrimeNumber(i)) logger->Error(); //zrobic moze jak printf (think)
    }

    return 0;
}

bool IsPrimeNumber(int num) {
    if (n <= 1)
        return false;
 
    for (int i = 2; i <= sqrt(n); i++)
        if (n % i == 0)
            return false;
 
    return true;
}