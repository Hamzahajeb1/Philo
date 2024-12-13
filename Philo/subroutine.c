#include "philo.h"

int ft_sleep(size_t ms)
{
    size_t  i;
    
    i = curr_time();
    while (ms > (curr_time() - i))
        usleep(300);
    return (0);
}

void    is_eating(t_thread *philo)
{
    pthread_mutex_lock(philo->right_fork);
    msg_printing(philo, philo->id, "take a fork");
    if (1 == philo->philo_num)
    {
        ft_sleep(philo->to_die);
        pthread_mutex_unlock(philo->right_fork);
        return;
    }
    pthread_mutex_lock(philo->left_fork);
    msg_printing(philo, philo->id, "take a fork");
    pthread_mutex_lock(philo->lock_meal);
    philo->is_eating = 1;
    philo->last_eat = get_current_time();
    philo->ate_meals++;
    print_message(philo, philo->id, "is eating");
    pthread_mutex_unlock(philo->lock_meal);
    ft_sleep(philo->to_eat);
    philo->is_eating = 0;
    pthread_mutex_unlock(philo->right_fork);
    pthread_mutex_unlock(philo->left_fork);
}

void    is_thinking(t_thread *philo)
{
    msg_printing(philo, philo->id, "is thinking");
}

void    is_sleeping(t_thread *philo)
{
    msg_printing(philo, philo->id, "is sleeping");
    ft_sleep(philo->to_sleep);
}