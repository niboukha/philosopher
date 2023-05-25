/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboukha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 13:27:56 by niboukha          #+#    #+#             */
/*   Updated: 2023/05/24 21:22:37 by niboukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long long	calcul_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(int i)
{
	long long	_time;

	_time = calcul_time_ms() + i;
	while (calcul_time_ms() < _time)
		usleep(100);
}

void	ft_print(t_philo *f, const char *txt, int x)
{
	if (x == 0)
	{
		sem_wait(f->semaphore->print);
		printf("%lld philo %d %s\n",
			calcul_time_ms() - f->start_time, f->id, txt);
		sem_post(f->semaphore->print);
	}
	else
		printf("%lld philo %d %s\n",
			calcul_time_ms() - f->start_time, f->id, txt);
}

void	stop_phils(t_philo *f)
{
	while (1)
	{
		if ((calcul_time_ms() - ((f->last_meal.tv_sec * 1000)
					+(f->last_meal.tv_usec / 1000))) > f->data.time_to_die)
		{
			sem_wait(f->semaphore->print);
			ft_print(f, "is deid", 1);
			exit(1);
		}
		usleep(100);
	}
}

void	stop_process(t_philo *f)
{
	int	status;
	int	i;

	while (1)
	{
		i = 0;
		while (i < f->data.number_of_philosophers)
		{
			waitpid(-1, &status, 0);
			if (status == 256)
			{
				i = 0;
				while (i < f->data.number_of_philosophers)
				{
					kill(f[i].pid, SIGKILL);
					i++;
				}
				exit(0);
			}
			i++;
		}
	}
}
