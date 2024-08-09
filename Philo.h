#ifndef PHILO_H
#define PHILO_H
#include <mutex>
#include <OptionsParser.h>
#include <chrono>

class Philo
{
public:
     Philo(    const int& own_number,
               const Options& options,
               std::mutex& print_mutex,
               std::mutex& left_fork,
               std::mutex& right_fork );

     void Print( const std::string& message );
     void Eat();
     void SleepThink();
     void Routine();
private:

     int own_number_;
     Options options_;

     std::chrono::high_resolution_clock::time_point start_time_;


     std::mutex& print_mutex_;
     std::mutex& left_fork_;
     std::mutex& right_fork_;

     Philo( const Philo& );
     Philo operator=( const Philo& );
};

#endif
