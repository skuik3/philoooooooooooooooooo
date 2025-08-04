/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_funcs2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:50:40 by skuik             #+#    #+#             */
/*   Updated: 2025/08/05 01:09:10 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_death_or_done(t_state *state, int i)
{
	int full_count;

	pthread_mutex_lock(&state->state_lock);
	full_count = state->full_philos;
	pthread_mutex_unlock(&state->state_lock);
	if (full_count == state->config->philo_nbr)
		print_it(state->philos[i], "everyone has finished the meals");
	else
		print_it(state->philos[i], "died");
}

void	*is_dead(t_state *state, int i)
{
	print_death_or_done(state, i);
	pthread_mutex_unlock(&state->philos[i]->food_lock);
	pthread_mutex_lock(&state->simulation_lock);
	state->is_running = 0;
	pthread_mutex_unlock(&state->simulation_lock);
	return (NULL);
}

int	is_running(t_philo *philo)
{
	int	running;

	pthread_mutex_lock(&philo->state->simulation_lock);
	running = philo->state->is_running;
	pthread_mutex_unlock(&philo->state->simulation_lock);
	return (running);
}

static int	is_invalid_config(t_config *config)
{
	if (config->philo_nbr < 1 || config->philo_nbr > 200)
		return (1);
	if (config->t_die <= 0 || config->t_eat <= 0 || config->t_sleep <= 0)
		return (1);
	if (config->snacks <= -2)
		return (1);
	return (0);
}

int	configload(char **argv, t_config *config, int argc)
{
	config->start_time = 0;
	config->philo_nbr = ft_atoi(argv[1]);
	config->t_die = ft_atoi(argv[2]);
	config->t_eat = ft_atoi(argv[3]);
	config->t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		config->snacks = ft_atoi(argv[5]);
	else
		config->snacks = -1;
	if (is_invalid_config(config))
	{
		printf("Error\n");
		return (ERROR);
	}
	return (SUCCESS);
}
