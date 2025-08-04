/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 13:44:03 by skuik             #+#    #+#             */
/*   Updated: 2025/08/05 01:00:23 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_digit(int c)
{
	if ((c >= '0' && c <= '9') || c == '+')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		if ((result * sign) > INT_MAX || (result * sign) < INT_MIN)
			return (-1);
		str++;
	}
	return ((int)(result * sign));
}

static int	is_numeric_string(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	while (str[i])
	{
		if (!is_digit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_args(char *argv[], int argc)
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
	{
		printf("Error\n");
		return (ERROR);
	}
	while (argv[i])
	{
		if (!is_numeric_string(argv[i]))
		{
			printf("Error\n");
			return (ERROR);
		}
		i++;
	}
	return (SUCCESS);
}

void	*philo_actions(void *arg)
{
	t_philo	*philo;
	int		running;

	philo = (t_philo *)arg;
	philo->lastmeal = get_time();
	if (philo->id % 2 == 0)
		usleep(100);
	while(1)
	{
		pthread_mutex_lock(&philo->state->simulation_lock);
		running = philo->state->is_running;
		pthread_mutex_unlock(&philo->state->simulation_lock);
		if (!running)
			break;
		take_forks(philo);
		is_eating(philo);
		put_forks(philo);
		is_sleeping(philo);
		is_thinking(philo);
	}
	return (NULL);
}
