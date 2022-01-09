/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_table.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 19:42:19 by tnanchen          #+#    #+#             */
/*   Updated: 2022/01/09 11:48:18 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	arg_error(char *param, char *message)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd(param, 2);
	ft_putstr_fd(DEFAULT, 2);
	ft_putstr_fd(message, 2);
	return (-1);
}

static void	save_args(int ac, char **av, t_args *args)
{
	args->n = atoi(av[1]);
	args->time_to_die = atoi(av[2]);
	args->time_to_eat = atoi(av[3]);
	args->time_to_sleep = atoi(av[4]);
	if (ac == 6)
		args->meals_goal = atoi(av[5]);
	else
		args->meals_goal = 0;
}

int	check_args(int ac, char **av, t_args *args)
{
	save_args(ac, av, args);
	if (args->n <= 0)
		return (arg_error("number_of_philosophers",
				" must be a positiv number greater than 0\n"));
	if (args->time_to_die <= 0)
		return (arg_error("time_to_die",
				" must be a positiv number greater than 0\n"));
	args->time_to_die += 5;
	if (args->time_to_eat <= 0)
		return (arg_error("time_to_eat",
				" must be a positiv number greater than 0\n"));
	if (args->time_to_sleep <= 0)
		return (arg_error("time_to_sleep",
				" must be a positiv number greater than 0\n"));
	if (ac == 6 && args->meals_goal <= 0)
		return (arg_error("number_of_times_each_philosopher_must_eat",
				" must be a positiv number greater than 0\n"));
	return (0);
}

t_philo	*philos_create(int n, t_time *time)
{
	t_philo	*philos;
	t_time	timer;
	int		i;

	philos = malloc(n * sizeof(t_philo));
	if (!philos)
		return (NULL);
	i = -1;
	get_time_in_ms(&timer, time->prog_start);
	while (++i < n)
	{
		philos[i].id = i + 1;
		philos[i].fork_in_hands = 0;
		philos[i].last_meal = time->timestamp_in_ms;
		philos[i].count_meals = 0;
		philos[i].timer = &timer;
		printf("%d %s%d is thinking%s\n",
			philos[i].last_meal, MAGENTA, philos[i].id, DEFAULT);
	}
	return (philos);
}

t_fork	*forks_create(int n)
{
	t_fork	*forks;
	int		i;

	forks = malloc(n * sizeof(t_fork));
	if (!forks)
		return (NULL);
	i = -1;
	while (++i < n)
	{
		forks[i].id = i + 1;
		forks[i].state = FREE;
	}
	return (forks);
}
