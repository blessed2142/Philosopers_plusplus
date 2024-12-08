#include "OptionsParser.h"
#include <iostream>
#include <Philo.h>
#include <thread>
#include <ratio>
#include <chrono>
#include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/time.h>

#include <Waiter.h>

int main( int argc, char** argv )
{
     OptionParser opt_parser( argc, argv );
     try
     {
          opt_parser.init();
     }
     catch( const std::exception& e )
     {
          std::cout << "Exception occurred during arg parse: " << e.what() << std::endl;
          return 1;
     }

     Waiter waiter( opt_parser.getOptions() );
     waiter.CreatePhilos();
     waiter.BeginSumulation();
     waiter.ObserveTable();

     return 0;
}

// class A
// {
// public:
//      A( int& i ) : i_( i )
//      {

//      }
//      void doWork( bool& flag )
//      {
//           i_ = 1488;
//           flag = true;
//      }
// private:
//      int& i_;
// };

// int main( int argc, char** argv )
// {
//      int i = 0;
//      bool flag = false;
//      A a( i );
//      std::thread t( &A::doWork, &a, std::ref( flag ) );
//      t.join();

//      std::cout << "Flag: " << std::boolalpha << flag << " int i: " << i << std::endl;
//      return 0;
// }

// int main( int argc, char** argv )
// {
//      // auto start = std::chrono::high_resolution_clock::now();

//      // for ( int i = 1; i < 100; ++i)
//      // {
//      //      auto now = std::chrono::high_resolution_clock::now();

//      //      auto int_ms = std::chrono::duration_cast<std::chrono::milliseconds>( now - start ).count();

//      //      std::cout << int_ms << " ms" << std::endl;
//      //      // now.
//      //      std::this_thread::sleep_until( std::chrono::round<std::chrono::milliseconds>( now + std::chrono::milliseconds( 200 ) )  );
//      //      // ft_usleep( 200 );
//      //      // superSleep( start, std::chrono::milliseconds( 200 * i ) );
//      //      // usleep( 200000 );
//      // }

//      int i = 5;

//      A a( i );
//      std::thread t( &A::DoSum, &a );
//      t.join();

//      std::cout << i << std::endl;

//      std::cout << "qq" << std::endl;

//      return 0;
// }

