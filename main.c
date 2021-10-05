/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 14:45:40 by abenaiss          #+#    #+#             */
/*   Updated: 2021/10/05 18:14:47 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*callback(void *arg)
{
	t_philosopher   *philo;

	philo = (t_philosopher *)arg;
	philo->dying_time = get_current_time() + philo->game_rules.time_to_die;
	while (1)
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

void	destroy_master_mutex(void)
{
	int i;

	i = -1;
	while (++i < master->game_rules.philo_number)
		pthread_mutex_destroy(&master->forks[i]);
	pthread_mutex_destroy(&master->output_mutex);
}

void*	master_watcher(void *arg)
{
	while (!master->first_blood)
		continue ;
	destroy_master_mutex();
	return (NULL);
}


void	threads_master(t_orchestrator *orch)
{
	int         i;
	int         ret;
	pthread_t   master_thread;

	i = -1;
	master->execution_time = get_current_time();
	while (++i < orch->game_rules.philo_number)
	{
		ret = pthread_create(&orch->philo_list[i].tid, NULL,
			callback, (void *)&orch->philo_list[i]);
		if (ret != 0)
			return ;
		pthread_detach(orch->philo_list[i].tid);
	}
	ret = pthread_create(&master_thread, NULL, master_watcher, NULL);
	pthread_join(master_thread, NULL);
}

void	init_philosophers(t_orchestrator *master)
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

void	init_master(char** args, int argc)
{
	master = malloc(sizeof(t_orchestrator));
	master->game_rules = (t_rules) {.philo_number = ft_atoi(args[1]), 
									.time_to_die = ft_atoi(args[2]),
									.time_to_eat = ft_atoi(args[3]),
									.time_to_sleep = ft_atoi(args[4]),
									.number_of_times_eat = -1};
	master->game_rules.time_to_eat_us = master->game_rules.time_to_eat * 1000;
	master->game_rules.time_to_sleep_us = master->game_rules.time_to_sleep * 1000;
	if (argc == 6)
		master->game_rules.number_of_times_eat = ft_atoi(args[5]);
	master->philo_list = malloc(sizeof(t_philosopher) * master->game_rules.philo_number);
	master->forks = malloc(sizeof(pthread_mutex_t) * master->game_rules.philo_number);
	master->first_blood = 0;
	master->full_counter = 0;
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
	{
		printf("./usage : number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]");
		return 0;
	}
	init_master(argv, argc);
	init_philosophers(master);
	threads_master(master);
	return 0 ;
}

//add fork structure inculding status of the fork
