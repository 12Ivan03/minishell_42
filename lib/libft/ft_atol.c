/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:12:24 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/09 18:16:51 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

int	ft_atol(const char *nptr)
{
	long		i;
	int			neg;
	long		num;

	num = 0;
	neg = 1;
	i = 0;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			neg = -neg;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (neg == -1 && num > INT_MAX)
			return (INT_MIN);
		else if (neg == 1 && num > INT_MAX)
			return (INT_MAX);
		num = (num * 10) + (nptr[i] - '0');
		i++;
	}
	return ((int)neg * num);
}
