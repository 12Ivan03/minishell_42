/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skippers_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerokhin <aerokhin@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:58:25 by aerokhin          #+#    #+#             */
/*   Updated: 2025/06/18 11:46:59 by aerokhin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	skip_till_specchars(char *str, size_t *i)
{
	*i += (str[*i] != '\0');
	while (str[*i] && str[*i] != '\'' && str[*i] != '"' && \
					str[*i] != '$')
	{
		(*i)++;
	}
}

void	skip_till_quotes(char *str, size_t *i, char c)
{
	while (str[*i] && (str[*i]) != c)
		(*i)++;
}

void	skip_till_meta_quotes(char *str, size_t *i)
{
	while (str[*i] && str[*i] != ' ' \
					&& !is_meta_char(str[*i]) && !is_quote(str[*i]))
		(*i)++;
}
