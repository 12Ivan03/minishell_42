/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:36:10 by ipavlov           #+#    #+#             */
/*   Updated: 2024/10/19 16:11:21 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_put_num(char *arr, int i, int fd)
{
	while (i >= 0)
	{
		ft_putchar_fd(arr[i], fd);
		i--;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	char	arr[11];
	int		i;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = n * -1;
	}
	if (n == -2147483648)
	{
		ft_putstr_fd("2147483648", fd);
		return ;
	}
	if (n == 0)
		ft_putchar_fd('0', fd);
	i = 0;
	while (n > 0)
	{
		arr[i] = (n % 10) + '0';
		n = n / 10;
		i++;
	}
	arr[i] = '\0';
	ft_put_num(arr, i - 1, fd);
}
