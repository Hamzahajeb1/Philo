#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <time.h>

# define MAX_PHILO 200

typedef struct s_thread
{
    int *dead;
    int id;
    int is_eating;
    int philo_num;
    int num_to_eat;
    int ate_meals;
    size_t start;
    size_t last_eat;
    size_t to_eat;
    size_t to_sleep;
    size_t to_die;
    pthread_t philos;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    pthread_mutex_t *lock_meal;
    pthread_mutex_t *lock_death;
    pthread_mutex_t *lock_writing;
    
}   t_thread;

typedef struct s_data
{
    int             flg;
    t_thread        *threads;
    pthread_mutex_t meal;
    pthread_mutex_t dead;
    pthread_mutex_t writing;
} t_data;

int     if_args_valid(char **argv);
int     ft_sleep(size_t ms);
int     dead_lock(t_thread *philo);
int     all_ate(t_thread *philo);
int     if_dead(t_thread *philo);
int     ft_atoi(char *str);
int     ft_strlen(char *str);
int     threads_init(pthread_mutex_t *fork, t_data *data);
size_t	curr_time();
void    data_init(t_thread *philo, t_data *data);
void    ft_clean(pthread_mutex_t *fork, t_data *data, char *str);
void    fork_init(int num_of_philo, pthread_mutex_t *fork);
void	msg_printing(t_thread *philo, int philosopher_id, char *str);
void    is_eating(t_thread *philo);
void    is_thinking(t_thread *philo);
void    is_sleeping(t_thread *philo);

#endif