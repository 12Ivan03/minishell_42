/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ip_destroy_free_main_3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerokhin <aerokhin@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 16:59:31 by aerokhin          #+#    #+#             */
/*   Updated: 2025/06/09 17:03:01 by aerokhin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_word(t_word *word)
{
	if (word->str)
	{
		free(word->str);
		word->str = NULL;
	}
}

void	free_string(t_string *string)
{
	if (string->str)
	{
		free(string->str);
		string->str = NULL;
	}
}

void	free_command(t_command **command)
{
	if ((*command) == NULL)
		return ;
	if ((*command)->command)
	{
		free((*command)->command);
		(*command)->command = NULL;
	}
	if ((*command)->parameters)
	{
		free((*command)->parameters);
		(*command)->parameters = NULL;
	}
	if ((t_opt *)(*command)->option != NULL)
	{
		if ((t_opt *)(*command)->option->opt_name != NULL)
		{
			free((t_opt *)(*command)->option->opt_name);
			((t_opt *)(*command)->option)->opt_name = NULL;
		}
		free((t_opt *)(*command)->option);
		(*command)->option = NULL;
	}
	if ((*command) != NULL)
		free((*command));
}

void	free_program(t_program **program)
{
	if (*program == NULL)
		return ;
	if ((*program)->name)
	{
		free((*program)->name);
		(*program)->name = NULL;
	}
	if ((*program)->parameters != NULL && (*program)->parameters)
	{
		free((*program)->parameters);
		(*program)->parameters = NULL;
	}
	if (*program != NULL)
	{
		free((*program));
		(*program) = NULL;
	}
}
