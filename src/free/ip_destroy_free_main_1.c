/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ip_destroy_free_main_1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penchoivanov <penchoivanov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:18:34 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/13 12:56:17 by penchoivano      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_op(t_opt *opt)
{
	if (opt)
	{
		if (opt->opt_name)
			free(opt->opt_name);
		opt->opt_name = NULL;
		free(opt);
	}
}

void	ft_free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	free_token_void(t_list_tokens **token)
{
	if ((*token)->token == WORD)
		free_word((t_word *)(*token)->value);
	else if ((*token)->token == STRING)
		free_string((t_string *)(*token)->value);
	else if ((*token)->token == COMMAND)
		free_command((t_command **)&(*token)->value);
	else if ((*token)->token == PROGRAM)
		free_program((t_program **)&(*token)->value);
	else if ((*token)->token == REDIRECTION_INPUT)
		free_re_in((t_re_input **)&(*token)->value);
	else if ((*token)->token == REDIRECTION_OUTPUT)
		free_re_out((t_re_output **)&(*token)->value);
	else if ((*token)->token == REDIRECTION_HERE_DOC)
		free_re_here((t_re_here **)&(*token)->value);
	else if ((*token)->token == REDIRECTION_APPEND)
		free_re_app((t_re_append **)&(*token)->value);
	else if ((*token)->token == OPTIONS)
		free_op((t_opt *)(*token)->value);
	if ((*token))
	{
		free(*token);
		(*token) = NULL;
	}
}
