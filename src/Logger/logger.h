#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <string_view>

/*
   TRACE,
   DEBUG,
   INFO,
   WARN,
   ERROR,
   FATAL
*/

enum class LogLevel {
  kTrace,
  kDebug,
  kInfo,
  kWarn,
  kError,
  kFatal
};

class Logger
{
public:

/* --- +Constructors & Destructors ------------------------------------------ */
  Logger(Logger &other) = delete;

/* --- +Methods ------------------------------------------------------------- */
  static Logger* GetInstance();
  void Error(std::string_view message);
    
/* --- +Operator overloadings ----------------------------------------------- */    
  void operator=(const Logger& other) = delete;
  
    
/* --- +Tools --------------------------------------------------------------- */    



protected:

/* --- #Constructors & Destructors ------------------------------------------ */
  Logger();
  
  
private:
  LogLevel level_;
  std::string message_buffer_;
};

#endif //!LOGGER_H