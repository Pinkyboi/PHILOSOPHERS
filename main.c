/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 14:45:40 by abenaiss          #+#    #+#             */
/*   Updated: 2021/10/04 19:01:46 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    *callback(void *arg)
{
    t_philosopher   *philo;

    philo = (t_philosopher *)arg;
    philo->dying_time = get_current_time() + philo->game_rules.time_to_die;
    while (1)
    {
        philo_eat(philo);
        if (master->full_counter == master->game_rules.philo_number)
            exit(-1);
        philo_sleep(philo);
        philo_think(philo);
    }
    return (NULL);
}

void    threads_master(t_orchestrator *orch)
{
    int         i;
    int         ret;

    i = -1;
    master->execution_time = get_current_time();
    while (++i < orch->game_rules.philo_number)
    {
        ret = pthread_create(&orch->philo_list[i].tid, NULL, callback, (void *)&orch->philo_list[i]);
        if (ret != 0)
            exit(-1);
    }
    while (i--)
        pthread_join(orch->philo_list[i].tid, NULL);
}

void    init_philosophers(t_orchestrator *master)
{
    unsigned int i;
    t_philosopher *mok;

    i = -1;
    while(++i < master->game_rules.philo_number)
    {
        mok = &master->philo_list[i];
        master->philo_list[i].id = i;
        master->philo_list[i].game_rules = master->game_rules;
        master->philo_list[i].meal_number = 0;
    }
}

void init_orchestrator(char** args, int argc)
{
    master = malloc(sizeof(t_orchestrator));
    master->game_rules = (t_rules) {.philo_number = ft_atoil(args[1]), 
                                    .time_to_die = ft_atoil(args[2]),
                                    .time_to_eat = ft_atoil(args[3]),
                                    .time_to_sleep = ft_atoil(args[4]),
                                    .number_of_times_eat = -1};
    if(argc == 6)
        master->game_rules.number_of_times_eat = ft_atoil(args[5]);
    master->philo_list = malloc(sizeof(t_philosopher) * master->game_rules.philo_number);
    master->forks = malloc(sizeof(pthread_mutex_t) * master->game_rules.philo_number);
    master->first_blood = -1;
    init_mutexs();
}


void    init_mutexs()
{
    int i;

    i = -1;
    while (++i < master->game_rules.philo_number)
        master->forks[i] = (pthread_mutex_t)PTHREAD_ERRORCHECK_MUTEX_INITIALIZER;
    pthread_mutex_init(&master->output_mutex, NULL);
}

// number_of_philosophers time_to_die
// time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

int main(int argc, char** argv)
{
    if(!(argc == 5 || argc == 6))
        exit(0);
    init_orchestrator(argv, argc);
    init_philosophers(master);
    threads_master(master);
    return 0 ;
}