/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sferrad <sferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:00:00 by sferrad           #+#    #+#             */
/*   Updated: 2025/02/24 15:43:06 by sferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	destroy_philosopher_mutexes(t_data *data, int i)
{
	pthread_mutex_destroy(&data->philos[i].meal_count_mutex);
	pthread_mutex_destroy(&data->philos[i].last_meal_time_mutex);
	if (data->number_of_eat != -1)
		pthread_mutex_destroy(&data->philos[i].is_full_mutex);
}

static void	destroy_forks(t_data *data)
{
	int	i;

	if (data->forks)
	{
		i = 0;
		while (i < data->number_of_philo)
		{
			pthread_mutex_destroy(&data->forks[i].fork);
			i++;
		}
		free(data->forks);
	}
}

void	ft_free_ressources(t_data *data)
{
	int	i;

	if (data->philos)
	{
		i = 0;
		while (i < data->number_of_philo)
		{
			destroy_philosopher_mutexes(data, i);
			i++;
		}
		free(data->philos);
	}
	destroy_forks(data);
	pthread_mutex_destroy(&data->end_simulation_mutex);
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->last_meal_mutex);
	pthread_mutex_destroy(&data->finished_mutex);
}
