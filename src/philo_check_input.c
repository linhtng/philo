/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_check_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 21:08:29 by thuynguy          #+#    #+#             */
/*   Updated: 2023/06/15 21:08:31 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/philo.h"

static int	ft_isspace(int c)
{
	return (c == '\t' || c == '\v'
		|| c == '\f' || c == '\r' || c == '\n' || c == ' ');
}

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	long	result;

	result = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '+')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			break ;
		result = result * 10 + *str - '0';
		str++;
	}
	if (*str && ft_isspace(*str))
	{
		while (ft_isspace(*str))
			str++;
	}
	if (!*str)
		return (result);
	else
		return (-1);
}

int	valid_input(int arc, char **arv)
{
	int	i;
	int	num;

	i = 1;
	while (i < arc)
	{
		num = ft_atoi(arv[i]);
		if (i == 1 && (num < 1 || num > 200))
		{
			printf("Number of philos must be between 1 and 200.\n");
			return (0);
		}
		if (num <= 0 || num > 2147483647)
		{
			printf("Arguments must be positive integers.\n");
			return (0);
		}
		i++;
	}
	return (1);
}

void	philo_usage(void)
{
	printf("Please enter 4 or 5 arguments\n");
	printf("1. Number of philosophers\n");
	printf("2. Time to die\n");
	printf("3. Time to eat\n");
	printf("4. Time to sleep\n");
	printf("5. Number of times each philo must eat (optional)\n");
}
