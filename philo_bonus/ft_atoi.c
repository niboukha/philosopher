/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboukha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:43:15 by niboukha          #+#    #+#             */
/*   Updated: 2023/05/25 16:48:55 by niboukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo_bonus.h"

void	error_function(void)
{
	printf("Error\n");
	exit(8);
}

int	ft_atoi(char *str)
{
	int			i;
	long		result;
	int			sign;

	i = 0;
	result = 0;
	sign = 1;
	while (str[i] && str[i] <= 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			error_function();
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		result = result * 10 + str[i++] - 48;
	if (str[i])
		error_function();
	return (result * sign);
}

void	check_args(char **av, int ac)
{
	int	i;

	i = 1;
	while (i < 5 || (i < 6 && ac == 6))
	{
		if (ft_atoi(av[i]) == 0)
			exit(1);
		i++;
	}
}
