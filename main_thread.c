/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 22:05:53 by tnanchen          #+#    #+#             */
/*   Updated: 2022/01/20 16:47:06 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	thread_error(void)
{
	ft_putstr_fd("Fail to create thread\n", 2);
	return (2);
}

static int	free_all(t_table_infos *table)
{
	free(table->philos);
	free(table->forks);
	return (1);
}

static int	main_thread(t_table_infos *table, int n)
{
	pthread_t		*th;
	int				i;
	void			*(*function_ptr)();

	th = malloc(n * sizeof(pthread_t));
	if (!th)
		return (thread_error());
	i = -1;
	if (is_even_or_odd(n) == 1)
		function_ptr = odd_philos_threads;
	else
		function_ptr = even_philos_threads;
	pthread_mutex_init(&(table->mutex), NULL);
	pthread_mutex_init(&(table->mutex2), NULL);
	while (++i < n)
	{
		if (pthread_create(&th[i], NULL, function_ptr, table) != 0)
			return (thread_error());
	}
	if (check_end_looper(table, n))
		return (free_all(table));
	return (0);
}

int	main(int ac, char **av)
{
	t_args			args;
	t_time			time;
	t_philo			*philos;
	t_fork			*forks;
	t_table_infos	table;

	if (ac < 5 || ac > 6)
		return (usage());
	if (check_args(ac, av, &args) < 0)
		return (usage());
	gettimeofday((struct timeval *)&time, NULL);
	time.prog_start = time.tv_sec * 1000 + time.tv_usec / 1000;
	get_time_in_ms(&time, time.prog_start);
	printf("%d %sPROG START%s\n", time.timestamp_in_ms, GREEN, DEFAULT);
	philos = philos_create(args.n, &time);
	forks = forks_create(args.n);
	table.args = &args;
	table.time = &time;
	table.philos = philos;
	table.forks = forks;
	if (args.n == 1)
		return (one_philo_thread(&table));
	return (main_thread(&table, args.n));
}
