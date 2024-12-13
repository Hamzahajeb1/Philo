#include "philo.h"

void	msg_printing(t_thread *philo, int philosopher_id, char *str)
{
	size_t	curr;

	pthread_mutex_lock(philo->lock_writing);
	curr = curr_time() - philo->start;
	if (dead_loop(philo) == NULL)
		printf("%zu %d %s\n", curr, philosopher_id, str);
	pthread_mutex_unlock(philo->lock_writing);
}


size_t	curr_time()
{
    struct timespec ts;

    if (-1 == clock_gettime(CLOCK_REALTIME, &ts))
    {
        write(2, "Error in getting time\n", 23);
        exit(EXIT_FAILURE);
    }
    return (ts.tv_sec * 1000) + (ts.tv_nsec / 1000000);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	check_args_data(const char *argv)
{
    int i;
    
    i = 0;
    while (argv[i] != '\0')
    {
        if (!ft_isdigit(argv[i]))
            return (1);
        i++;
    }
    return (0);
}

int if_args_valid(char **argv)
{
	if (MAX_PHILO < (argv[1]) || 0 >= ft_atoi(argv[1])
		|| 1 == check_args_data(argv[1]))
		return (write(2, "Invalid philo number\n", 22), 1);
	if (0 >= ft_atoi(argv[2])|| 1 == check_args_data(argv[2]))
		return (write(2, "Invalid time to die\n", 21), 1);
	if (0 >= ft_atoi(argv[3]) || 1 == check_args_data(argv[3]))
		return (write(2, "Invalid time to eat\n", 21), 1);
	if (0 >= ft_atoi(argv[4]) || 1 == check_args_data(argv[4]))
		return (write(2, "Invalid time to sleep\n", 23), 1);
	if (argv[5] && 0 > (ft_atoi(argv[5]) || 1 == check_args_data(argv[5])))
		return (write(2, "Invalid number of times philo should eat\n",
				42), 1);
	return (0);
}
