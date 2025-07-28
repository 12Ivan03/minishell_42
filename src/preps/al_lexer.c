/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   al_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerokhin <aerokhin@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:00:57 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/03 15:54:19 by aerokhin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_list_words	*lexer(t_main_env **main_env, char *str)
{
	size_t			i;
	t_list_words	*list_words;
	int				error;

	error = 0;
	i = 0;
	list_words = NULL;
	while (str && str[i])
	{
		while (is_white_space(str[i]))
			i++;
		if (str[i] == '>' || str[i] == '<')
			error = word_more_n_less(main_env, &list_words, str, &i);
		else if (str[i] == '-')
			error = word_option(main_env, &list_words, str, &i);
		else if (str[i] == '|')
			error = link_t_word(&list_words, ft_strdup("|"), 0);
		else if (str[i] != 0)
			error = word_string(main_env, &list_words, str, &i);
		if (error)
			return (free_list_words(&list_words), NULL);
		i += (str[i] != 0);
	}
	return (list_words);
}
