/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 22:07:31 by tnanchen          #+#    #+#             */
/*   Updated: 2022/01/08 22:54:41 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* libraries */
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

/* terminal colors */
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define DEFAULT "\033[0m"

/* utils */
# define ODD 1
# define EVEN 2

/************ ARGS ************/
typedef struct s_args
{
	int				n;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	meals_goal;
}	t_args;

/************ TIME ************/
typedef struct s_time
{
	long int		tv_sec;
	int				tv_usec;
	unsigned int	timestamp_in_ms;
	unsigned int	prog_start;
}	t_time;

/************ PHILOS ************/
/* philo states */
# define DEAD 0
# define THINKING 1
# define EATING 2
# define SLEEPING 3

typedef struct s_philo
{
	int				id;
	int				fork_in_hands;
	unsigned int	last_meal;
	unsigned int	count_meals;
	t_time			*timer;
}	t_philo;

/************ FORKS ************/
/* forks states */
# define FREE 0

typedef struct s_fork
{
	int				id;
	int				state;
}	t_fork;

/************ TABLE ************/
typedef struct s_table_infos
{
	t_args			*args;
	t_time			*time;
	t_philo			*philos;
	t_fork			*forks;
	pthread_mutex_t	mutex;
	pthread_mutex_t	mutex2;
}	t_table_infos;

/* philo_utils */
void		ft_putstr_fd(char *s, int fd);
int			ft_atoi(const char *str);
int			is_even_or_odd(int id);
void		get_time_in_ms(t_time *time, unsigned int prog_start);

/* create_table */
int			usage(void);
int			check_args(int ac, char **av, t_args *args);
t_philo		*philos_create(int n, t_time *time);
t_fork		*forks_create(int n);

/* check_end */
int			check_end_looper(t_table_infos *table, int n);

/* created_threads */
void		*odd_philos_threads(void *arg);
void		*even_philos_threads(void *arg);
int			one_philo_thread(t_table_infos *table);

/* routines */
void		routine_all(int index, t_table_infos *table, int n);

/* take_forks */
int			last_meal_check(unsigned int *last_meal, t_time *timer,
				unsigned int time_to_die, unsigned int prog_start);
void		take_forks_and_start_eating(int index, t_table_infos *table, int n);

/* drope_forks */
void		drope_forks_and_sleep(int index, t_table_infos *table, int n);

#endif
