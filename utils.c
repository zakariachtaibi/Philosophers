# include "philosophers.h" 

void error_exit(const char *error)
{
    printf(RED "%s\n" RST, error);
    exit(EXIT_FAILURE);
}

void    mutex_handel(pthread_mutex_t *mutex, t_code code)
{
    if (code == LOCK)
        pthread_mutex_lock(mutex);
    else if (code == UNLOCK)
        pthread_mutex_unlock(mutex);
    else if (code == INIT)
        pthread_mutex_init(mutex, NULL);
    else if (code == DESTROY)
        pthread_mutex_destroy(mutex);
    else
        error_exit("Wrong code of mutex handle");
}

void    pthread_handel(pthread_t *thread, void *(*func)(void *), void *data, t_code code)
{
    if (code == CREATE)
        pthread_create(thread, NULL, func, data);
    else if (code == JOIN)
        pthread_join(*thread, NULL);
    else if (code == DETACH)
        pthread_detach(*thread);
    else
        error_exit("Wrong, please use <CREATE> <JOIN> <DETACH>");
}

long    gettime(t_time time)
{
    struct timeval  tv;
    if (gettimeofday(&tv, NULL))
        error_exit("Gettimeoftoday failed!");
    if (time == SECOND)
        return (tv.tv_sec + (tv.tv_usec / 1e6));
    else if (time == MILLISECOND)
        return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
    else if (time == MICROSECOND)
        return ((tv.tv_sec * 1e6) + tv.tv_usec);
    else
        error_exit("Wrong input to gettime!");
    return (1337);
}

void    precise_usleep(long usec, t_data *data)
{
    long    start;
    long    elapsed;
    long    rem;

    start = gettime(MICROSECOND);
    while (gettime(MICROSECOND) - start < usec)
    {
        if (simulation_finished(data))
             break;
        elapsed = gettime(MICROSECOND) - start;
        rem = usec - elapsed;

        if (rem > 1e3)
            usleep(rem / 2);
        else
        {
            //spinlock
            while (gettime(MICROSECOND) - start < usec)
                ;
        }
    }
}