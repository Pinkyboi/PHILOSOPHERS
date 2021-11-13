/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 15:27:10 by abenaiss          #+#    #+#             */
/*   Updated: 2021/11/13 02:32:06 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void init_philosophers(void)
{
	int i;

	i = -1;
    env->philo_list = (t_philo*)malloc(sizeof(t_philo) * env->params[philo_number]);
	while (++i < env->params[philo_number])
    {
		env->philo_list[i].id = i;
        env->philo_list[i].eat_count = 0;
    }
}

static void init_forks(void)
{
	int i;

	i = -1;
    env->fork_list = (t_fork*)malloc(sizeof(t_fork) * env->params[philo_number]);
	while (++i < env->params[philo_number])
    {
        env->fork_list[i].fork_lock
            = (pthread_mutex_t)PTHREAD_ERRORCHECK_MUTEX_INITIALIZER;
        env->fork_list[i].users[curent_user] = -1;
        env->fork_list[i].users[past_user] = -1;
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
    env->philo_full = 0;
    if (argc == 6)
        env->params[max_eat_count] = my_atoi(argv[5]);
    else
        env->params[max_eat_count] = -1;
    init_philosophers();
    init_forks();
}