# include "philosophers.h"

void print_initialized_data(t_data *data)
{
    printf("Initialized Data:\n");
    printf("Number of philosophers: %ld\n", data->philo_nbr);
    printf("Time to die: %ld ms\n", data->time_to_die);
    printf("Time to eat: %ld ms\n", data->time_to_eat);
    printf("Time to sleep: %ld ms\n", data->time_to_sleep);
    printf("Number of times each philosopher must eat: %ld\n", data->nbr_limit_meals);
    printf("Start simulation time: %ld ms\n", data->start_simulation);
    printf("End simulation flag: %s\n", data->end_simulation ? "true" : "false");
    printf("\nPhilosophers:\n"); 
    for (int i = 0; i < data->philo_nbr; i++)
    {
        printf("Philosopher %d:\n", data->philos[i].philo_id);
        printf("  Meals eaten: %ld\n", data->philos[i].meals_counter);
        printf("  Is full: %s\n", data->philos[i].full ? "true" : "false");
        printf("  Fisrt fork ID: %d\n", data->philos[i].first_fork->fork_id);
        printf("  Second fork ID: %d\n", data->philos[i].second_fork->fork_id);
        printf("\n");
    }
    printf("Forks:\n");
    for (int i = 0; i < data->philo_nbr; i++)
        printf("Fork %d initialized\n", data->forks[i].fork_id);
}

int main(int ac, char **av)
{
    t_data data; 
    if (ac == 5 || ac == 6)
    {
        parse_input(&data, av);
        data_init(&data);
        // print_initialized_data(&data);
        dinner_start(&data);
        // clean(&table);
    } else
        error_exit("Wrong input:\n" YELLOW "Enter like this ./philo 5 800 200 200 [5]" RST);
    return 0;
}