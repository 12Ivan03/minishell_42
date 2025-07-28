/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerokhin <aerokhin@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:25:24 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/26 18:35:14 by aerokhin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	pipe_pipe(char *str)
{
	int		i;
	char	c;

	i = -1;
	c = 0;
	while (str[++i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			c = str[i++];
			while (str[i] && str[i] != c)
				i++;
			if (!str[i++])
				break ;
		}
		if (str[i] == '|')
		{
			i++;
			while (str[i] && is_white_space(str[i]))
				i++;
			if (str[i] == '|')
				return (1);
		}
	}
	return (0);
}

int	is_pipe(char c)
{
	if (c == '|')
		return (1);
	return (0);
}
