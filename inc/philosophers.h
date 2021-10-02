/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 11:52:43 by abenaiss          #+#    #+#             */
/*   Updated: 2021/10/02 18:54:40 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/types.h>

typedef struct  s_fork
{
    int         is_used;
    
}               t_fork;

typedef struct      s_rules
{
    unsigned int             philo_number;
    unsigned int             eating_time;
    unsigned int             sleeping_time;
    unsigned int             time_to_die;
}                   t_rules;

typedef struct      s_philosopher
{
    unsigned int    id;
    t_rules         game_rules;
    short           is_eating;
    short           is_sleeping;
    short           is_thinking;
    unsigned int    last_meal;
    unsigned int    dying_time;
    t_fork          *left_fork;
    t_fork          *right_fork;
}                   t_philosopher;

typedef struct      s_ochestrator
{
    t_rules         game_rules;
    t_philosopher   *philo_list;
    t_fork          *fork_list;
    int             *forks;
    int             first_blood;
}                   t_orchestrator;

pthread_mutex_t     g_mutex;
t_orchestrator      *master;

int ft_atoi(char* str);