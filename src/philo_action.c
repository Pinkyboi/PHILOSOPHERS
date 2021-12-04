/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 14:57:18 by abenaiss          #+#    #+#             */
/*   Updated: 2021/12/04 01:09:52 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	int		fork_number;

	fork_number = philo->params[philo_number];
	if (get_fork(philo))
	{
		pthread_mutex_lock(&philo->death_mutex);
		if (!philo->end_thread)
		{
			pthread_mutex_unlock(&philo->death_mutex);
			philo->last_meal = get_current_time();
			print_action_message(philo, GREEN_TEXT"is eating"COLOR_ESC,
				VALID_PRINT_SIG);
			msleep(&philo->end_thread, philo->params[time_to_eat]);
			clean_fork(philo);
			if (++philo->eat_count == philo->params[max_eat_count])
				philo->end_thread = true;
		}
		else
			pthread_mutex_unlock(&philo->death_mutex);
	}
}

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->death_mutex);
	if (!philo->end_thread)
	{
		pthread_mutex_unlock(&philo->death_mutex);
		print_action_message(philo, GREEN_TEXT"is sleeping"COLOR_ESC,
			VALID_PRINT_SIG);
		msleep(&philo->end_thread, philo->params[time_to_sleep]);
	}
	else
		pthread_mutex_unlock(&philo->death_mutex);
}

void	philo_think(t_philo *philo)
{
	if (!philo->end_thread)
		print_action_message(philo, GREEN_TEXT"is thinking"COLOR_ESC,
			VALID_PRINT_SIG);
}
