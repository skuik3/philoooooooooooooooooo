/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:28:13 by skuik             #+#    #+#             */
/*   Updated: 2025/08/04 18:18:51 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_threads(t_state *state)
{
	int	i;

	i = 0;
	if (pthread_create(&state->routine, NULL, &routine, state))
		return (ERROR);
	while (i < state->config->philo_nbr)
	{
		if (pthread_create(&state->philos[i]->thread, NULL, &philo_process,
				state->philos[i]))
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

static int	join_threads(t_state *state)
{
	int	i;

	i = 0;
	while (i < state->config->philo_nbr)
	{
		if (pthread_join(state->philos[i]->thread, NULL))
			return (ERROR);
		i++;
	}
	if (pthread_join(state->routine, NULL))
		return (ERROR);
	return (SUCCESS);
}

int	init_thread(t_state *state)
{
	if (create_threads(state))
		return (ERROR);
	if (join_threads(state))
		return (ERROR);
	return (SUCCESS);
}
