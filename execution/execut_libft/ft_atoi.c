/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 13:24:27 by lsemlali          #+#    #+#             */
/*   Updated: 2022/10/02 11:41:35 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ex_libft.h"

static int	my_skip(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\n' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		i = i + 1;
		if (str[i - 1] == '-')
			i = -i;
	}
	return (i);
}

long	ft_atoi(const char *str)
{
	long	i;
	long	p;
	long	n;

	p = 1;
	i = my_skip(str);
	if (i < 0)
	{
		i = -i;
		p = -1;
	}
	n = 0;
	while (str[i] >= '0' && str[i] <= '9' && str[i])
	{
		n = n * 10 + (str[i] - 48);
		i++;
	}
	return (n * p);
}
