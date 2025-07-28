/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   al_lexer_words_helpers.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerokhin <aerokhin@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:55:41 by aerokhin          #+#    #+#             */
/*   Updated: 2025/06/03 17:41:57 by aerokhin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*more_single_double(char *str, size_t *i)
{
	char	*word;

	if (str[*i + 1] == '>')
		word = ft_strdup(">>");
	else
		word = ft_strdup(">");
	(*i) += str[*i + 1] == '>';
	return (word);
}

int	skip_if_quotes(char *str, size_t *i)
{
	char	c;

	c = str[(*i)++];
	skip_till_quotes(str, i, c);
	if (str[*i] != c)
		return (1);
	(*i) += (str[*i] == c);
	return (0);
}
