/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 14:58:39 by abenaiss          #+#    #+#             */
/*   Updated: 2021/12/04 01:10:35 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action_message(t_philo *philo, const char *message, int print_sig)
{
	long			event_time;
	static short	print_status = VALID_PRINT_SIG;

	pthread_mutex_lock(philo->print_mutex);
	if (print_status == VALID_PRINT_SIG)
	{
		event_time = get_current_time() - philo->start_time;
		printf("[%ld ms] philosopher id: %d %s\n",
			event_time, philo->id + 1, message);
		print_status = print_sig;
	}
	pthread_mutex_unlock(philo->print_mutex);
}
