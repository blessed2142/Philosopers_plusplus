#include <Philo.h>
#include <iostream>
#include <thread>

Philo::Philo( const int& own_number,
              const Options& options,
          //     std::mutex& print_mutex,
              std::timed_mutex& print_mutex,
              std::mutex& left_fork,
              std::mutex& right_fork ) :
     own_number_( own_number ),
     options_( options ),
     eated_( 0 ),
     feed_up_( false ),
     philo_work_( true ),
     print_mutex_( print_mutex ),
     left_fork_( left_fork ),
     right_fork_( right_fork )
     {
     }

// timestamp X has taken a fork
void Philo::Print( const std::string& message )
{
     // std::lock_guard<std::mutex> lg( print_mutex_ );
     if ( print_mutex_.try_lock_for( std::chrono::milliseconds( options_.time_to_die ) ) )
     {
          std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(
               std::chrono::high_resolution_clock::now() - start_time_ ).count() 
          << " " << own_number_ << " " << message << std::endl;
          print_mutex_.unlock();
     }
}

void Philo::Eat()
{
     if ( !philo_work_ )
     {
          return ;
     }
     
     if ( own_number_ % 2 == 1 )
     {
          std::lock( right_fork_, left_fork_ );
          std::lock_guard<std::mutex> lk1( right_fork_, std::adopt_lock );
          std::lock_guard<std::mutex> lk2( left_fork_, std::adopt_lock );
          Print( "has taken a fork" );
          Print( "is eating" );
          last_meal_ = std::chrono::high_resolution_clock::now();
          std::this_thread::sleep_until( std::chrono::round<std::chrono::milliseconds>(
               std::chrono::high_resolution_clock::now() + std::chrono::milliseconds( options_.time_to_eat ) )  );
          ++eated_;
          if ( eated_ == options_.must_eat )
          {
               Stop();
               feed_up_ = true;
          }
     }
     else
     {
          std::lock( left_fork_, right_fork_ );
          std::lock_guard<std::mutex> lk1( left_fork_, std::adopt_lock );
          std::lock_guard<std::mutex> lk2( right_fork_, std::adopt_lock );
          Print( "has taken a fork" );
          Print( "is eating" );
          last_meal_ = std::chrono::high_resolution_clock::now();
          std::this_thread::sleep_until( std::chrono::round<std::chrono::milliseconds>(
               std::chrono::high_resolution_clock::now() + std::chrono::milliseconds( options_.time_to_eat ) )  );
          ++eated_;
          if ( eated_ == options_.must_eat )
          {
               Stop();
               feed_up_ = true;
          }
     }
}

void Philo::SleepThink()
{
     if ( !philo_work_ )
     {
          return ;
     }

     Print( "is sleeping" );
     std::this_thread::sleep_until( std::chrono::round<std::chrono::milliseconds>(
          std::chrono::high_resolution_clock::now() + std::chrono::milliseconds( options_.time_to_sleep ) )  );
     Print( "is thinking" );
}

void Philo::Routine()
{
     for ( ; philo_work_ ; )
     {
          Eat();
          SleepThink();
     }
}

bool Philo::IsDead()
{
     return last_meal_ + std::chrono::milliseconds( options_.time_to_die ) < 
     std::chrono::high_resolution_clock::now();
}

void Philo::SetStartTime( const std::chrono::high_resolution_clock::time_point& start_time )
{
     start_time_ =  start_time;
     last_meal_ = start_time;
}

int Philo::GetOwnNumber() const
{
     return own_number_;
}

void Philo::Stop()
{
     philo_work_ = false;
}

bool Philo::isFeadUp() const
{
     return feed_up_;
}