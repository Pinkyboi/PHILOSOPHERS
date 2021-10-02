/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 14:45:40 by abenaiss          #+#    #+#             */
/*   Updated: 2021/10/02 18:56:02 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long    get_milliseconds(unsigned int seconds, unsigned int microseconds)
{
    return(seconds * 1000 + microseconds / 1000);
}

int     get_current_time(void)
{
    struct timeval  tv;

    gettimeofday(&tv, NULL);
    return (get_milliseconds(tv.tv_sec, tv.tv_usec));
}

void    print_action_message(int philo_id, const char* message)
{
    struct timeval  tv;

    gettimeofday(&tv, NULL);
    printf("%ld philosopher : %d is %s\n", get_milliseconds(tv.tv_sec, tv.tv_usec), philo_id, message);
}

void    philo_sleep(t_philosopher *philo)
{
    if(get_current_time() + philo->game_rules.sleeping_time > philo->dying_time)
    {
        print_action_message(philo->id, "dying");
        exit(0);
    }
    print_action_message(philo->id, "sleeping");
    usleep(philo->game_rules.sleeping_time);
}

void    philo_eat(t_philosopher *philo)
{
    int id;

    if(get_current_time() + philo->game_rules.eating_time > philo->dying_time)
    {
        print_action_message(id, "dying");
        exit(0);
    }
    id = philo->id;
    print_action_message(id, "eating");
    usleep(philo->game_rules.eating_time);
    philo->dying_time += philo->game_rules.time_to_die;
    pthread_mutex_lock(&g_mutex);
    master->forks[id] = 0;
    master->forks[(id + 1) % master->game_rules.philo_number] = 0;
    pthread_mutex_unlock(&g_mutex);
}

void    kill_philosophers()
{
    
}

void    philo_think(t_philosopher *philo)
{
    print_action_message(philo->id, "thinking");
    if(get_current_time() > philo->dying_time)
    {
        print_action_message(philo->id, "dying");
        exit(0);
    }
}

int     forks_status(int id)
{
    if (!master->forks[id] && !master->forks[(id + 1) % master->game_rules.philo_number])
    {
        master->forks[id] = 1;
        master->forks[(id + 1) % master->game_rules.philo_number] = 1;
        return (1);
    }
    return (0);
}

void    *callback(void *arg)
{
    t_philosopher   *philo;
    int             forks;

    philo = (t_philosopher *)arg;
    philo->dying_time = get_current_time() + philo->game_rules.time_to_die;
    while(1)
    {
        pthread_mutex_lock(&g_mutex);
        forks = forks_status(philo->id);
        pthread_mutex_unlock(&g_mutex);
        if (forks)
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
        master->philo_list[i].id = i;
        master->philo_list[i].is_eating = 0;
        master->philo_list[i].is_sleeping = 0;
        master->philo_list[i].is_thinking = 0;
        master->philo_list[i].game_rules = master->game_rules;
        master->philo_list[i].right_fork = &(master->fork_list[i]);
        master->philo_list[i].left_fork = &(master->fork_list[(i + 1) % master->game_rules.philo_number]);
    }
}

t_orchestrator* init_orchestrator(char** args)
{
    t_orchestrator  *master;
    int             v1;
    int             v2;
    int             v3;
    int             v4;
    int             i;

    v1 = ft_atoi(args[1]);
    v2 = ft_atoi(args[2]);
    v3 = ft_atoi(args[3]);
    v4 = ft_atoi(args[4]);
    printf("%d %d %d %d\n", v1, v2, v3, v4);
    master = malloc(sizeof(t_orchestrator));
    master->game_rules = (t_rules) {v1, v2, v3, v4};
    master->philo_list = malloc(sizeof(t_philosopher) * v1);
    master->fork_list = malloc(sizeof(t_fork) * v1);
    i = -1;
    while (++i < v1)
        master->forks[i] = 0;
    return master;
}

// number_of_philosophers time_to_die
// time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

int main(int argc, char** argv)
{
    // t_orchestrator *master;

    pthread_mutex_init(&g_mutex, NULL);
    if(argc != 5)
        exit(0);
    master = init_orchestrator(argv);
    // g_mutexs = malloc(sizeof(pthread_mutex_t) * master->game_rules.philo_number);
    init_philosophers(master);
    threads_master(master);
    return 0 ;
}