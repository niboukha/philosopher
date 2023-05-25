/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboukha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 10:11:04 by niboukha          #+#    #+#             */
/*   Updated: 2023/05/25 15:47:06 by niboukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	help_function(t_philo *f)
{
	ft_usleep(f->data.time_to_sleep);
	ft_print(f, "is thinking", 0);
}

void	*philosophers(void *p)
{
	t_philo	*f;

	f = (t_philo *)p;
	while (1)
	{
		pthread_mutex_lock(&f->data.forks[f->id - 1]);
		ft_print(f, "has taken a fork", 0);
		pthread_mutex_lock(&f->data.forks[f->id
			% f->data.number_of_philosophers]);
		ft_print(f, "has taken a fork", 0);
		ft_print(f, "is eating", 0);
		ft_usleep(f->data.time_to_eat);
		pthread_mutex_lock(&(f->mutex->p));
		if (f->data.number_eat != -1)
			f->data.number_eat--;
		f->last_meal = calcul_time_ms();
		pthread_mutex_unlock(&(f->mutex->p));
		pthread_mutex_unlock(&f->data.forks[f->id - 1]);
		pthread_mutex_unlock(&f->data.forks[f->id
			% f->data.number_of_philosophers]);
		ft_print(f, "is sleeping", 0);
		help_function(f);
	}
}

void	init_philo(char **av, int ac, t_philo *f)
{
	int		i;
	t_mutex	*mut;

	f->data.forks = malloc(sizeof(pthread_mutex_t) * ft_atoi(av[1]));
	mut = malloc(sizeof(t_mutex));
	pthread_mutex_init(&(mut->print), NULL);
	pthread_mutex_init(&(mut->p), NULL);
	i = 0;
	while (i < ft_atoi(av[1]))
	{
		if (ac == 6)
			f[i].data.number_eat = ft_atoi(av[5]);
		else
			f[i].data.number_eat = -1;
		f[i].data.number_of_philosophers = ft_atoi(av[1]);
		f[i].data.time_to_die = ft_atoi(av[2]);
		f[i].data.time_to_eat = ft_atoi(av[3]);
		f[i].data.time_to_sleep = ft_atoi(av[4]);
		f[i].id = i + 1;
		f[i].data.forks = f->data.forks;
		f[i].mutex = mut;
		pthread_mutex_init(&(f[i].data.forks[i]), NULL);
		i++;
	}
}

int	main(int ac, char **av)
{
	pthread_t	*th;
	t_philo		*f;
	int			i;

	if (ac == 5 || ac == 6)
	{
		f = malloc(sizeof(t_philo) * ft_atoi(av[1]));
		th = malloc(sizeof(pthread_t) * ft_atoi(av[1]));
		if (check_args(av, ac) == -1 || check_args(av, ac) == -2)
			return (0);
		init_philo(av, ac, f);
		i = -1;
		while (++i < ft_atoi(av[1]))
		{
			f[i].start_time = calcul_time_ms();
			f[i].last_meal = calcul_time_ms();
			if (pthread_create(&th[i], NULL, philosophers, &f[i]) == -1)
				return (print_error());
			usleep(100);
		}
		stop_phils(f);
		destroy_mut(f);
	}
	return (0);
}
