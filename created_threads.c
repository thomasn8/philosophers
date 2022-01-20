/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   created_threads.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 00:51:18 by tnanchen          #+#    #+#             */
/*   Updated: 2022/01/20 10:58:56 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*odd_philos_threads(void *arg)
{
	t_table_infos	*table;
	int				n;
	static int		current = -1;
	int				index;

	table = (t_table_infos *)arg;
	n = table->args->n;
	pthread_mutex_lock(&table->mutex);
	current += 1;
	index = current;
	pthread_mutex_unlock(&table->mutex);
	usleep(n * 25);
	if (index + 1 == n)
		usleep(table->args->time_to_eat * 1000);
	if (is_even_or_odd(table->philos[index].id) == EVEN)
		usleep(100);
	while (1)
	{	
		routine_all(index, table, n);
		usleep(1000);
	}
	return (NULL);
}

void	*even_philos_threads(void *arg)
{
	t_table_infos	*table;
	int				n;
	static int		current = -1;
	int				index;

	table = (t_table_infos *)arg;
	n = table->args->n;
	pthread_mutex_lock(&table->mutex);
	current += 1;
	index = current;
	pthread_mutex_unlock(&table->mutex);
	usleep(n * 25);
	if (is_even_or_odd(table->philos[index].id) == ODD)
		usleep(100);
	while (1)
		routine_all(index, table, n);
	return (NULL);
}

static int	thread_error(void)
{
	ft_putstr_fd("Fail to create thread\n", 2);
	return (2);
}

static void	*philo_alone(void *arg)
{
	t_table_infos	*table;

	table = (t_table_infos *)arg;
	usleep(table->args->time_to_die * 1000);
	printf("%s%d 1 died%s\n", RED, table->args->time_to_die, DEFAULT);
	return (NULL);
}

int	one_philo_thread(t_table_infos *table)
{
	pthread_t		th;

	pthread_mutex_init(&(table->mutex), NULL);
	pthread_mutex_init(&(table->mutex2), NULL);
	if (pthread_create(&th, NULL, philo_alone, table) != 0)
		return (thread_error());
	usleep(table->args->time_to_die * 2000);
	pthread_mutex_destroy(&(table->mutex));
	pthread_mutex_destroy(&(table->mutex2));
	free(table->philos);
	free(table->forks);
	printf("%sPhilosophs do not like to philosophize alone%s\n", RED, DEFAULT);
	return (0);
}
