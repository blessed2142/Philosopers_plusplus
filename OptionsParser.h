#ifndef OPTION_PARSER_H
#define OPTION_PARSER_H

#include <string.h>
#include <exception>
#include <string>
#include <iostream>

class Exception: public std::exception
{
public:
     Exception( const std::string& message ) : message_( message )
     {}

     virtual ~Exception() noexcept {}
     virtual const char* what() const noexcept
     {
          return message_.c_str();
     }

private:
     std::string message_;
};

struct Options
{
     Options()
     {
          memset( this, 0, sizeof( Options ) );
     }

     int philosophers;
     int time_to_die;
     int time_to_eat;
     int time_to_sleep;
     int must_eat;
};

class OptionParser
{
public:
     OptionParser( int argc, char** argv );
     void init();
     OptionParser( const OptionParser& ) = delete;
     OptionParser operator=( const OptionParser& ) = delete;


     const Options getOptions() const;
     const bool isMustEatSet() const;

     void printUsage() const;

private:
     int       argc_;
     char**    argv_;
     Options   options_;
     bool      must_eat_set_;

};


#endif