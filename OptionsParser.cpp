#include "OptionsParser.h"
#include <vector>
#include <algorithm>
#include <iostream>

     // int       argc_;
     // char**    argv_;
     // Options   options_;
     // bool      must_eat_set_;

OptionParser::OptionParser( int argc, char** argv ) : argc_( argc ), argv_( argv ), must_eat_set_( false )
{
}

void OptionParser::init()
{
     std::vector<std::string> argvec;

     if ( argc_ != 5 && argc_ != 6 )
     {
          printUsage();
          throw Exception( "Wrong number of args" );
     }

     for ( int i = 1; i < argc_; ++i )
     {
          argvec.push_back( argv_[ i ] );
     }


     for ( auto arg : argvec )
     {
          if ( !std::all_of( arg.begin(), arg.end(), ::isdigit ) )
          {
               printUsage();
               throw Exception( "One of args contain somthing beside digit" );
          }
     }

     options_.philosophers = std::stoi( argvec[0] );
     options_.time_to_die = std::stoi( argvec[1] );
     options_.time_to_eat = std::stoi( argvec[2] );
     options_.time_to_sleep = std::stoi( argvec[3] );
     if ( argc_ == 6 )
     {
          options_.must_eat = std::stoi( argvec[4] );
          must_eat_set_ = true;
     }

     if ( options_.philosophers <= 1 ||
          options_.time_to_die <= 0 ||
          options_.time_to_eat <= 0 ||
          options_.time_to_sleep <= 0 || 
          ( options_.must_eat <= 0 && must_eat_set_ ) )
     {
          printUsage();
          throw Exception( "One of args is below 1" );
     }
}

const Options OptionParser::getOptions() const
{
     return options_;
}

const bool OptionParser::isMustEatSet() const
{
     return must_eat_set_;
}

void OptionParser::printUsage() const
{
     std::cout << "Usage: " << std::endl <<
     "./philosophers [number of philosophers] [time_to_die] [time_to_eat] [time_to_sleep] (optional)[must_eat]"
     << std::endl;
}

//      int philosophers;
//      int time_to_die;
//      int time_to_eat;
//      int time_to_sleep;
//      int must_eat;