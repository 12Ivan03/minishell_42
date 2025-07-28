/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   al_lexer_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerokhin <aerokhin@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 17:48:39 by aerokhin          #+#    #+#             */
/*   Updated: 2025/06/03 17:41:33 by aerokhin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	word_env_var(t_main_env **main_env, t_list_words **list_words, \
				char *str, size_t *i)
{
	size_t	start_word;
	char	*word;
	int		space_before;

	space_before = count_characters_before(str, ' ', (*i) - 1);
	(*i)++;
	if (str[*i] == '?')
	{
		link_t_word(list_words, ft_strdup("$?"), space_before);
		(*i)++;
	}
	else
	{
		start_word = *i - 1;
		while (str[*i] && !is_white_space(str[*i]))
			(*i)++;
		word = ft_substr(str, start_word, *i - start_word);
		if (!word)
			return (error_handler_num(main_env, -10, "word_env_var", ""));
		link_t_word(list_words, word, space_before);
	}
	(*i)--;
	return (0);
}

int	word_more_n_less(t_main_env **main_env, t_list_words **list_words, \
					char *str, size_t *i)
{
	char	*word;
	int		space_before;
	char	c;

	word = NULL;
	c = str[*i];
	space_before = count_characters_before(str, ' ', (*i) - 1);
	if (c == '>')
		word = more_single_double(str, i);
	else if (c == '<')
	{
		if (str[*i + 1] == '<')
		{
			if (str[(*i) + 2] != '\0' && str[*i + 2] == '-')
				word = ft_strdup("<<-");
			else
				word = ft_strdup("<<");
			(*i) += (str[(*i) + 2] != '\0' && str[*i + 2] == '-') + 1;
		}
		else
			word = ft_strdup("<");
	}
	if (!word)
		return (error_handler_num(main_env, -10, "word_more_n_less", ""));
	return (link_t_word(list_words, word, space_before), 0);
}

int	word_option(t_main_env **main_env, t_list_words **list_words, \
				char *str, size_t *i)
{
	size_t	start_word;
	char	*word;
	int		space_before;

	space_before = count_characters_before(str, ' ', (*i) - 1);
	start_word = *i;
	(*i)++;
	while (str[*i] && str[*i] != ' ')
		(*i)++;
	word = ft_substr(str, start_word, *i - start_word + 1);
	if (!word)
		return (error_handler_num(main_env, -10, "word_option", ""));
	link_t_word(list_words, word, space_before);
	return (0);
}

int	word_string(t_main_env **main_env, t_list_words **list_words, \
				char *str, size_t *i)
{
	size_t	start_word;
	char	*word;
	int		space_before;

	space_before = count_characters_before(str, ' ', (*i) - 1);
	skip_whitespace(str, i);
	start_word = *i;
	while (str && str[*i])
	{
		if (is_quote(str[*i]))
			if (skip_if_quotes(str, i))
				return (error_handler_num(main_env, -26, "syntax error", ""));
		skip_till_meta_quotes(str, i);
		if (str[*i] == ' ' || is_meta_char(str[*i]))
			break ;
		(*i) += (!is_quote(str[*i]) && str[*i] != '\0');
	}
	word = ft_substr(str, start_word, *i - start_word);
	if (!word)
		return (error_handler_num(main_env, -10, "word_string", ""));
	if (ft_strlen(word) != 0)
		link_t_word(list_words, word, space_before);
	(*i) -= (*i > 0 && str[*i - 1] != '\0');
	return (0);
}

// cat <out.txt > 1 <123 > 4 < outfile1234