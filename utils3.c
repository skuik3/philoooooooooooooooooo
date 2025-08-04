/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:26:25 by skuik             #+#    #+#             */
/*   Updated: 2025/08/04 20:00:04 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_philo_death(t_state *state, int i)
{
	long	time;

	time = get_time() - state->philos[i]->lastmeal;
	if (state->philos[i]->meal_count > 0 && time > (long)state->config->t_die)
		return (1);
	return (0);
}

void	print_it(t_philo *philo, char *msg)
{
	long	now;

	pthread_mutex_lock(&philo->state->print_lock);
	now = get_time() - get_long(&philo,philo->state->print_lock);
	if (philo->state->is_running)
		printf("%ld\t%d %s\n", now, philo->id, msg);
	pthread_mutex_unlock(&philo->state->print_lock);
}

unsigned long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	delay(int duration)
{
	unsigned long	start_time;

	start_time = get_time();
	while (get_time() - start_time < (unsigned long)duration)
	{
		usleep(1);
	}
}

long get_long(t_philo *philo, long val)
{
	long returnable;
	pthread_mutex_lock(&philo->food_lock);
	returnable = val;
	pthread_mutex_unlock(&philo->food_lock);
	return returnable;
	
}