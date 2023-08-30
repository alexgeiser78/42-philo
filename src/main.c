#include "../include/philo.h"

int main(int argc, char *argv[]) 
{
    t_info data;

    if (argc != 5)
        return (0);
    var_init(&data, argv);
    return 0;
}