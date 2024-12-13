#include "philo.h"

void    *monitor(void *p)
{
    t_thread    *th;
    
    th = (t_thread *)p;
    while (1)
        if (1 == all_ate(th) || 1 == if_dead(th))
            break ;
    return (p);
}

void    *routine(void *p)
{
    t_thread    *th;
    
    th = (t_thread *)p;
    if (0 == th->id % 2)
        ft_sleep(1);
    while(!dead_lock(th))
    {
        is_eating(th);
        is_sleeping(th);
        is_thinking(th);
    }
    return (p);
}

void    destroy(pthread_mutex_t *fork, t_data *data)
{
    int i;
    
    pthread_mutex_destroy(&data->writing);
    pthread_attr_destroy(&data->meal);
    pthread_attr_destroy(&data->dead);
    i = 0;
    while (i <data->threads[0].philo_num)
    {
        pthread_attr_destroy(&fork[i]);
        i++;
    }
}

void    ft_clean(pthread_mutex_t *fork, t_data *data, char *str)
{
    if (str)
    {
        write(2, str, ft_strlen(str));
        write(2, "\n", 1);
    }
    destroy(fork, data);
}

int threads_init(pthread_mutex_t *fork, t_data *data)
{
    int       i;
    pthread_t th;

    i = 0;
    if (0 != pthread_create(&th, NULL, &monitor, data->threads))
        ft_clean(fork, data, "Thread creation failed");
    while (i < data->threads[0].philo_num)
    {
        if (0 != pthread_create(&data->threads[i].philos, NULL, &routine, &data->threads[i]))
            ft_clean(fork, data, "Thread creation failed");
        i++;
    }
    if (0 != pthread_join(th, NULL))
        ft_clean(fork, data, "Thread join failed");
    i = 0;
    while (i < data->threads[0].philo_num)
    {
        if (0 != pthread_join(data->threads[i].philos, NULL))
            ft_clean(fork, data, "Thread join failed");
        i++;
    }
    return 0;
}
