/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   al_env_handlers_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerokhin <aerokhin@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 14:47:19 by aerokhin          #+#    #+#             */
/*   Updated: 2025/06/20 11:59:17 by aerokhin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	handle_curly_var(char *str, size_t i, size_t *var_len, char **temp)
{
	size_t	j;

	j = i + 1;
	while (str[j] && str[j] != '}')
		j++;
	if (!str[j])
		return (1);
	*temp = ft_substr(str, i + 1, j - i - 1);
	if (!(*temp))
		return (1);
	*var_len = j - i + 3;
	return (0);
}

char	*handle_no_closing_quote(char *str, size_t *i, size_t j)
{
	char	*temp;

	temp = ft_substr(str, (*i) - 1, j - (*i) + 1);
	if (!temp)
		return (NULL);
	(*i) = j;
	return (temp);
}

// 1 -error, 0 - is ok
int	handle_var_name(char *str, size_t i, size_t *var_len, char **temp)
{
	size_t	j;

	j = i;
	while (str[j] && (ft_isalnum(str[j]) || str[j] == '_'))
		(j)++;
	if (j == i)
		return (1);
	*temp = ft_substr(str, i, j - i);
	if (!(*temp))
		return (1);
	*var_len = j - i + 1;
	return (0);
}
