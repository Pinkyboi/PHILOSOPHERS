/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 15:27:10 by abenaiss          #+#    #+#             */
/*   Updated: 2021/11/12 18:54:32 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philosophers(void)
{
	int i;

	i = -1;
    env->philo_list = (t_philo*)malloc(sizeof(t_philo) * env->params[philo_number]);
	while(++i < env->params[philo_number])
		env->philo_list[i].id = i;
}

void	init_forks(void)
{
	int i;

	i = -1;
    env->fork_list = (t_fork*)malloc(sizeof(t_fork) * env->params[philo_number]);
	while(++i < env->params[philo_number])
    {
		pthread_mutex_init(&env->fork_list[i].fork_lock, NULL);
        env->fork_list[i].users[past_user] = -1;
        env->fork_list[i].users[curent_user] = -1;
        env->fork_list[i].id = i;
    }
}

void    initialize_env(int argc, char** argv)
{
    env->params[philo_number]  = my_atoi(argv[1]);
    env->params[time_to_die]   = my_atoi(argv[2]);
    env->params[time_to_eat]   = my_atoi(argv[3]);
    env->params[time_to_sleep] = my_atoi(argv[4]);
    env->terminate = flase;
    if(argc == 6)
        env->params[max_eat_count] = my_atoi(argv[5]);
    else
        env->params[max_eat_count] = -1;    
    env->fork_list = (t_fork*)malloc(sizeof(t_fork) * env->params[philo_number]);
    init_philosophers();
    init_forks();
}