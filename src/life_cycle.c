/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 22:04:00 by abenaiss          #+#    #+#             */
/*   Updated: 2021/12/04 01:08:22 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	check_starvation(t_env *env, t_philo current_philo)
{
	pthread_mutex_lock(&current_philo.death_mutex);
	if (get_current_time() - current_philo.last_meal >= env->params[time_to_die])
	{
		env->end_simulation = true;
		print_action_message(&current_philo,
			RED_TEXT"died"COLOR_ESC, STOP_PRINT_SIG);
	}
	pthread_mutex_unlock(&current_philo.death_mutex);
}

static void	*watcher_life_cycle(void *arg)
{
	t_env			*env;
	int				philo_index;
	unsigned int	stack_status;

	env = (t_env *)arg;
	while (!env->end_simulation)
	{
		usleep(10);
		philo_index = -1;
		stack_status = env->params[philo_number];
		while (++philo_index < (int)env->params[philo_number])
		{
			if (!env->philo_list[philo_index].start_time)
				continue;
			if (env->philo_list[philo_index].end_thread == false)
				check_starvation(env, env->philo_list[philo_index]);
			else
				stack_status--;
		}
		if (stack_status == 0)
			env->end_simulation = true;
	}
	philo_index = -1;
	while (++philo_index < (int)env->params[philo_number])
		env->philo_list[philo_index].end_thread = true;
	return (NULL);
}

static void	*philo_life_cycle(void *arg)
{
	t_philo					*philo;
	int						action_index;
	static t_philo_action	*philo_action[ACTION_NUMBER] = {
		&philo_eat,
		&philo_sleep,
		&philo_think
	};

	action_index = 0;
	philo = (t_philo *)arg;
	while (!philo->end_thread)
	{
		philo_action[action_index](philo);
		action_index++;
		action_index %= ACTION_NUMBER;
	}
	return (NULL);
}

void	setting_dinner(t_env *env)
{
	unsigned int	i;
	int				failed_philo;
	int				failed_watcher;

	failed_watcher = pthread_create(&env->w_tid, NULL,
		watcher_life_cycle, (void *)env);
	if (!failed_watcher)
	{
		i = -1;
		env->start_time = get_current_time();
		while (++i < env->params[philo_number])
		{
			env->philo_list[i].last_meal = get_current_time();
			env->philo_list[i].start_time = env->start_time;
			failed_philo = pthread_create(&env->philo_list[i].p_tid, NULL,
					philo_life_cycle, (void *)&env->philo_list[i]);
			if (failed_philo && --i)
			{
				error_handler(ERR_THREAD);
				env->end_simulation = true;
				break ;
			}
		}
		while (i--)
			pthread_join(env->philo_list[i].p_tid, NULL);
		pthread_join(env->w_tid, NULL);
	}
	else
		error_handler(ERR_THREAD);
}
