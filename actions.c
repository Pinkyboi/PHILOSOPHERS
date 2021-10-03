/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 14:54:43 by abenaiss          #+#    #+#             */
/*   Updated: 2021/10/03 18:58:28 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    print_action_message(int philo_id, const char* message)
{
    struct timeval  tv;
    
    gettimeofday(&tv, NULL);
    pthread_mutex_lock(&master->output_mutex);
    if (master->first_blood != -1)
    {
        printf("%ld %d\t%s\n",
            get_milliseconds(tv.tv_sec, tv.tv_usec), master->first_blood, "died");
        exit(0);
    }
    printf("%ld %d\t%s\n", get_milliseconds(tv.tv_sec, tv.tv_usec), philo_id, message);
    pthread_mutex_unlock(&master->output_mutex);
}

void    philo_sleep(t_philosopher *philo)
{
    if (get_current_time() + philo->game_rules.time_to_sleep > philo->dying_time)
        master->first_blood = philo->id;
    print_action_message(philo->id, "is sleeping");
    usleep(philo->game_rules.time_to_sleep * 1000);
}

void     lock_forks(t_philosopher *philo)
{
    pthread_mutex_lock(&master->forks[philo->id]);
    pthread_mutex_lock(&master->forks[(philo->id + 1) % master->game_rules.philo_number]);
    print_action_message(philo->id, "is eating");
    usleep(philo->game_rules.time_to_eat * 1000);
    philo->dying_time += philo->game_rules.time_to_die;
    pthread_mutex_unlock(&master->forks[(philo->id + 1) % master->game_rules.philo_number]);
    pthread_mutex_unlock(&master->forks[philo->id]);
}

void    unlock_forks(t_philosopher *philo)
{
    pthread_mutex_unlock(&master->forks[philo->id]);
    pthread_mutex_unlock(&master->forks[(philo->id + 1) % master->game_rules.philo_number]);
}

void    philo_eat(t_philosopher* philo)
{
    int     id;

    id = philo->id;
    
    if (get_current_time() + philo->game_rules.time_to_eat > philo->dying_time)
        master->first_blood = philo->id;
    if (philo->id != (philo->id + 1) % master->game_rules.philo_number)
        lock_forks(philo);
    // if (lock_forks(philo))
//     {
//         print_action_message(id, "is eating");
//         usleep(philo->game_rules.time_to_eat);
//         philo->dying_time += philo->game_rules.time_to_die;
//         unlock_forks(philo);
//     }
// }
}
void    philo_think(t_philosopher *philo)
{
    if (get_current_time() > philo->dying_time)
        master->first_blood = philo->id;
    print_action_message(philo->id, "is thinking");
}
























































































// void    philo_eat(t_philosopher *philo)
// {
//     int id;

//     id = philo->id;
//     if (get_current_time() + philo->game_rules.time_to_eat > philo->dying_time)
//     {
//         pthread_mutex_lock(&g_mutex);
//         master->first_blood = philo->id;
//         pthread_mutex_unlock(&g_mutex);
//     }
//     pthread_mutex_lock(&g_mutex[id]);
//     pthread_mutex_lock(&g_mutex[id+1]);

//     print_action_message(id, "is eating");
//     usleep(philo->game_rules.time_to_eat);
//     philo->dying_time += philo->game_rules.time_to_die;

//     // master->forks[id] = 0;
//     // master->forks[(id + 1) % master->game_rules.philo_number] = 0;
//     pthread_mutex_unlock(&g_mutex[id]);
//     pthread_mutex_unlock(&g_mutex[id+1]);

    
// }
