/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pick_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 00:30:51 by abenaiss          #+#    #+#             */
/*   Updated: 2022/08/15 22:57:30 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static short	is_fork_available(t_philo *philo, t_fork *fork)
{
	if (fork->is_fork_used == false && (philo->id + 1) != fork->past_users)
		return (1);
	return (0);
}

static short	wait_turn(t_philo *philo, t_fork *fork)
{
	while (!philo->end_thread)
	{
		if (is_fork_available(philo, fork))
			return (1);
		usleep(10);
	}
	return (0);
}

static void	attribute_fork(t_philo *philo, t_fork *fork)
{
	fork->is_fork_used = true;
	fork->past_users = philo->id + 1;
	print_action_message(philo, GREEN_TEXT"picked a fork"COLOR_ESC,
		VALID_PRINT_SIG);
}

static short	execute_philo(t_philo *philo)
{
	while (!philo->end_thread)
		usleep(10);
	return (0);
}

int	get_fork(t_philo *philo)
{
	if (philo->small_fork == philo->big_fork)
		return (execute_philo(philo));
	pthread_mutex_lock(&philo->small_fork->fork_lock);
	if(is_fork_available(philo, philo->small_fork))
	{
		pthread_mutex_lock(&philo->big_fork->fork_lock);
		if (is_fork_available(philo, philo->big_fork))
		{
			attribute_fork(philo, philo->big_fork);
			attribute_fork(philo, philo->small_fork);
			pthread_mutex_unlock(&philo->big_fork->fork_lock);
			pthread_mutex_unlock(&philo->small_fork->fork_lock);
			return (1);
		}
		pthread_mutex_unlock(&philo->big_fork->fork_lock);
	}
	pthread_mutex_unlock(&philo->small_fork->fork_lock);
	wait_turn(philo, philo->small_fork);
	wait_turn(philo, philo->big_fork);
	return (get_fork(philo));
}
