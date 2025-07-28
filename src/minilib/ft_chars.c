/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerokhin <aerokhin@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:45:21 by aerokhin          #+#    #+#             */
/*   Updated: 2025/05/30 15:40:23 by aerokhin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	count_characters_before(char *str, char c, int start)
{
	int	i;

	if (start < 0)
		return (0);
	i = start;
	while (start >= 0 && str[i] == c)
		i--;
	return (start - i);
}

char	*repeat_char(char c, int n)
{
	char	*str;
	int		i;

	str = (char *)ft_calloc(sizeof(char), (n + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < n)
	{
		str[i] = c;
		i++;
	}
	return (str);
}
