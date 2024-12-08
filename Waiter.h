#ifndef WAITER_H
#define WAITER_H

#include <OptionsParser.h>
#include <vector>
#include <Philo.h>
#include <thread>
#include <deque>

class Waiter
{
public:
     Waiter( const Options& other );

     void CreatePhilos();
     void BeginSumulation();
     void ObserveTable();
     void FeedChecker( bool& all_feed, std::mutex& all_feed_mutex  );
private:
     Options options_;
     std::deque<Philo> philos_;

     // std::mutex print_mutex_;
     std::timed_mutex print_mutex_;
     std::vector<std::mutex> fork_mutexes_;

     std::vector<std::thread> threads_;

     Waiter( const Waiter&);
     Waiter &operator=( const Waiter& );


};

#endif