#ifndef PHILO_H
#define PHILO_H
#include <mutex>
#include <OptionsParser.h>


class Philo
{
public:
     Philo(    const int& own_number,
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

private:

     int own_number_;
     Options options_;


     std::mutex& print_mutex_;
     std::mutex& left_fork_;
     std::mutex& right_fork_;
};

#endif
