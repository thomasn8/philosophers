/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 22:12:10 by tnanchen          #+#    #+#             */
/*   Updated: 2022/01/09 10:43:53 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_time_in_ms(t_time *time, unsigned int prog_start)
{	
	gettimeofday((struct timeval *)time, NULL);
	time->timestamp_in_ms = (time->tv_sec * 1000 + time->tv_usec / 1000)
		- prog_start;
}

int	is_even_or_odd(int id)
{
	if (id % 2)
		return (ODD);
	return (EVEN);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
		write(fd, s++, 1);
}

int	usage(void)
{
	char	*msg1;
	char	*msg2;

	msg1 = "usage: ./philo number_of_philosophers time_to_die time_to_eat";
	msg2 = " time_to_sleep [number_of_times_each_philosopher_must_eat]\n";
	ft_putstr_fd(msg1, 2);
	ft_putstr_fd(msg2, 2);
	return (1);
}

int	ft_atoi(const char *str)
{
	int	sign;
	int	res;

	sign = 1;
	res = 0;
	while (*str == '\t' || *str == '\n' || *str == '\v' || *str == '\f'
		|| *str == '\r' || *str == ' ')
		str++;
	if (*str == '-')
		sign *= -1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + *str - '0';
		str++;
	}
	return (res * sign);
}
