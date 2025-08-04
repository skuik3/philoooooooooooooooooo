/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 21:04:30 by skuik             #+#    #+#             */
/*   Updated: 2025/08/04 17:36:42 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_philo_mutexes(t_state *state)
{
	int	i;

	i = 0;
	while (i < state->config->philo_nbr)
	{
		pthread_mutex_destroy(&state->philos[i]->food_lock);
		i++;
	}
}

static void	destroy_forks(t_state *state)
{
	int	i;

	i = 0;
	while (i < state->config->philo_nbr)
	{
		pthread_mutex_destroy(&state->forks[i]);
		i++;
	}
}

static void	free_philo_structs(t_state *state)
{
	int	i;

	i = 0;
	while (i < state->config->philo_nbr)
	{
		free(state->philos[i]);
		state->philos[i] = NULL;
		i++;
	}
}

void	free_mutex(t_state *state)
{
	if (!state || !state->config)
		return ;
	destroy_philo_mutexes(state);
	destroy_forks(state);
	pthread_mutex_destroy(&state->simulation_lock);
	pthread_mutex_destroy(&state->print_lock);
	pthread_mutex_destroy(&state->state_lock);
}

void	free_all(t_state *state)
{
	if (!state)
		return ;
	free_mutex(state);
	if (state->philos)
	{
		free_philo_structs(state);
		free(state->philos);
		state->philos = NULL;
	}
	if (state->forks)
	{
		free(state->forks);
		state->forks = NULL;
	}
}
