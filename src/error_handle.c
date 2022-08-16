/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/14/07 14:34:00 by abenaiss          #+#    #+#             */
/*   Updated: 2022/14/07 14:36:22 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

short	error_handler(short error_code)
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
	if (error_code == ERR_MALLOC)
		printf("%s\n", "Internal error, please try again.");
	if (error_code == ERR_THREAD)
		printf("%s\n", "Internal error, please try again.");
	if (error_code == ERR_MUTEX_DEATH || error_code == ERR_MUTEX_PRINT
		|| error_code == ERR_MUTEX_FORK)
		printf("%s\n", "Internal error, please try again.");
	if (error_code == ERR_NEGATIVE)
		printf("%s\n", "No passed parameter should be negative.");
	if (error_code == ERR_ZERO)
		printf("%s\n", "No passed parameter should be null.");
	return (1);
}
