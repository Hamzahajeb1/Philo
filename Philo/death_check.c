#include "philo.h"

int	all_ate(t_thread *philo)
{
	int	i;
	int	done;

	done = 0;
	i = 0;
	if (-1 == philo[0].num_to_eat)
		return (0);
	while (i < philo[0].philo_num)
	{
		pthread_mutex_lock(philo[i].lock_meal);
		if (philo[i].num_to_eat <= philo[i].ate_meals)
			done++;
		pthread_mutex_unlock(philo[i].lock_meal);
		i++;
	}
	if (done == philo[0].philo_num)
	{
		pthread_mutex_lock(philo[0].lock_death);
		*philo->dead = 1;
		pthread_mutex_unlock(philo[0].lock_death);
		return (1);
	}

	return (0);
}


int	dead_lock(t_thread *philo)
{
    pthread_mutex_lock(philo->lock_death);
    if (1 == *philo->dead)
    {
        pthread_mutex_unlock(philo->lock_death);
        return (1);
    }
    pthread_mutex_unlock(philo->lock_death);
    return (0);
}

int	is_dead(t_thread *philo, size_t to_die)
{
	pthread_mutex_lock(philo->lock_meal);
	if (0 == philo->is_eating && philo->last_eat - curr_time() >= to_die)
	{
		pthread_mutex_unlock(philo->lock_meal);
		return (1);
	}
	pthread_mutex_unlock(philo->lock_meal);
	return (0);
}

int check_philo(t_thread *philo)
{
    if (is_dead(philo, philo->to_die))
    {
        msg_printing(philo, philo->id, "dead");
        pthread_mutex_lock(philo->lock_death);
        *philo->dead = 1;
        pthread_mutex_unlock(philo->lock_death);
        return (1);
    }
    return (0);
}

int if_dead(t_thread *philo)
{
    int i;

    i = 0;
    while (i < philo[0].philo_num)
    {
        if (check_philo(&philo[i]))
            return (1);
        i++;
    }
    return (0);
}