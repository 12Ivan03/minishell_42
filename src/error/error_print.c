/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_prt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 17:45:47 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/16 18:08:42 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	err_prt_n(char *str)
{
	ft_putendl_fd(str, 2);
}

void	err_prt_one(char *str, char *str1)
{
	ft_putstr_fd(str, 2);
	ft_putendl_fd(str1, 2);
}

void	err_prt_two(char *str, char *str1, char *str2)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd(str1, 2);
	ft_putendl_fd(str2, 2);
}

void	err_prt_three(char *str, char *str1, char *str2, char *str3)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd(str1, 2);
	ft_putstr_fd(str2, 2);
	ft_putendl_fd(str3, 2);
}

void	err_prt_char(char *str, char c, char *str1)
{
	ft_putstr_fd(str, 2);
	ft_putchar_fd(c, 2);
	ft_putendl_fd(str1, 2);
}
