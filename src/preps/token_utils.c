/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerokhin <aerokhin@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 12:38:07 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/26 14:49:14 by aerokhin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	*word_function(t_main_env **main_env, char *str)
{
	t_word	*word;

	word = (t_word *)malloc(sizeof(t_word));
	if (!word)
		return (NULL);
	word->str = ft_strdup(str);
	if (word->str == NULL)
		return (error_handler_null(main_env, -10, "Word ", "function"));
	return ((void *)word);
}

void	*string_function(t_main_env **main_env, char *str)
{
	t_string	*string;

	string = (t_string *)malloc(sizeof(t_string));
	if (!string)
		return (NULL);
	string->str = ft_strdup(str);
	if (string->str == NULL)
		return (error_handler_null(main_env, -10, "string ", "function"));
	return ((void *)string);
}

void	*command_function(t_main_env **main_env, char *str, \
												t_list_words **list_words)
{
	t_command	*command;
	char		*tmp;

	if (init_command_function(&command, str))
		return (error_handler_null(main_env, -10, "command ", "function"));
	if (command_option_determination(&command, list_words))
		return (free_command(&command), \
			error_handler_null(main_env, -10, "command ", "function"));
	(*list_words) = (*list_words)->next;
	command->parameters = ft_strdup("");
	if (command->parameters == NULL)
		return (error_handler_null(main_env, -10, "command ", "function"));
	while ((*list_words) != NULL && (*list_words)->word != NULL && \
			ft_strchr("><|", (*list_words)->word[0]) == NULL)
	{
		if (command_parameters_populate(&command, list_words, &tmp))
			return (error_handler_null(main_env, -10, "command ", "function"));
	}
	if ((*list_words) != NULL && \
			ft_strchr("><|", (*list_words)->word[0]) != NULL && \
			(*list_words)->prev != NULL)
		(*list_words) = (*list_words)->prev;
	return ((void *)command);
}

void	*program_function(t_main_env **main_env, char *str, \
											t_list_words **list_words)
{
	t_program	*program;
	char		*tmp;

	if (init_program_function(&program, str))
		return (error_handler_null(main_env, -10, "program ", "function"));
	while ((*list_words) != NULL && (*list_words)->next != NULL)
	{
		if ((*list_words)->next == NULL || \
					ft_strchr("|<>", (*list_words)->next->word[0]) != NULL)
			break ;
		if (program_loop_helper(&program, list_words, &tmp))
			return (error_handler_null(main_env, -10, "program ", "function"));
	}
	return ((void *)program);
}

void	*option_function(t_main_env **main_env, char *str)
{
	t_opt	*opt;

	opt = (t_opt *)malloc(sizeof(t_opt));
	if (!opt)
		return (NULL);
	opt->opt_name = ft_strdup(str);
	if (opt->opt_name == NULL)
		return (error_handler_null(main_env, -10, "program ", "function"));
	return ((void *)opt);
}
