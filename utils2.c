# include "philosophers.h"

void    set_bool(pthread_mutex_t *mutex, bool *dest,bool value)
{
    mutex_handel(mutex, LOCK);
    *dest = value;
    mutex_handel(mutex, UNLOCK);
}

bool    get_bool(pthread_mutex_t *mutex, bool *value)
{
    bool retrn;

    mutex_handel(mutex, LOCK);
    retrn = *value;
    mutex_handel(mutex, UNLOCK);
    return (retrn);
}

void    set_long(pthread_mutex_t *mutex, long *dest,long value)
{
    mutex_handel(mutex, LOCK);
    *dest = value;
    mutex_handel(mutex, UNLOCK);
}

long    get_long(pthread_mutex_t *mutex, long *value)
{
    long retrn;

    mutex_handel(mutex, LOCK);
    retrn = *value;
    mutex_handel(mutex, UNLOCK);
    return (retrn);
}

bool    simulation_finished(t_data *data)
{
    return (get_bool(&data->data_mutex, &data->end_simulation));
}
