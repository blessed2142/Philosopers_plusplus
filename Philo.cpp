#include <Philo.h>
#include <iostream>
#include <thread>

Philo::Philo( const int& own_number,
              const Options& options,
              std::mutex& print_mutex,
              std::mutex& left_fork,
              std::mutex& right_fork ) :
     own_number_( own_number ),
     options_( options ),
     print_mutex_( print_mutex ),
     left_fork_( left_fork ),
     right_fork_( right_fork )
     {
     }

// timestamp X has taken a fork
void Philo::Print( const std::string& message )
{
     std::lock_guard<std::mutex> lg( print_mutex_ );
     std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(
          std::chrono::high_resolution_clock::now() - start_time_ ).count() 
     << " " << own_number_ << " " << message << std::endl;
}

void Philo::Eat()
{
     if ( own_number_ % 2 == 1 )
     {
          std::lock( right_fork_, left_fork_ );
          std::lock_guard<std::mutex>( right_fork_, std::adopt_lock );
          std::lock_guard<std::mutex>( left_fork_, std::adopt_lock );
          Print( "is eating" );
          std::this_thread::sleep_until( std::chrono::round<std::chrono::milliseconds>(
               std::chrono::high_resolution_clock::now() + std::chrono::milliseconds( options_.time_to_eat ) )  );
     }
     else
     {
          std::lock( left_fork_, right_fork_ );
          std::lock_guard<std::mutex>( left_fork_, std::adopt_lock );
          std::lock_guard<std::mutex>( right_fork_, std::adopt_lock );
          Print( "is eating" );
          std::this_thread::sleep_until( std::chrono::round<std::chrono::milliseconds>(
               std::chrono::high_resolution_clock::now() + std::chrono::milliseconds( options_.time_to_eat ) )  );
     }
}

void Philo::SleepThink()
{
     Print( "is sleeping" );
     std::this_thread::sleep_until( std::chrono::round<std::chrono::milliseconds>(
          std::chrono::high_resolution_clock::now() + std::chrono::milliseconds( options_.time_to_sleep ) )  );
     Print( "is thinking" );
}

void Philo::Routine()
{
     Eat();
     SleepThink();
}