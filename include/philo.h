#ifndef PHILO_H
# define PHILO_H

typedef struct l_info
{
    int     num_of_philo;
    int     time_to_die;
    int     time_to_eat;
    int     time_to_sleep;
}   t_info;


int var_init(t_info *data, char *argv[]);
#endif