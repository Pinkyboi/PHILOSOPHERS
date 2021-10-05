/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pick_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 15:10:17 by abenaiss          #+#    #+#             */
/*   Updated: 2021/10/05 18:35:46 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int min(int number1, int number2)
{
    if(number1 < number2)
        return (number1);
    return (number2);
}

int max(int number1, int number2)
{
    if(number1 > number2)
        return (number1);
    return (number2);
}

int     get_smaller_fork(int philo_id)
{
    return min(philo_id , (philo_id + 1) % master->game_rules.philo_number);
}

int     get_bigger_fork(int philo_id)
{
    return max(philo_id , (philo_id + 1) % master->game_rules.philo_number);
}

void     lock_forks(t_philosopher *philo)
{
    pthread_mutex_lock(&master->forks[get_smaller_fork(philo->id)]);
    print_action_message(philo->id, "took a fork");
    if (!pthread_mutex_lock(&master->forks[get_bigger_fork(philo->id)]))
    {
        print_action_message(philo->id, "took a fork");
        print_action_message(philo->id, "is eating");
        usleep(philo->game_rules.time_to_eat_us);
        philo->dying_time += philo->game_rules.time_to_die;
        philo->meal_number++;
        if (philo->meal_number == master->game_rules.number_of_times_eat)
            master->full_counter++;
        if (master->full_counter == master->game_rules.philo_number)
            master->first_blood = 1;
        pthread_mutex_unlock(&master->forks[get_bigger_fork(philo->id)]);
    }
    else
        while(1)
            if (get_current_time() >= philo->dying_time)
                print_action_message(philo->id, "died");
    pthread_mutex_unlock(&master->forks[get_smaller_fork(philo->id)]);
}