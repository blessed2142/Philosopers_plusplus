#ifndef PHILO_H
#define PHILO_H
#include <mutex>
#include <OptionsParser.h>
#include <chrono>
#include <shared_mutex>

class Philo
{
public:
     Philo(    const int& own_number,
               const Options& options,
               // std::mutex& print_mutex,
               std::timed_mutex& print_mutex,
               std::mutex& left_fork,
               std::mutex& right_fork );

     void Print( const std::string& message );
     void Routine();
     bool IsDead();
     void SetStartTime( const std::chrono::high_resolution_clock::time_point& start_time );
     int  GetOwnNumber() const;
     void Stop();
     bool isFeadUp();

     Philo( const Philo& ) = delete;
     Philo &operator=( const Philo& ) = delete;
     Philo( Philo&& ) = delete;
     Philo &operator=( Philo&& ) = delete;
private:

     int       own_number_;
     Options   options_;
     int       eated_;
     bool      feed_up_;
     bool      philo_work_;

     std::chrono::high_resolution_clock::time_point start_time_;
     std::chrono::high_resolution_clock::time_point last_meal_;


     // std::mutex& print_mutex_;
     std::timed_mutex& print_mutex_;
     std::mutex& left_fork_;
     std::mutex& right_fork_;
     
     std::shared_mutex last_meal_mutex_;
     std::shared_mutex philo_work_mutex_;
     std::shared_mutex feed_up_mutex_;


     void Eat();
     void SleepThink();
};

#endif
