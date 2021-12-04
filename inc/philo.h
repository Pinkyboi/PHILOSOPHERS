/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 21:55:35 by abenaiss          #+#    #+#             */
/*   Updated: 2021/12/04 14:49:45 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>

# define PARAM_NUMBER 5
# define ACTION_NUMBER 3

# define ERR_WRONG_PARAM_NUMBER 1
# define ERR_NEGATIVE 2
# define ERR_ZERO 3
# define ERR_MALLOC 4
# define ERR_MUTEX 5

# define RED_TEXT "\033[0;31m"
# define GREEN_TEXT "\033[0;32m"
# define COLOR_ESC "\033[0m"

# define VALID_PRINT_SIG 1
# define STOP_PRINT_SIG 0

enum
{
	false,
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

typedef struct s_fork
{
	pthread_mutex_t	fork_lock;
	unsigned int	past_users;
	short			is_fork_used;
}					t_fork;

typedef struct s_philo
{
	short			end_thread;
	unsigned int	id;
	unsigned int	last_meal;
	unsigned int	start_time;
	unsigned int	eat_count;
	unsigned int	*params;
	t_fork			*small_fork;
	t_fork			*big_fork;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	death_mutex;
	pthread_t		p_tid;
}					t_philo;

typedef struct s_env
{
	short			end_simulation;
	unsigned int	params[PARAM_NUMBER];
	unsigned int	start_time;
	t_fork			*fork_list;
	t_philo			*philo_list;
	pthread_mutex_t	print_mutex;
	pthread_t		w_tid;
}					t_env;

typedef void	t_philo_action(t_philo *philo);

long	get_current_time(void);

int		my_atoi(char *string);

short	initialize_env(t_env *env, int argc, char **argv);

t_fork	*get_smaller_fork(int philo_id, t_env *env);
t_fork	*get_bigger_fork(int philo_id, t_env *env);

void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);

void	print_action_message(t_philo *philo,
			const char *message, int print_sig);

void	msleep(short *end_simulation, unsigned int delay_second);

void	setting_dinner(t_env *env);

int		get_fork(t_philo *philo);

void	clean_fork(t_philo *philo);
#endif