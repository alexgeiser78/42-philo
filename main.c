# include "philo.h"

void	go(t_info data)
{
int i;

i = -1;
	while (++i < data.num_of_philo)
	{

    pthread_create(&data.philo[i].thread, NULL, \
				&philo_life, &(data.philo[i]));
	}
}
//pthread_create(pthread_t *thread, const pthread_attr_t *attr,
//    void *(*start_routine)(void*), void *arg);

//pthread_create() create a new thread, with attributes specified by attr
//If attr is NULL, the default attributes are used. 
//If the attributes specified by attr are modified later, the thread's attributes 
//are not affected. Upon successful completion, pthread_create() stores the ID of 
//the created thread in the location referenced by thread.

//start_routine with arg as its sole argument. If the start_routine returns, 
//the effect is as if there was an implicit call to pthread_exit() 
//using the return value of start_routine as the exit status. Note that 
//the thread in which main() was originally invoked differs from this. 
//When it returns from main(), the effect is as if there was an implicit 
//call to exit() using the return value of main() as the exit status.

//The signal state of the new thread is initialised as follows:
//The signal mask is inherited from the creating thread.
//The set of signals pending for the new thread is empty.
//If pthread_create() fails, no new thread is created and the contents of the 
//location referenced by thread are undefined. 

 //RETURN VALUE

//If successful, the pthread_create() function returns zero. 
//Otherwise, an error number is returned to indicate the error. 




int	main(int argc, char *argv[]) 
{
	t_info	data;

	if (argc != 5)
		return (0);
	var_init(&data, argv);
	go(data);

	return 0;
}