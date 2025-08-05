/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42prague.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:26:25 by skuik             #+#    #+#             */
/*   Updated: 2025/08/05 00:05:40 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_philo_death(t_state *state, int i)
{
	long	time;
	int		meal_count;

	time = get_time() - state->philos[i]->lastmeal;
	meal_count = state->philos[i]->meal_count;
	if (meal_count > 0 && time > (long)state->config->t_die)
		return (1);
	return (0);
}

void	print_it(t_philo *philo, char *msg)
{
	long	now;
	int		running;

	pthread_mutex_lock(&philo->state->print_lock);
	now = get_time() - philo->state->config->start_time;
	pthread_mutex_lock(&philo->state->simulation_lock);
	running = philo->state->is_running;
	pthread_mutex_unlock(&philo->state->simulation_lock);
	if (running)
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
