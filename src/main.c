/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 22:02:07 by abenaiss          #+#    #+#             */
/*   Updated: 2021/12/04 14:49:43 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	clear_env(t_env *env, short err_code)
{
	unsigned int	i;

	i = -1;
	if (err_code != ERR_MUTEX_PRINT)
		pthread_mutex_destroy(&env->print_mutex);
	if (env->fork_list)
	{
		if (err_code != ERR_MUTEX_FORK)
			while (++i < env->params[philo_number])
				pthread_mutex_destroy(&env->fork_list[i].fork_lock);
		free(env->fork_list);
	}
	if (env->philo_list)
	{
		if (err_code != ERR_MUTEX_DEATH)
			while (++i < env->params[philo_number])
				pthread_mutex_destroy(&env->philo_list[i].death_mutex);
		free(env->philo_list);
	}
}

int	main(int argc, char **argv)
{
	t_env	*env;
	short	err_code;

	if (argc != 5 && argc != 6)
	{
		error_handler(ERR_WRONG_PARAM_NUMBER);
		return (0);
	}
	err_code = 0;
	env = (t_env *)malloc(sizeof(t_env));
	if (!env)
		err_code = error_handler(ERR_MALLOC);
	if (!err_code)
	{
		err_code = initialize_env(env, argc, argv);
		if (!error_handler(err_code))
			setting_dinner(env);
		clear_env(env, err_code);
	}
	return (0);
}
