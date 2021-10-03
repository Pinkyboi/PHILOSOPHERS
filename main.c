/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 14:45:40 by abenaiss          #+#    #+#             */
/*   Updated: 2021/10/03 18:20:58 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// int     forks_status(int id)
// {
//     if (!master->forks[id] && !master->forks[(id + 1) % master->game_rules.philo_number])
//     {
//         master->forks[id] = 1;
//         master->forks[(id + 1) % master->game_rules.philo_number] = 1;
//         return (1);
//     }
//     return (0);
// }

void    *callback(void *arg)
{
    t_philosopher   *philo;

    philo = (t_philosopher *)arg;
    philo->dying_time = get_current_time() + philo->game_rules.time_to_die;
    while(1)
    {
        philo_eat(philo);
        philo_sleep(philo);
        philo_think(philo);
    }
    return (NULL);
}

void    threads_master(t_orchestrator *orch)
{
    int         i;
    int         ret;
    pthread_t   tid[orch->game_rules.philo_number];

    i = -1;
    while (++i < orch->game_rules.philo_number)
    {
        ret = pthread_create(&tid[i], NULL, callback, (void *)&orch->philo_list[i]);
        if (ret != 0)
            exit(-1);
    }
    while (i--)
        pthread_join(tid[i], NULL);
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
    }
}

void init_orchestrator(char** args)
{
    // t_orchestrator  *master;

    master = malloc(sizeof(t_orchestrator));
    master->game_rules = (t_rules) {.philo_number = ft_atoil(args[1]), 
                                    .time_to_die = ft_atoil(args[2]),
                                    .time_to_eat = ft_atoil(args[3]),
                                    .time_to_sleep = ft_atoil(args[4])};
    master->philo_list = malloc(sizeof(t_philosopher) * master->game_rules.philo_number);
    master->forks = malloc(sizeof(pthread_mutex_t) * master->game_rules.philo_number);
    master->first_blood = -1;
    init_mutexs();
    // return master;
}

// number_of_philosophers time_to_die
// time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

void    init_mutexs()
{
    int i;

    i = -1;
    while (++i < master->game_rules.philo_number)
        pthread_mutex_init(&master->forks[i], NULL);
    pthread_mutex_init(&master->output_mutex, NULL);
}

int main(int argc, char** argv)
{
    if(argc != 5)
        exit(0);
    init_orchestrator(argv);
    init_philosophers(master);
    threads_master(master);
    return 0 ;
}