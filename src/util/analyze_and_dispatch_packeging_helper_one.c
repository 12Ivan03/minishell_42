/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_and_dispatch_packeging_helper_one.c        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 15:33:51 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/16 15:13:58 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	populate_package_one(t_list_tokens *tokens, t_package **temp)
{
	if (tokens->token == COMMAND && (*temp)->flag == 0)
	{
		(*temp)->command = ft_command_dup((t_command *)tokens->value);
		(*temp)->flag = 1;
	}
	else if (tokens->token == PROGRAM && (*temp)->flag == 0)
	{
		(*temp)->program = ft_program_dup((t_program *)tokens->value);
		(*temp)->flag = 1;
	}
}

static int	gather_program(t_package *temp, char **tmp_all)
{
	char	*tmp;

	tmp = NULL;
	if (temp->program != NULL && temp->program->parameters[0] != '\0')
	{
		tmp = ft_str3join(temp->program->parameters, " ", *tmp_all);
		free(temp->program->parameters);
	}
	else
		tmp = ft_str3join("", "", *tmp_all);
	free(*tmp_all);
	if (tmp == NULL)
		return (1);
	temp->program->parameters = tmp;
	return (0);
}

static int	gather_command(t_package *temp, char **tmp_all)
{
	char	*tmp;

	tmp = NULL;
	if (temp->command != NULL && temp->command->parameters[0] != '\0')
	{
		tmp = ft_str3join(temp->command->parameters, " ", *tmp_all);
		free(temp->command->parameters);
	}
	else
		tmp = ft_strdup(*tmp_all);
	free(*tmp_all);
	if (tmp == NULL)
		return (1);
	temp->command->parameters = tmp;
	return (0);
}

static int	gather_all(t_package *temp, \
							t_list_tokens *tokens, int flag)
{
	char	*tmp_all;
	int		error;

	error = 0;
	tmp_all = NULL;
	if (tokens->token == PROGRAM)
		tmp_all = gather_prev_and_next(((t_program *)tokens->value)->name, \
					"", ((t_program *)tokens->value)->parameters);
	else
		tmp_all = gather_prev_and_next(((t_command *)tokens->value)->command, \
							((t_command *)tokens->value)->option->opt_name, \
							((t_command *)tokens->value)->parameters);
	if (tmp_all == NULL)
		return (1);
	if (flag)
		error = gather_program(temp, &tmp_all);
	else
		error = gather_command(temp, &tmp_all);
	if (error)
		return (1);
	return (0);
}

int	populate_package(t_main_env **main_env, t_package *temp, \
					t_list_tokens *tokens)
{
	int	error;

	error = 0;
	if (tokens->token == COMMAND && temp->flag == 0)
		populate_package_one(tokens, &temp);
	else if (tokens->token == PROGRAM && temp->flag == 0)
		populate_package_one(tokens, &temp);
	else if ((tokens->token == PROGRAM || tokens->token == COMMAND) \
			&& temp->flag == 1)
	{
		if (temp->program != NULL)
			error = gather_all(temp, tokens, 1);
		else
			error = gather_all(temp, tokens, 0);
	}
	else
		error = create_redir_list(main_env, tokens->token, \
								tokens->value, temp);
	return (error);
}
