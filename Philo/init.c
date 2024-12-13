#include "philo.h"

void    data_int(t_thread *philo, t_data *data)
{
    data->flg = 0;
    data->threads = philo;
    pthread_mutex_init(&data->meal, NULL);
    pthread_mutex_init(&data->dead, NULL);
    pthread_mutex_init(&data->writing, NULL);
}

void    fork_init(int num_of_philo, pthread_mutex_t *fork)
{
    int i;
    
    i = 0;
    while (i < num_of_philo)
    {
        pthread_mutex_init(&fork[i], NULL);
        i++;
    }
}

void	in_init(char **argv, t_thread *philo)
{
	philo->philo_num = ft_atoi(argv[1]);
	philo->to_die = ft_atoi(argv[2]);
	philo->to_eat = ft_atoi(argv[3]);
	philo->to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		philo->num_to_eat = ft_atoi(argv[5]);
	else
		philo->num_to_eat = -1;
}

void	init_single_philo(char **argv, t_thread *philo, pthread_mutex_t *fork, int i)
{
	int	num_philos;

	num_philos = ft_atoi(argv[1]);
	philo->id = i + 1;
	philo->is_eating = 0;
	philo->ate_meals = 0;
	in_init(argv, philo);
	philo->start = curr_time();
	philo->last_eat = curr_time();
	philo->left_fork = &fork[i];
	if (i == 0)
		philo->right_fork = &fork[num_philos - 1];
	else
		philo->right_fork = &fork[i - 1];
}

void	philo_init(char **argv, t_thread *philo, pthread_mutex_t *fork, t_data *data)
{
	int	num_philos;
	int	i;

	num_philos = ft_atoi(argv[1]);
	i = 0;
	while (i < num_philos)
	{
		philo[i].lock_writing = &data->writing;
		philo[i].lock_death = &data->dead;
		philo[i].lock_meal = &data->meal;
		philo[i].dead = &data->flg;
		init_single_philo(argv, &philo[i], fork, i);
		i++;
	}
}
