/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   al_env_handlers_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 14:49:15 by aerokhin          #+#    #+#             */
/*   Updated: 2025/06/26 17:01:55 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*handle_single_quotes(t_main_env **main_env, \
							char *str, size_t *i, int flag)
{
	char	*result;
	size_t	start;
	size_t	end;

	(void)flag;
	(void)main_env;
	start = (*i) + 1;
	end = start;
	skip_till_quotes(str, &end, '\'');
	*i = end + (str[end] == '\'' );
	result = ft_substr(str, start, end - start);
	return (result);
}

char	*handle_double_quotes(t_main_env **main_env, \
							char *str, size_t *i, int flag)
{
	char	*result;
	char	*temp;
	char	*temp2;
	size_t	start;
	size_t	end;

	start = (*i) + 1;
	end = start;
	skip_till_quotes(str, &end, '"');
	*i = end + (str[end] == '"');
	temp = ft_substr(str, start, end - start);
	if (flag == -1)
		return (temp);
	temp2 = replace_vars(main_env, temp, 2, 0);
	free (temp);
	result = ft_strdup(temp2);
	free(temp2);
	return (result);
}
