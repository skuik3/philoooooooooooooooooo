/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 11:59:18 by skuik             #+#    #+#             */
/*   Updated: 2025/08/05 00:54:50 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*skinny_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->food_lock);
	print_it(philo, "has taken a fork");
	pthread_mutex_unlock(&philo->food_lock);
	delay(philo->config->t_die);
	pthread_mutex_lock(&philo->food_lock);
	philo->meal_count++;
	pthread_mutex_unlock(&philo->food_lock);
	return (NULL);
}

static void	initial_think_if_even(t_philo *philo)
{
	if (philo->id % 2 != 1)
	{
		is_thinking(philo);
		delay(philo->config->t_eat);
	}
}

void	*philo_process(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->config->snacks == 0)
		return (NULL);
	if (philo->state->config->philo_nbr == 1)
		return (skinny_philo(philo));
	initial_think_if_even(philo);
	while (1)
	{
		if (!is_running(philo))
			return (NULL);
		philo_actions(philo);
	}
	return (NULL);
}

static int	handle_state_checks(t_state *state, int i)
{
	pthread_mutex_lock(&state->philos[i]->food_lock);
	pthread_mutex_lock(&state->state_lock);
	if (check_philo_death(state, i)
		|| state->full_philos == state->config->philo_nbr)
	{
		pthread_mutex_unlock(&state->state_lock);
		return (1);
	}
	pthread_mutex_unlock(&state->state_lock);
	pthread_mutex_unlock(&state->philos[i]->food_lock);
	return (0);
}

void	*routine(void *arg)
{
	t_state	*state;
	int		i;

	state = (t_state *)arg;
	if (state->config->snacks == 0)
		return (NULL);
	while (1)
	{
		i = 0;
		while (i < state->config->philo_nbr)
		{
			if (handle_state_checks(state, i))
				return (is_dead(state, i));
			i++;
		}
		delay(1);
	}
	return (NULL);
}
