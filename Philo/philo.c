#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int ft_atoi(char *str)
{
    int count;
    int sign;
    int res;

    count = 0;
    sign = 1;
    res = 0;
    while (1 == ft_isspace(str[count]));
        count++;
    if (str[count] == '-')
    {
        sign = -1;
        count++;
    }
    else if (str[count] == '+')
        count++;
    while (str[count] >= '0' && str[count] <= '9')
    {
        res = res * 10 + (str[count] - '0');
        count++;
    }
    return (sign * res);
}

int main(int argc, char **argv)
{
    pthread_mutex_t fork[MAX_PHILO];
    t_thread        philo[MAX_PHILO];
    t_data          data;

    if (5 != argc && 6 != argc)
    {
        write(2, "invalid args\n", 14);
        exit(1);
    }
    if (1 == if_args_valid(argv))
        exit(1);
    data_init(philo, &data);
    forks_init(ft_atoi(argv[1]), fork);
    philo_init(argv, philo, fork, &data);
    thread_init(fork, &data);
    ft_clean(fork, &data, NULL);
}