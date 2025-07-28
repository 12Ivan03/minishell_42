/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_like_a_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 12:57:47 by aerokhin          #+#    #+#             */
/*   Updated: 2025/06/07 16:41:38 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// Counting how many parts in source string
// separated by whitespaces and only these characters
// if these character inside single or double quotes
// not counted
// if these character are the first or last
// in the string not counted

static int	count_parts(char *str)
{
	size_t		i;
	int			count;
	char		c;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && (is_white_space(str[i])))
			i++;
		if (str[i] && ((i == 0 || is_white_space(str[i - 1])) \
								&& !is_white_space(str[i])))
			count++;
		while (str[i] && !is_white_space(str[i]) && \
				str[i] != '"' && str[i] != '\'')
			i++;
		c = str[i];
		if (c == '"' || c == '\'')
		{
			i++;
			skip_till_quotes(str, &i, c);
		}
		i += (str[i] != 0);
	}
	return (count);
}

static void	*split(char *str, char **result, t_ijk *var)
{
	skip_whitespace(str, &(*var).i);
	if ((*var).i == 0 || (is_white_space(str[(*var).i - 1]) \
			&& !is_white_space(str[(*var).i])))
		(*var).k = (*var).i;
	skip_text(str, &(*var).i);
	skip_quotes(str, &(*var).i);
	if (is_white_space(str[(*var).i]))
	{
		result[(*var).j] = ft_substr(str, (*var).k, (*var).i - (*var).k);
		if (!result[(*var).j])
		{
			free_str_array(result);
			return (NULL);
		}
		(*var).j++;
		(*var).k = (*var).i;
	}
	(*var).i++;
	return (result);
}

static int	add_last_part(char **result, t_ijk *var, char *str)
{
	if (var->i > 0 && !is_white_space(str[var->i - 1])
		&& var->i != var->k)
	{
		result[var->j] = ft_substr(str, var->k, var->i - var->k);
		if (!result[var->j])
			return (0);
		var->j++;
	}
	return (1);
}

char	**ft_like_a_split(char *str)
{
	t_ijk		var;
	int			count;
	char		**result;

	var = (t_ijk){0, 0, 0};
	count = count_parts(str);
	result = (char **)malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	while (var.i < ft_strlen(str) && str[var.i] && var.i < ft_strlen(str))
		if (split(str, result, &var) == NULL)
			return (NULL);
	var.i = var.i - (var.i > 0);
	if (!add_last_part(result, &var, str))
		return (free_str_array(result), NULL);
	result[var.j] = NULL;
	return (result);
}
