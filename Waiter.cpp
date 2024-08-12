#include <Waiter.h>
#include <algorithm>

Waiter::Waiter( const Options& options ) : options_( options )
{
     std::vector<std::mutex> for_swap( options_.philosophers );

     fork_mutexes_.swap( for_swap );
}

void Waiter::CreatePhilos()
{
     const int first_element = 0;
     int philoNumber = 0;
     for ( int i = 0; i < options_.philosophers; ++i )
     {
          philoNumber = i + 1;
          if ( philoNumber == options_.philosophers )
          {
               philos_.emplace_back( philoNumber, options_, print_mutex_, fork_mutexes_[i], fork_mutexes_[ first_element ] );
               break;
          }
          philos_.emplace_back( philoNumber, options_, print_mutex_, fork_mutexes_[ i ], fork_mutexes_[ i + 1 ] );
     }
}

void Waiter::BeginSumulation()
{
//  std::thread t(&X::do_lengthy_work, &my_x);
     // Сначала "сажаем за стол" нечетных философов
     std::chrono::high_resolution_clock::time_point start_time = std::chrono::high_resolution_clock::now();
     for ( auto& philo : philos_ )
     {
          philo.SetStartTime( start_time );
          if ( philo.GetOwnNumber() % 2 == 1 )
          {
               // threads_.push_back( std::thread( &Philo::Routine, &philo ) );
               threads_.emplace_back( &Philo::Routine, &philo );
          }
     }

     // Затем четных
     for ( auto& philo : philos_ )
     {
          if ( philo.GetOwnNumber() % 2 == 0 )
          {
               // threads_.push_back( std::thread( &Philo::Routine, &philo ) );
               threads_.emplace_back( &Philo::Routine, &philo );
          }
     }
}

// void Waiter::FeedChecker( bool& all_feed, std::vector<Philo>& philos )
void Waiter::FeedChecker( bool& all_feed )
{
     for ( ; ; )
     {
          if ( std::all_of( philos_.begin(), philos_.end(), []( Philo p ){ return p.isFeadUp(); } ) )
          {
               all_feed = true;
               return ;
          }
          std::this_thread::sleep_for( std::chrono::milliseconds( 2 ) );
     }
}

void Waiter::ObserveTable()
{
     int i = 0;
     bool all_feed = false;
     if ( options_.must_eat > 0 )
     {
          std::thread feedThread( &Waiter::FeedChecker, this, std::ref( all_feed ) );
          // std::thread feedThread( FeedChecker, std::ref( all_feed ), std::ref( philos_ ) );
          feedThread.detach();
     }

     while ( !philos_[i].IsDead() && !all_feed )
     {
          if ( i + 1 == options_.philosophers )
          {
               i = 0;
               continue;
          }
          else
          {
               ++i;
          }
          std::this_thread::sleep_for( std::chrono::milliseconds( 1 ) );
     }

     if ( !all_feed )
     {
          for( auto& philo : philos_ )
          {
               philo.Stop();
          }
     
          philos_[i].Print( "died" );
     }
     {
          std::lock_guard<std::timed_mutex> lkt( print_mutex_ );


          for ( auto& thread : threads_ )
          {
               if ( thread.joinable() )
               {
                    thread.join();
               }
          }
     }
}