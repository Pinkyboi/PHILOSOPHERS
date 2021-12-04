/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 15:27:10 by abenaiss          #+#    #+#             */
/*   Updated: 2021/12/04 14:48:38 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static short	init_philosophers(t_env *env)
{
	unsigned int	i;

	i = -1;
	env->philo_list = malloc(sizeof(t_philo) * env->params[philo_number]);
	if (!env->philo_list)
		return (ERR_MALLOC);
	while (++i < env->params[philo_number])
	{
		if (pthread_mutex_init(&env->philo_list[i].death_mutex, NULL))
			return (ERR_MUTEX);
		env->philo_list[i].id = i;
		env->philo_list[i].big_fork = get_bigger_fork(i, env);
		env->philo_list[i].small_fork = get_smaller_fork(i, env);
		env->philo_list[i].params = env->params;
		env->philo_list[i].print_mutex = &env->print_mutex;
		env->philo_list[i].end_thread = false;
		env->philo_list[i].eat_count = 0;
	}
	return (0);
}

static short	init_forks(t_env *env)
{
	unsigned int	i;

	i = -1;
	env->fork_list
		= (t_fork*)malloc(sizeof(t_fork) * env->params[philo_number]);
	if (!env->fork_list)
		return (ERR_MALLOC);
	while (++i < env->params[philo_number])
	{
		if (pthread_mutex_init(&env->fork_list[i].fork_lock, NULL))
			return (ERR_MUTEX);
		env->fork_list[i].is_fork_used = false;
		env->fork_list[i].past_users = -1;
	}
	return (0);
}

static short	verify_philo_params(int argc, const unsigned int *params)
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
	env->end_simulation = false;
	env->fork_list = NULL;
	env->philo_list = NULL;
	if (pthread_mutex_init(&env->print_mutex, NULL))
		return (ERR_MUTEX);
	if (argc == 6)
		env->params[max_eat_count] = my_atoi(argv[5]);
	else
		env->params[max_eat_count] = 0;
	return (safe_init(argc, env));
}
