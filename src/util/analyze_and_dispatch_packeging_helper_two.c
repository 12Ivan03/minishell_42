/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_and_dispatch_packeging_helper_two.c        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerokhin <aerokhin@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 15:37:31 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/09 16:55:22 by aerokhin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	gather_name(char **tmp_name, char **name)
{
	if (*name)
		*tmp_name = ft_strdup(*name);
	else
		*tmp_name = ft_strdup("");
}

static void	gather_res(char **tmp_res, char **tmp, char **real)
{
	if (*real)
		*tmp_res = ft_strjoin(*tmp, *real);
	else
		*tmp_res = ft_strdup(*tmp);
	free(*tmp);
}

char	*gather_prev_and_next(char *name, char *opt, char *param)
{
	char	*tmp_name;
	char	*tmp_opt;
	char	*tmp_params;

	tmp_name = NULL;
	tmp_opt = NULL;
	tmp_params = NULL;
	gather_name(&tmp_name, &name);
	if (tmp_name == NULL)
		return (NULL);
	gather_res(&tmp_opt, &tmp_name, &opt);
	if (tmp_opt == NULL)
		return (NULL);
	gather_res(&tmp_params, &tmp_opt, &param);
	if (tmp_params == NULL)
		return (NULL);
	return (tmp_params);
}

t_command	*ft_command_dup(t_command *command)
{
	t_command	*new_command;

	new_command = (t_command *)malloc(sizeof(t_command));
	new_command->command = ft_strdup(command->command);
	if (new_command->command == NULL)
		return (new_command);
	if (command->option != NULL)
	{
		new_command->option = (t_opt *)malloc(sizeof(t_opt));
		if (new_command->option == NULL)
			return (new_command);
		new_command->option->opt_name = ft_strdup(command->option->opt_name);
		if (new_command->option->opt_name == NULL)
			return (new_command);
	}
	else
		new_command->option = NULL;
	new_command->parameters = ft_strdup(command->parameters);
	if (new_command->parameters == NULL)
		return (new_command);
	return (new_command);
}

t_program	*ft_program_dup(t_program *program)
{
	t_program	*new_program;

	new_program = (t_program *)malloc(sizeof(t_program));
	new_program->name = ft_strdup(program->name);
	if (new_program->name == NULL)
		return (new_program);
	new_program->parameters = ft_strdup(program->parameters);
	if (new_program->parameters == NULL)
		return (new_program);
	return (new_program);
}
