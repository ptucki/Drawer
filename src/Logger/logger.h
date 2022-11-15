#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <string_view>

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
  static void Trace(std::string_view message);
  static void Debug(std::string_view message);
  static void Info(std::string_view message);
  static void Warn(std::string_view message);
  static void Error(std::string_view message);
  static void Fatal(std::string_view message);
  
  void SetLevel(LogLevel level);
    
/* --- +Operator overloadings ----------------------------------------------- */    
  void operator=(const Logger& other) = delete;
  
    
/* --- +Tools --------------------------------------------------------------- */    
    
protected:

/* --- #Constructors & Destructors ------------------------------------------ */
  Logger();
  
  
private:

/* --- -Methods ------------------------------------------------------------- */
  static std::string GetDate();
  static std::string LevelToString(LogLevel level);
  
  bool LevelHigherOrEqual(LogLevel level);
  bool LevelLowerOrEqual(LogLevel level);

  LogLevel level_;
  std::string message_buffer_;
};

#endif //!LOGGER_H