/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   al_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 21:12:02 by aerokhin          #+#    #+#             */
/*   Updated: 2025/05/31 16:14:13 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*remove_quotes_n_join(t_main_env **main_env, char *str, int start, \
								int end)
{
	char	*new_str;
	int		i;
	int		j;
	int		count;

	count = 0;
	i = start - 1;
	while (++i < end)
		if (str[i] == '"')
			count++;
	new_str = (char *)ft_calloc((end - start - count + 2), sizeof(char));
	if (!new_str)
		return (error_handler_null(main_env, -10, "al_quotes", "remove_q"));
	i = start - 1;
	j = 0;
	while (++i <= end)
		if (str[i] != '"')
			new_str[j++] = str[i];
	return (new_str);
}

char	*add_quotes(t_main_env **main_env, char *str, char c)
{
	char	*new_str;
	int		i;
	int		j;

	new_str = (char *)malloc(sizeof(char) * (ft_strlen(str) + 3));
	if (!new_str)
		return (error_handler_null(main_env, -10, "al_quotes", "add_quotes"));
	new_str[0] = c;
	i = 0;
	j = 1;
	while (str[i])
		new_str[j++] = str[i++];
	new_str[j] = c;
	new_str[j + 1] = '\0';
	return (new_str);
}
