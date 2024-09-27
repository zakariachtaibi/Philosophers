#include "philosophers.h"

static int is_space(char c)
{
    return ((c >= 9 && c <= 13) || c == 32);
}

static bool is_valid_number(const char *str)
{
    while (is_space(*str))
        str++;
    if (*str == '+')
        str++;
    if (!*str)
        return false;
    while (*str) {
        if (!ft_isdigit(*str))
            return false;
        str++;
    }
    return true;
}

static long ft_atol(const char *str)
{
    long num;

    if (!is_valid_number(str))
        error_exit("Invalid input: not a valid positive integer");
    num = 0;
    while (is_space(*str))
        str++;
    if (*str == '+')
        str++;
    while (ft_isdigit(*str)) {
        num = num * 10 + (*str - '0');
        if (num > INT_MAX)
            error_exit("Number out of range");
        str++;
    }
    return num;
}

void parse_input(t_data *data, char **av)
{
    data->philo_nbr = ft_atol(av[1]);
    data->time_to_die = ft_atol(av[2]);
    data->time_to_eat = ft_atol(av[3]);
    data->time_to_sleep = ft_atol(av[4]);


    if (data->philo_nbr <= 0 || data->philo_nbr > 200)
        error_exit("Number of philosophers must be between 1 and 200");
    if (data->time_to_die < 60 || data->time_to_eat < 60 || data->time_to_sleep < 60)
        error_exit("Time values must be at least 60 ms");
    data->time_to_die *= 1000;
    data->time_to_eat *= 1000;
    data->time_to_sleep *= 1000;

    if (av[5]) {
        data->nbr_limit_meals = ft_atol(av[5]);
        if (data->nbr_limit_meals <= 0)
            error_exit("Number of times each philosopher must eat should be positive");
    } else
        data->nbr_limit_meals = -1;
}