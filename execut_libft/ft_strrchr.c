/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 10:04:49 by lsemlali          #+#    #+#             */
/*   Updated: 2022/09/28 12:49:18 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ex_libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	int		p;
	char	v;

	p = 0;
	i = 0;
	v = (char )c;
	if (s[i] == '\0' && v == '\0')
	{
		return ((char *)&s[i]);
	}
	while (s[i])
	{
		if (s[i] == v)
			p = i;
		i++;
	}
	if (v == '\0')
		return ((char *)&s[i]);
	if (p == 0 && s[0] != v)
		return (0);
	return ((char *)&s[p]);
}
