#include "OptionsParser.h"
#include <iostream>
#include <Philo.h>

void foo( int argc, char** argv )
{
     for ( int i = 0; i < argc; ++i )
     {
          std::cout << argv[i] << std::endl;
     }
}

int main( int argc, char** argv )
{
     // OptionParser op( argc, argv );
     // try
     // {
     //      op.init();
     // }
     // catch( const std::exception &e )
     // {
     //      std::cout << "Exception caught: " << e.what() << std::endl;
     // }

     std::mutex mutex;

     Philo p( mutex );

     p.mutex_.lock();
     p.mutex_.unlock();


     return 0;
}