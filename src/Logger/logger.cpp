#include "logger.h"
#include <iostream>
#include <ctime>

Logger* Logger::GetInstance()
{
  static Logger* instance = new Logger();

  return instance;
}

void Logger::Trace(std::string_view message){
    LogLevel level = LogLevel::kTrace;
    if(GetInstance()->LevelLowerOrEqual(level))
    std::cout << "[" << LevelToString(level) << "] "
              << GetDate() << " - " << message << "\n";    
}

void Logger::Debug(std::string_view message){
    std::cout << "[" << LevelToString(LogLevel::kDebug) << "] "
              << GetDate() << " - " << message << "\n";    
}

void Logger::Info(std::string_view message){
    std::cout << "[" << LevelToString(LogLevel::kInfo) << "] "
              << GetDate() << " - " << message << "\n";    
}

void Logger::Warn(std::string_view message){
    std::cout << "[" << LevelToString(LogLevel::kWarn) << "] "
              << GetDate() << " - " << message << "\n";    
}

void Logger::Error(std::string_view message){
    std::cout << "[" << LevelToString(LogLevel::kError) << "] "
              << GetDate() << " - " << message << "\n";    
}

void Logger::Fatal(std::string_view message){
    std::cout << "[" << LevelToString(LogLevel::kFatal) << "] "
              << GetDate() << " - " << message << "\n";    
}



Logger::Logger() : level_{ LogLevel::kInfo }, message_buffer_{ "" } {
  std::cout << "Succes Logger created!" << std::endl;
}


void Logger::SetLevel(LogLevel level) {
    level_ = level;
}


bool Logger::LevelHigherOrEqual(LogLevel level) {
    bool ret_b{ false };
    if(static_cast<int>(level_) >= static_cast<int>(level)) ret_b = true;
    
    return ret_b;
}

bool Logger::LevelLowerOrEqual(LogLevel level) {
    bool ret_b{ false };
    if(static_cast<int>(level_) <= static_cast<int>(level)) ret_b = true;
    
    return ret_b;
}


std::string Logger::GetDate() {
  std::string date;
  date.reserve(21);
    
  auto now = time(0);
  tm* now_local = localtime(&now);
  
  int dateParts[] = {
    now_local->tm_year + 1900,  // Year
    now_local->tm_mon,          // Month
    now_local->tm_mday,         // Day of a month
    now_local->tm_hour,         // Hour
    now_local->tm_min,          // Minute
    now_local->tm_sec,          // Second
  };
  
  char buffer[4];
  for(int i = 0; i < sizeof(dateParts) / sizeof(int); ++i) {
    if(i == 0){
      std::sprintf(buffer, "%d", dateParts[i]);    
    } else {
      std::sprintf(buffer, "%02d", dateParts[i]);    
    }
    date += buffer;
    if(i <= 1) date += '/';
    else if(i == 2) date += ' ';
    else if(i < sizeof(dateParts) / sizeof(int) - 1) date += ':';
    
  }
  
  return date;
}

std::string Logger::LevelToString(LogLevel level) {
  std::string ret_str{ "" };
  
  switch(level) {
    case LogLevel::kTrace:
      ret_str = "TRACE";
      break;
    
    case LogLevel::kDebug:
      ret_str = "DEBUG";
      break;
    
    case LogLevel::kInfo:
      ret_str = "INFO";
      break;
    
    case LogLevel::kWarn:
      ret_str = "WARN";
      break;
    
    case LogLevel::kError:
      ret_str = "ERROR";
      break;
    
    case LogLevel::kFatal:
      ret_str = "FATAL";
      break;
    
    default:
      ret_str = "UNDEF";
      break;
  }
  
  return ret_str;
}