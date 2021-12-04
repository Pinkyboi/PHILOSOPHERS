/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_forks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 15:03:06 by abenaiss          #+#    #+#             */
/*   Updated: 2021/12/04 01:10:13 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	min(int number1, int number2)
{
	if (number1 < number2)
		return (number1);
	return (number2);
}

static int	max(int number1, int number2)
{
	if (number1 > number2)
		return (number1);
	return (number2);
}

t_fork	*get_smaller_fork(int philo_id, t_env *env)
{
	unsigned int	fork_number;

	fork_number = env->params[philo_number];
	return (&env->fork_list[min(philo_id, (philo_id + 1) % fork_number)]);
}

t_fork	*get_bigger_fork(int philo_id, t_env *env)
{
	unsigned int	fork_number;

	fork_number = env->params[philo_number];
	return (&env->fork_list[max(philo_id, (philo_id + 1) % fork_number)]);
}
