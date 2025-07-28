/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_l.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:12:38 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/20 12:16:31 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_tokens	get_enum(t_main_env **main_env, char *str)
{
	t_list_words	*list_words;

	list_words = (*main_env)->list_words;
	if (str[0] == '>')
	{
		if (str[1] == '>')
			return (REDIRECTION_APPEND);
		else
			return (REDIRECTION_OUTPUT);
	}
	else if (str[0] == '<')
	{
		if (str[1] == '<')
			return (REDIRECTION_HERE_DOC);
		else
			return (REDIRECTION_INPUT);
	}
	else if (str[0] == '|')
		return (PIPE);
	else if (built_in_command(str))
		return (COMMAND);
	else if (detect_program(&list_words))
		return (PROGRAM);
	return (PROGRAM);
}

void	*get_struct_value(t_main_env **main_env, t_tokens token, char *str, \
							t_list_words **list_words)
{
	if (token == COMMAND)
		return (command_function(main_env, str, list_words));
	else if (token == PROGRAM)
		return (program_function(main_env, str, list_words));
	else if (token == REDIRECTION_INPUT)
		return (re_in_function(main_env, list_words));
	else if (token == REDIRECTION_OUTPUT)
		return (re_out_function(main_env, list_words));
	else if (token == REDIRECTION_HERE_DOC)
		return (re_here_function(main_env, list_words));
	else if (token == REDIRECTION_APPEND)
		return (re_app_function(main_env, list_words));
	else if (token == PIPE)
		return (NULL);
	return (NULL);
}

char	*check_str_token_word(t_main_env **main_env, \
									t_list_words **list_words)
{
	char	*str;
	int		i;

	str = replace_vars(main_env, (*list_words)->word, 0, 0);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '\0')
	{
		if ((*list_words)->next != NULL)
		{
			free(str);
			str = NULL;
			*list_words = (*list_words)->next;
			str = replace_vars(main_env, (*list_words)->word, 0, 0);
			return (str);
		}
		else
			return (str);
	}
	return (str);
}

t_list_tokens	*create_note_token(t_main_env **main_env, \
									t_list_words **list_words)
{
	t_list_tokens	*token_list;
	char			*str;

	str = check_str_token_word(main_env, list_words);
	if (str == NULL)
		return (NULL);
	token_list = (t_list_tokens *)malloc(sizeof(t_list_tokens));
	if (token_list == NULL)
		return (free(str), NULL);
	token_list->token = get_enum(main_env, str);
	token_list->value = get_struct_value(main_env, \
							token_list->token, str, list_words);
	free(str);
	str = NULL;
	if (token_list->token != PIPE && token_list->value == NULL)
		return (NULL);
	token_list->next = NULL;
	token_list->prev = NULL;
	return (token_list);
}

int	link_t_token(t_main_env **main_env, t_list_tokens **list_token, \
											t_list_words **list_words)
{
	t_list_tokens	*note;
	t_list_tokens	*last_note;

	note = create_note_token(main_env, list_words);
	if (note == NULL)
		return (1);
	if (*list_token == NULL)
	{
		*list_token = note;
		return (0);
	}
	last_note = *list_token;
	while (last_note->next != NULL)
		last_note = last_note->next;
	last_note->next = note;
	note->prev = last_note;
	return (0);
}
