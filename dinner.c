#include "philosophers.h"

static void thinking(t_philo *philo)
{
    write_status(THINKING, philo, DEBUG_MODE);
}

void    *lone_philo(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    wait_all_threads(philo->data);
    set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
    increase_long(&philo->data->data_mutex, &philo->data->threads_running_nbr);
    write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
    while (!simulation_finished(philo->data))
    {
        usleep(200);
    }
    printf(WHITE"%-6ld"RST" %d died\n", gettime(MILLISECOND) - philo->data->start_simulation, philo->philo_id);
        // write_status(DIED, philo, DEBUG_MODE);
    return (NULL);
}

static void eat(t_philo *philo)
{
    // grab forks
    mutex_handel(&philo->first_fork->fork, LOCK);
    write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
    mutex_handel(&philo->second_fork->fork, LOCK);
    write_status(TAKE_SECOND_FORK, philo, DEBUG_MODE);
    // write eat, update last meal, update meals counter
    set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
    philo->meals_counter++;
    write_status(EAITING, philo, DEBUG_MODE);
    precise_usleep(philo->data->time_to_eat, philo->data);
    if (philo->data->nbr_limit_meals > 0 && philo->meals_counter == philo->data->nbr_limit_meals)
        set_bool(&philo->philo_mutex, &philo->full, true);
    // unlock mutex
    mutex_handel(&philo->first_fork->fork, UNLOCK);
    mutex_handel(&philo->second_fork->fork, UNLOCK);
}

void    *dinner_simulation(void *data)
{
    t_philo *philo;

    philo = (t_philo *)data;
    wait_all_threads(philo->data);
    // set last meal time
    set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
    increase_long(&philo->data->data_mutex, &philo->data->threads_running_nbr);
    while (!simulation_finished(philo->data))
    {
        if (philo->full)
            break;
        eat(philo);
        write_status(SLEEPING, philo, DEBUG_MODE);
        precise_usleep(philo->data->time_to_sleep, philo->data);
        thinking(philo);
    }
    return (NULL);
}

void    dinner_start(t_data *data)
{
    int i;

    i = -1;
    if (data->nbr_limit_meals == 0)
        return ;
    else if (data->philo_nbr == 1)
        pthread_handel(&data->philos[0].thread_id, lone_philo, &data->philos[0], CREATE);
    else
    {
        while (++i < data->philo_nbr)
            pthread_handel(&data->philos[i].thread_id, dinner_simulation, &data->philos[i], CREATE);  
    }
    // monitor
    pthread_handel(&data->monitor, monitor_dinner, data, CREATE);
    data->start_simulation = gettime(MILLISECOND);
    // threads are ready
    set_bool(&data->data_mutex, &data->all_threads_ready, true);
    i = -1;
    while (++i < data->philo_nbr)
        pthread_handel(&data->philos[i].thread_id, NULL, NULL, JOIN);
    
}