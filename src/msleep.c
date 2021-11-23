/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:02:57 by abenaiss          #+#    #+#             */
/*   Updated: 2021/11/12 23:38:18 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	msleep(short *terminate, unsigned int delay_second)
{
	int	end_time;

	end_time = get_current_time() + delay_second;
	while (end_time > get_current_time())
	{
		if (*terminate)
			return ;
		usleep(10);
	}
}
