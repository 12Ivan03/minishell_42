/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:51:59 by ipavlov           #+#    #+#             */
/*   Updated: 2024/10/19 16:27:14 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static void	ft_convert_i_to_a(char *num_str, int len, int *number, int neg)
{
	num_str[len] = '\0';
	while (len > 0)
	{
		num_str[len - 1] = (*number % 10) + '0';
		*number = *number / 10;
		len--;
	}
	if (neg < 0)
		num_str[0] = '-';
}

static int	ft_neg(int *n)
{
	if (*n < 0)
		return (-1);
	else
		return (1);
}

static int	ft_len(int *n)
{
	if (*n < 0)
		return (1);
	else
		return (0);
}

char	*ft_itoa(int n)
{
	int		len;
	int		neg;
	int		number;
	char	*num_str;

	neg = ft_neg(&n);
	len = ft_len(&n);
	number = n * neg;
	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	num_str = (char *)malloc((len + 1) * sizeof(char));
	if (num_str == NULL)
		return (NULL);
	ft_convert_i_to_a(num_str, len, &number, neg);
	return (num_str);
}
