/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_forks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 00:37:49 by abenaiss          #+#    #+#             */
/*   Updated: 2021/11/20 09:42:54 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    clean_fork(t_philo *philo, t_fork *smaller_fork, t_fork *bigger_fork)
{
    bigger_fork->users[curent_user] = -1;
    bigger_fork->users[past_user] = philo->id;
    print_action_message(philo, GREEN_TEXT"dropped a fork"COLOR_ESC);
    smaller_fork->users[curent_user] = -1;
    smaller_fork->users[past_user] = philo->id;
    print_action_message(philo, GREEN_TEXT"dropped a fork"COLOR_ESC);
}