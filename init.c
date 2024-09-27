# include "philosophers.h"

static void  assign_forks(t_philo *philo, t_fork *forks, int philo_position)
{
    int philo_nbr;

    philo_nbr = philo->data->philo_nbr;
    philo->first_fork = &forks[(philo_position + 1) % philo_nbr];
    philo->second_fork = &forks[philo_position];  
    if (philo->philo_id % 2 == 0)
    {
        philo->first_fork = &forks[philo_position];
        philo->second_fork = &forks[(philo_position + 1) % philo_nbr];  
    }   
}

static void philo_init(t_data *data)
{
    int     i;
    t_philo *philo;

    i = -1;
    while (++i < data->philo_nbr)
    {
        philo = data->philos + i;
        philo->philo_id = i + 1;
        philo->full = false;
        philo->meals_counter = 0;
        philo->data = data;
        mutex_handel(&philo->philo_mutex, INIT);
        assign_forks(philo, data->forks, i);
    }
}

void    data_init(t_data *data)
{
    int i;

    i = -1;
    data->end_simulation = false;
    data->all_threads_ready = false;
    data->threads_running_nbr = 0;
    data->philos = malloc(sizeof(t_philo) * data->philo_nbr);
    if (data->philos == NULL)
        error_exit("Error in malloc for philosophers");
    mutex_handel(&data->data_mutex, INIT);
    mutex_handel(&data->write_mutex, INIT);
    data->forks = malloc(sizeof(t_fork) * data->philo_nbr);
    if (data->forks == NULL)
        error_exit("Error in malloc for forks");
    while (++i < data->philo_nbr)
    {
        mutex_handel(&data->forks[i].fork, INIT);
        data->forks[i].fork_id = i;
    }
    philo_init(data);
}