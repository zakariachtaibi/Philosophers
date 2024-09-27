#include "philosophers.h"

static bool philo_died(t_philo *philo)
{
    long    elapsed;
    long    t_to_die;

    if (get_bool(&philo->philo_mutex, &philo->full))
        return (false);
    elapsed = gettime(MILLISECOND) - get_long(&philo->philo_mutex, &philo->last_meal_time);
    t_to_die = philo->data->time_to_die / 1e3;
    if (elapsed > t_to_die)
        return (true);
    return (false);
}

void    *monitor_dinner(void *data)
{
    t_data  *table;
    int     i;

    table = (t_data *)data;
    // wait untill all threads running
    while (!all_threads_running(&table->data_mutex, &table->threads_running_nbr, table->philo_nbr))
        ;
    // check time to die
    while (!simulation_finished(table))
    {
        i = -1;
        while (++i < table->philo_nbr && !simulation_finished(table))
        {
            if (philo_died(table->philos + i))
            {
                set_bool(&table->data_mutex, &table->end_simulation, true);
                // printf(WHITE"%-6ld"RST" %d died\n", gettime(MILLISECOND) - table->start_simulation, table->philos->philo_id);
                // write_status(DIED, table->philos + i, DEBUG_MODE);
            }
        }
    }
    return (NULL);
}