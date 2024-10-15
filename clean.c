# include "philosophers.h"

void    clean(t_data *data)
{
    t_philo *philo;
    int     i;

    i = -1;
    while (++i < data->philo_nbr)
    {
        philo = data->philos + i;
        mutex_handel(&philo->philo_mutex, DESTROY);
    }
    mutex_handel(&data->write_mutex, DESTROY);
    mutex_handel(&data->data_mutex, DESTROY);
    free(data->forks);
    free(data->philos);
}

void    de_synchronize_philos(t_philo *philo)
{
    if (philo->data->philo_nbr % 2 == 0)
    {
        if (philo->philo_id % 2 == 0)
            precise_usleep(3e4, philo->data);
    } else
    {
        if (philo->philo_id % 2)
            thinking(philo, true);
    }
}