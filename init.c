/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:28:13 by skuik             #+#    #+#             */
/*   Updated: 2025/08/04 18:18:39 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_philo_fields(t_state *state, int i)
{
	state->philos[i] = malloc(sizeof(t_philo));
	if (!state->philos[i])
		return (ERROR);
	state->philos[i]->fork1 = 0;
	state->philos[i]->fork2 = 0;
	state->philos[i]->id = i + 1;
	state->philos[i]->meal_count = 0;
	state->philos[i]->lastmeal = 0;
	state->philos[i]->state = state;
	state->philos[i]->config = state->config;
	state->philos[i]->fed = 0;
	if (pthread_mutex_init(&state->philos[i]->food_lock, NULL))
		return (ERROR);
	return (SUCCESS);
}

int	init_philos(t_state *state, int nbr_philo)
{
	int	i;

	i = 0;
	state->philos = malloc(sizeof(t_philo *) * nbr_philo);
	if (!state->philos)
		return (ERROR);
	state->config->start_time = get_time();
	while (i < nbr_philo)
	{
		if (init_philo_fields(state, i))
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

static int	init_mutexes_core(t_state *state)
{
	if (pthread_mutex_init(&state->print_lock, NULL))
		return (ERROR);
	if (pthread_mutex_init(&state->simulation_lock, NULL))
		return (ERROR);
	if (pthread_mutex_init(&state->state_lock, NULL))
		return (ERROR);
	return (SUCCESS);
}

int	init_mutex(t_state *state, int nbr_philo)
{
	int	i;

	i = 0;
	if (init_mutexes_core(state))
		return (ERROR);
	state->forks = malloc(sizeof(pthread_mutex_t) * nbr_philo);
	if (!state->forks)
		return (ERROR);
	while (i < nbr_philo)
	{
		if (pthread_mutex_init(&state->forks[i], NULL))
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

int	init_state(t_state *state, t_config *config)
{
	state->is_running = 1;
	state->config = config;
	state->all_meal_count = 0;
	state->full_philos = 0;
	if (init_mutex(state, config->philo_nbr))
		return (ERROR);
	if (init_philos(state, config->philo_nbr))
		return (ERROR);
	return (SUCCESS);
}
