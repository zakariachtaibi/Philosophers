# include "philosophers.h"

void    wait_all_threads(t_data *data)
{
    while (!get_bool(&data->data_mutex, &data->all_threads_ready))
        ;
}

bool    all_threads_running(pthread_mutex_t *mutex, long *threads, long philo_nbr)
{
    bool ret;

    ret = false;
    mutex_handel(mutex, LOCK);
    if (*threads == philo_nbr)
        ret = true;
    mutex_handel(mutex, UNLOCK);
    return (ret);
}

void    increase_long(pthread_mutex_t *mutex, long *value)
{
    mutex_handel(mutex, LOCK);
    (*value)++;
    mutex_handel(mutex, UNLOCK);
}