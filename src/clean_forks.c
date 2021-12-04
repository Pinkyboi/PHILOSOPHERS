/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_forks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 00:37:49 by abenaiss          #+#    #+#             */
/*   Updated: 2021/12/04 00:13:43 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_fork(t_philo *philo)
{
	philo->big_fork->is_fork_used = false;
	print_action_message(philo,
		GREEN_TEXT"dropped a fork"COLOR_ESC, VALID_PRINT_SIG);
	philo->small_fork->is_fork_used = false;
	print_action_message(philo,
		GREEN_TEXT"dropped a fork"COLOR_ESC, VALID_PRINT_SIG);
}
