/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_cmd_fun.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 11:40:40 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/07 19:04:50 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	command_option_helper(t_command **command, t_list_words **list_words)
{
	(*list_words) = (*list_words)->next;
	while ((*list_words)->next != NULL && \
			(*list_words)->next->word != NULL && \
			!ft_strncmp("-n ", (*list_words)->next->word, 3))
		(*list_words) = (*list_words)->next;
	(*command)->option->opt_name = ft_strdup((*list_words)->word);
}

int	command_option_determination(t_command **command, t_list_words **list_words)
{
	if ((*list_words)->next != NULL && (*list_words)->next->word != NULL)
	{
		if (!ft_strncmp("echo", (*list_words)->word, 4) && \
			!ft_strncmp("-n ", (*list_words)->next->word, 3))
		{
			command_option_helper(command, list_words);
			if ((*command)->option->opt_name == NULL)
				return (1);
		}
		else
		{
			(*command)->option->opt_name = ft_strdup("");
			if ((*command)->option->opt_name == NULL)
				return (1);
		}
	}
	else
	{
		(*command)->option->opt_name = ft_strdup("");
		if ((*command)->option->opt_name == NULL)
			return (1);
	}
	return (0);
}

int	command_parameters_populate(t_command **command, \
								t_list_words **list_words, char **tmp)
{
	if ((*list_words)->space_before >= 1)
		(*tmp) = ft_strjoin((*command)->parameters, " ");
	else
		(*tmp) = ft_strdup((*command)->parameters);
	if ((*tmp) == NULL)
		return (1);
	free((*command)->parameters);
	(*command)->parameters = ft_strjoin((*tmp), (*list_words)->word);
	free((*tmp));
	if ((*command)->parameters == NULL)
		return (1);
	(*list_words) = (*list_words)->next;
	return (0);
}

int	program_loop_helper(t_program **program, t_list_words **list_words, \
															char **tmp)
{
	if ((*list_words)->next != NULL && (*list_words)->next->space_before >= 1)
		(*tmp) = ft_strjoin((*program)->parameters, " ");
	else
		(*tmp) = ft_strjoin((*program)->parameters, "");
	if ((*tmp) == NULL)
		return (1);
	free((*program)->parameters);
	(*program)->parameters = ft_strjoin((*tmp), (*list_words)->next->word);
	free((*tmp));
	if ((*program)->parameters == NULL)
		return (1);
	(*list_words) = (*list_words)->next;
	return (0);
}
