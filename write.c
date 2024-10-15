# include "philosophers.h"

static void write_status_debug(t_philo_status status, t_philo *philo, long elapsed)
{
    if (status == TAKE_FIRST_FORK && !simulation_finished(philo->data))
        printf(WHITE"%6ld"RST" %d has taken the 1 fork[%d]\n", elapsed, philo->philo_id, philo->first_fork->fork_id);
    else if (status == TAKE_SECOND_FORK && !simulation_finished(philo->data))
        printf(WHITE"%6ld"RST" %d has taken the 2 fork[%d]\n", elapsed, philo->philo_id, philo->second_fork->fork_id);
    else if (status == EAITING && !simulation_finished(philo->data))
        printf(WHITE"%6ld"RST" %d is eating\n", elapsed, philo->philo_id);
    else if (status == SLEEPING && !simulation_finished(philo->data))
        printf(WHITE"%6ld"RST" %d is sleeping\n", elapsed, philo->philo_id);
    else if (status == THINKING && !simulation_finished(philo->data))
        printf(WHITE"%-ld"RST" %d is thinking\n", elapsed, philo->philo_id);
    else if (status == DIED && !simulation_finished(philo->data))
        printf(WHITE"%6ld"RST" %d died\n", elapsed, philo->philo_id);
}

void    write_status(t_philo_status status, t_philo *philo, bool debug)
{
    long    elapsed;

    elapsed = gettime(MILLISECOND) - philo->data->start_simulation;
    if (philo->full)    
        return ;
    mutex_handel(&philo->data->write_mutex, LOCK);
    if (debug == 1)
        write_status_debug(status, philo, elapsed);
    else
    {
        if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK) && !simulation_finished(philo->data))
            printf(WHITE"%-6ld"RST" %d has taken a fork\n", elapsed, philo->philo_id);
        else if (status == EAITING && !simulation_finished(philo->data))
            printf(WHITE"%-6ld"RST" %d is eating\n", elapsed, philo->philo_id);
        else if (status == SLEEPING && !simulation_finished(philo->data))
            printf(WHITE"%-6ld"RST" %d is sleeping\n", elapsed, philo->philo_id);
        else if (status == THINKING && !simulation_finished(philo->data))
            printf(WHITE"%-6ld"RST" %d is thinking\n", elapsed, philo->philo_id);
        else if (status == DIED)
            printf(WHITE"%-6ld"RST" %d died\n", elapsed, philo->philo_id);
    }
    mutex_handel(&philo->data->write_mutex, UNLOCK);
}