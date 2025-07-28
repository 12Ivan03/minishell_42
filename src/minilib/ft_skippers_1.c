/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skippers_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:24:06 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/23 15:01:56 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	skip_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] && is_white_space(str[i]))
		i++;
	return (i);
}

int	skip_last_spaces(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (i >= 0 && str[i] && is_white_space(str[i]))
		i--;
	return (i);
}

void	skip_text(char *str, size_t *i)
{
	if (str[*i] && !is_white_space(str[*i]) && !is_quote(str[*i]))
	{
		while (str[*i] && !is_white_space(str[*i]) \
					&& str[*i] != '"' && str[*i] != '\'')
			(*i)++;
	}
}

void	skip_quotes(char *str, size_t *i)
{
	char	c;

	c = str[*i];
	if (c == '"' || c == '\'')
	{
		(*i)++;
		while (str[*i] && (str[*i]) != c)
		{
			(*i)++;
		}
		(*i)++;
	}
}

void	skip_whitespace(char *str, size_t *i)
{
	while (str[*i] && (is_white_space(str[*i])))
	{
		(*i)++;
	}
}
