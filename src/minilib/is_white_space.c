/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_white_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:04:45 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/23 19:19:49 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_white_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

int	is_meta_char(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

int	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

int	is_correct_pipes(char **str)
{
	int	i;
	int	len;

	len = ft_strlen(*str);
	i = 0;
	while ((*str) && (*str)[i])
	{
		if ((*str)[i] == '|')
		{
			i += (i < len);
			while ((*str)[i] && is_white_space((*str)[i]))
				i += (i < len);
			if ((*str)[i] == '|')
				return (0);
		}
		i += (i < len);
	}
	return (1);
}
