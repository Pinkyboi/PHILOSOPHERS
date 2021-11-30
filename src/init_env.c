/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 15:27:10 by abenaiss          #+#    #+#             */
/*   Updated: 2021/11/30 03:06:19 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static short	init_philosophers(t_env *env)
{
	int	i;

	i = -1;
	env->philo_list = malloc(sizeof(t_philo) * env->params[philo_number]);
	if (!env->philo_list)
		return (ERR_MALLOC);
	while (++i < env->params[philo_number])
	{
		env->philo_list[i].fork_list = env->fork_list;
		env->philo_list[i].params = env->params;
		env->philo_list[i].print_mutex = &env->print_mutex;
		env->philo_list[i].terminate = &env->terminate;
		env->philo_list[i].start_time = &env->start_time;
		env->philo_list[i].philo_full = &env->philo_full;
		env->philo_list[i].id = i;
		env->philo_list[i].eat_count = 0;
	}
	return (0);
}

static short	init_forks(t_env *env)
{
	int	i;

	i = -1;
	env->fork_list
		= (t_fork*)malloc(sizeof(t_fork) * env->params[philo_number]);
	if (!env->fork_list)
		return (ERR_MALLOC);
	while (++i < env->params[philo_number])
	{
		env->fork_list[i].fork_lock
			= (pthread_mutex_t)PTHREAD_ERRORCHECK_MUTEX_INITIALIZER;
		env->fork_list[i].users[curent_user] = -1;
		env->fork_list[i].users[past_user] = -1;
	}
	return (0);
}

static short	verify_philo_params(int argc, const long *params)
{
	int	i;
	int	param_number;

	param_number = PARAM_NUMBER;
	if (argc != 6)
		param_number--;
	i = -1;
	while (++i < param_number)
	{
		if (params[i] == 0)
			return (ERR_ZERO);
		if (params[i] < 0)
			return (ERR_NEGATIVE);
	}
	return (0);
}

static short	safe_init(int argc, t_env *env)
{
	short	err_handler;

	err_handler = verify_philo_params(argc, env->params);
	if (err_handler)
		return (err_handler);
	err_handler = init_forks(env);
	if (err_handler)
		return (err_handler);
	err_handler = init_philosophers(env);
	if (err_handler)
		return (err_handler);
	return (0);
}

short	initialize_env(t_env *env, int argc, char **argv)
{
	env->params[philo_number] = my_atoi(argv[1]);
	env->params[time_to_die] = my_atoi(argv[2]);
	env->params[time_to_eat] = my_atoi(argv[3]);
	env->params[time_to_sleep] = my_atoi(argv[4]);
	env->terminate = flase;
	env->philo_full = 0;
	env->fork_list = NULL;
	env->philo_list = NULL;
	if (pthread_mutex_init(&env->print_mutex, NULL))
		return (ERR_MUTEX);
	if (argc == 6)
		env->params[max_eat_count] = my_atoi(argv[5]);
	else
		env->params[max_eat_count] = -1;
	return (safe_init(argc, env));
}
