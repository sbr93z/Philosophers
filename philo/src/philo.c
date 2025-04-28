/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sferrad <sferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:05:00 by sferrad           #+#    #+#             */
/*   Updated: 2025/02/26 17:00:32 by sferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philo)
	{
		if (pthread_create(&data->philos[i].thread_id, NULL, routine,
				&data->philos[i]) != 0)
			return (0);
		if (pthread_create(&data->philos[i].death_thread_id, NULL, check_death,
				&data->philos[i]) != 0)
			return (0);
		i++;
	}
	i = 0;
	while (i < data->number_of_philo)
	{
		if (pthread_join(data->philos[i].thread_id, NULL) != 0)
			return (0);
		if (pthread_join(data->philos[i].death_thread_id, NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	start_simulation(t_data *data)
{
	data->start_simulation = get_timestamp();
	data->end_simulation = 0;
	if (!create_threads(data))
		return (0);
	return (1);
}

void	handle_one_philo(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	data->start_simulation = get_timestamp();
	pthread_mutex_lock(&philo->left_fork->fork);
	print_status(data, philo->id, "has taken a fork");
	handmade_usleep(data->time_to_die, data);
	pthread_mutex_lock(&data->print_mutex);
	printf("%ld %d died\n", get_timestamp() - data->start_simulation,
		philo->id);
	pthread_mutex_unlock(&data->print_mutex);
	pthread_mutex_unlock(&philo->left_fork->fork);
	return ;
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 5)
		return (printf("ERROR: Not enough arguments\n"), 1);
	if (!init_data(&data, ac, av))
		return (printf("ERROR: Invalid arguments\n"), 1);
	if (data.number_of_philo == 1)
	{
		handle_one_philo(&data.philos[0]);
		ft_free_ressources(&data);
		return (0);
	}
	if (!parsing(data, ac, av) || !start_simulation(&data))
	{
		printf("ERROR: Invalid arguments or thread creation failed\n");
		ft_free_ressources(&data);
		return (1);
	}
	ft_free_ressources(&data);
	return (0);
}
