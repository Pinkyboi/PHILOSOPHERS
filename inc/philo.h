/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 11:34:29 by abenaiss          #+#    #+#             */
/*   Updated: 2021/11/13 01:39:46 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdio.h>

#ifndef __PHILO_H__
# define __PHILO_H__

#define USAGE_MESSAGE "Usage: ./philo [philosopher's number] [time to die] [time to eat] [time to sleep] [max number of meals]\n"
#define PARAM_NUMBER 5
#define ACTION_NUMBER 3

enum
{
    curent_user,
    past_user  
};

enum
{
    flase,
    true  
};

enum
{
    philo_number,
    time_to_die,
    time_to_eat,
    time_to_sleep,
    max_eat_count,    
};

typedef struct      s_fork
{
    pthread_mutex_t fork_lock;
    int             users[2];
    int             fork_status;
    int             id;
}                   t_fork;

typedef struct		s_philo
{
    int				id;
    int				eat_count;
    int             last_meal;
    pthread_t       p_tid;
    pthread_t       w_tid;
}                   t_philo;

typedef struct		s_env
{
    long            params[PARAM_NUMBER];
    int             terminate;
    int             philo_full;
    unsigned long   start_time;
    t_fork          *fork_list;
    t_philo         *philo_list;
    pthread_mutex_t print_mutex;
}                   t_env;

t_env   *env;
typedef void    t_philo_action(t_philo *philo);

long    get_current_time(void);

int     my_atoi(char* string);

void    initialize_env(int argc, char** argv);

int     get_smaller_fork(int philo_id);
int     get_bigger_fork(int philo_id);

void    philo_eat(t_philo* philo);
void    philo_sleep(t_philo* philo);
void    philo_think(t_philo* philo);

void    print_action_message(int philo_id, const char* message);

void    msleep(unsigned int delay_second);

void    setting_dinner(void);

int     get_fork(t_philo *philo, t_fork* smaller_fork, t_fork* bigger_fork);

void    clean_fork(t_philo *philo, t_fork *smaller_fork, t_fork *bigger_fork);
#endif