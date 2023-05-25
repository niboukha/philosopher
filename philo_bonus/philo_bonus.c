/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboukha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:19:36 by niboukha          #+#    #+#             */
/*   Updated: 2023/05/25 18:51:27 by niboukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*philosophers(void *p)
{
	t_philo	*f;

	f = (t_philo *)p;
	while (1)
	{
		sem_wait(f->semaphore->forks);
		ft_print(f, "has taken a left fork", 0);
		sem_wait(f->semaphore->forks);
		ft_print(f, "has taken a right fork", 0);
		ft_print(f, "is eating", 0);
		gettimeofday(&f->last_meal, NULL);
		if (f->data.number_eat != -1)
			f->data.number_eat--;
		ft_usleep(f->data.time_to_eat);
		sem_post(f->semaphore->forks);
		sem_post(f->semaphore->forks);
		ft_print(f, "is sleeping", 0);
		ft_usleep(f->data.time_to_sleep);
		ft_print(f, "is thinking", 0);
		if (f->data.number_eat == 0)
			exit(1);
	}
	return (NULL);
}

void	open_semaphore(char **av, t_sem	*semaphore)
{
	sem_unlink("forks");
	sem_unlink("print");
	semaphore->forks = sem_open("forks", O_CREAT, 0777, ft_atoi(av[1]));
	semaphore->print = sem_open("print", O_CREAT, 0777, 1);
	if (semaphore->forks == SEM_FAILED || semaphore->print == SEM_FAILED)
	{
		printf("Failed to open semphore for empty\n");
		exit(1);
	}
}

void	init_philo(char **av, int ac, t_philo *f)
{
	int		i;
	t_sem	*semaphore;

	i = 0;
	semaphore = malloc (sizeof(t_sem));
	open_semaphore(av, semaphore);
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
		f[i].semaphore = semaphore;
		i++;
	}
}

void	child_process(char **av, t_philo *f, pthread_t	*th)
{
	int	i;

	i = 0;
	f[0].start_time = calcul_time_ms();
	while (i < ft_atoi(av[1]))
	{
		gettimeofday(&f[i].last_meal, NULL);
		f[i].pid = fork();
		if (f[i].pid == 0)
		{
			f[i].start_time = f[0].start_time;
			if (pthread_create(&th[i], NULL, philosophers, &f[i]) == -1)
			{
				printf("Error\n");
				exit (1);
			}
			stop_phils(&f[i]);
		}
		i++;
	}
}

int	main(int ac, char **av)
{
	t_philo		*f;
	pthread_t	*th;

	if (ac == 5 || ac == 6)
	{
		f = malloc(sizeof(t_philo) * ft_atoi(av[1]));
		th = malloc(sizeof(pthread_t) * ft_atoi(av[1]));
		check_args(av, ac);
		init_philo(av, ac, f);
		child_process(av, f, th);
		stop_process(f);
	}
	return (0);
}
