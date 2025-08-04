/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 11:58:47 by skuik             #+#    #+#             */
/*   Updated: 2025/08/04 17:59:09 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	handle_error(t_state *state, int is_error)
{
	if (is_error && state)
		free_all(state);
	return (EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	t_state		state;
	t_config	config;
	int			err;

	err = 0;
	if (check_args(argv, argc) || configload(argv, &config, argc))
		return (EXIT_FAILURE);
	if (init_state(&state, &config))
		return (EXIT_FAILURE);
	err = init_thread(&state);
	if (err)
		return (handle_error(&state, err));
	free_all(&state);
	return (EXIT_SUCCESS);
}
