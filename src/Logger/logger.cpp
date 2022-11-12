#include "logger.h"
#include <iostream>

Logger* Logger::GetInstance()
{
  static Logger* instance = new Logger();

  return instance;
}


void Error(std::string_view){
  std::cout << "[ Error ]: " << message << " ;\n";
}


Logger::Logger() : log_level{ LogLevel::kInfo }, message_buffer{ "" } {
  std::cout << "Succes Logger created!" << std::endl;
}