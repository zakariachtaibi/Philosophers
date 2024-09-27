#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdlib.h>
# include <sys/time.h>
# include <limits.h>
# include "libft/libft.h"

// ANSI escape codes for colors
#define RST         "\033[0m" // default color
#define BOLD        "\033[1m"
#define BLACK       "\033[30m"
#define RED         "\033[31m"
#define GREEN       "\033[32m"
#define YELLOW      "\033[33m"
#define BLUE        "\033[34m"
#define MAGENTA     "\033[35m"
#define CYAN        "\033[36m"
#define WHITE       "\033[37m"

# define DEBUG_MODE 1

typedef enum e_status
{
    EAITING,
    SLEEPING,
    THINKING,
    TAKE_FIRST_FORK,
    TAKE_SECOND_FORK,
    DIED,
}   t_philo_status;

typedef enum e_code
{
    LOCK,
    UNLOCK,
    INIT,
    DESTROY,
    CREATE,
    JOIN,
    DETACH,
}   t_code;

typedef enum e_time
{
    SECOND,
    MILLISECOND,
    MICROSECOND,
}   t_time;

typedef struct s_fork
{
    pthread_mutex_t fork;
    int             fork_id;
} t_fork;

typedef struct s_philo
{
    int             philo_id;
    long            meals_counter;
    bool            full; // if philosophers eat all food
    long            last_meal_time;
    t_fork          *first_fork;
    t_fork          *second_fork;
    pthread_t       thread_id;
    pthread_mutex_t philo_mutex;
    struct s_data   *data; 
} t_philo;

typedef struct s_data
{
    long            philo_nbr;
    long            time_to_die;
    long            time_to_eat;
    long            time_to_sleep;
    long            nbr_limit_meals;
    long            start_simulation;
    bool            end_simulation; // a philo dies or all philos full
    bool            all_threads_ready;
    long            threads_running_nbr;
    pthread_t       monitor;
    pthread_mutex_t data_mutex;
    pthread_mutex_t write_mutex;
    t_fork          *forks;
    t_philo         *philos;
} t_data;

//error
void    error_exit(const char *error);
//parsing
void    parse_input(t_data *data, char **av);
//handel
void    mutex_handel(pthread_mutex_t *mutex, t_code code);
void    pthread_handel(pthread_t *thread, void *(*func)(void *), void *data, t_code code);
//init
void    data_init(t_data *data);
//setter & getters
void    set_bool(pthread_mutex_t *mutex, bool *dest,bool value);
bool    get_bool(pthread_mutex_t *mutex, bool *value);
void    set_long(pthread_mutex_t *mutex, long *dest,long value);
long    get_long(pthread_mutex_t *mutex, long *value);
bool    simulation_finished(t_data *data);
// synchro
void    wait_all_threads(t_data *data);
long    gettime(t_time time);
void    precise_usleep(long usec, t_data *data);
// write_status
void    write_status(t_philo_status status, t_philo *philo, bool debug);

void    dinner_start(t_data *data);
bool    all_threads_running(pthread_mutex_t *mutex, long *threads, long philo_nbr);
void    increase_long(pthread_mutex_t *mutex, long *value);

void    *monitor_dinner(void *data);
#endif
