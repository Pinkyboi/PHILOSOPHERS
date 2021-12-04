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

static short	error_handler(short error_code)
{
	if (!error_code)
		return (0);
	printf("\033[0;31m");
	printf("Error : ");
	printf("\033[0m");
	if (error_code == ERR_WRONG_PARAM_NUMBER)
		printf("%s\n", "Usage: ./philo [philosopher's number]"
			"[time to die] [time to eat] [time to sleep]"
			"[max number of meals]");
	if (error_code == ERR_MALLOC || error_code == ERR_MUTEX)
		printf("%s\n", "Internal error, please try again.");
	if (error_code == ERR_NEGATIVE)
		printf("%s\n", "No passed parameter should be negative.");
	if (error_code == ERR_ZERO)
		printf("%s\n", "No passed parameter should be null.");
	return (1);
}

static void	clear_env(t_env *env)
{
	unsigned int	i;

	i = -1;
	pthread_mutex_destroy(&env->print_mutex);
	if (env->fork_list)
	{
		while (++i < env->params[philo_number])
			pthread_mutex_destroy(&env->fork_list[i].fork_lock);
		free(env->fork_list);
	}
	if (env->philo_list)
	{
		while (++i < env->params[philo_number])
			pthread_mutex_destroy(&env->philo_list[i].death_mutex);
		free(env->philo_list);
	}
}

int	main(int argc, char **argv)
{
	t_env	*env;
	short	err_status;

	if (argc != 5 && argc != 6)
	{
		error_handler(ERR_WRONG_PARAM_NUMBER);
		return (0);
	}
	err_status = 0;
	env = (t_env *)malloc(sizeof(t_env));
	if (!env)
		err_status = error_handler(ERR_MALLOC);
	if (!err_status)
	{
		err_status = error_handler(initialize_env(env, argc, argv));
		if (!err_status)
			setting_dinner(env);
		clear_env(env);
	}
	return (0);
}
