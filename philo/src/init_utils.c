/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sferrad <sferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:00:00 by sferrad           #+#    #+#             */
/*   Updated: 2025/02/26 17:09:47 by sferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	init_fork(t_fork *fork, int id)
{
	fork->fork_id = id;
	if (pthread_mutex_init(&fork->fork, NULL) != 0)
		return ;
}

void	init_philosopher(t_data *data, int id)
{
	t_philo	*philo;

	philo = &data->philos[id];
	philo->id = id + 1;
	philo->meals_count = 0;
	philo->last_meal_time = get_timestamp();
	philo->left_fork = &data->forks[id];
	philo->right_fork = &data->forks[(id + 1) % data->number_of_philo];
	philo->data = data;
	philo->is_full = false;
	init_philo_mutexes(philo, data);
}

int	init_philosophers_and_forks(t_data *data)
{
	int	i;

	if (data->number_of_philo < 0)
		return (0);
	data->forks = malloc(sizeof(t_fork) * data->number_of_philo);
	if (!data->forks)
		return (0);
	data->philos = malloc(sizeof(t_philo) * data->number_of_philo);
	if (!data->philos)
	{
		free(data->forks);
		return (0);
	}
	i = -1;
	while (++i < data->number_of_philo)
	{
		init_fork(&data->forks[i], i);
		init_philosopher(data, i);
	}
	return (1);
}

int	init_full_mutex(t_philo *philo)
{
	if (pthread_mutex_init(&philo->is_full_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&philo->meal_count_mutex);
		pthread_mutex_destroy(&philo->last_meal_time_mutex);
		return (1);
	}
	return (0);
}

void	init_philo_mutexes(t_philo *philo, t_data *data)
{
	if (pthread_mutex_init(&philo->meal_count_mutex, NULL) != 0)
		return ;
	if (pthread_mutex_init(&philo->last_meal_time_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&philo->meal_count_mutex);
		return ;
	}
	if (data->number_of_eat != -1)
	{
		if (pthread_mutex_init(&philo->is_full_mutex, NULL) != 0)
		{
			pthread_mutex_destroy(&philo->meal_count_mutex);
			pthread_mutex_destroy(&philo->last_meal_time_mutex);
			return ;
		}
	}
}
