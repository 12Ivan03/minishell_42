/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in_error_seeker_helper.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerokhin <aerokhin@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:48:39 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/23 12:25:30 by aerokhin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	pwd_env_error_exe(t_main_env **main_env, t_command *command)
{
	char	*tmp;

	tmp = replace_vars(main_env, command->parameters, 0, 0);
	if (tmp == NULL)
		return (error_handler_num(main_env, -10, "", ""));
	free(command->parameters);
	command->parameters = tmp;
	if (command->option->opt_name[0] == '-')
		return (error_handler_num(main_env, -11, command->command, \
										command->option->opt_name));
	else if (command->parameters[0] == '-')
		return (error_handler_num(main_env, -11, command->command, \
												command->parameters));
	if (ft_strncmp("pwd", command->command, ft_strlen(command->command)) != 0 \
											&& command->parameters[0] != '\0')
		return (error_handler_num(main_env, -12, command->command, \
												command->parameters));
	if (ft_strncmp("pwd", command->command, ft_strlen(command->command)) == 0 \
		&& (command->parameters[0] != '\0' && command->parameters[1] != '\0') \
	&& (command->parameters[1] == '-' && ft_isalnum(command->parameters[2])))
		return (error_handler_num(main_env, -12, command->command, \
												command->parameters));
	return (0);
}

static int	command_loop(t_main_env **main_env, char **cmd_split_array)
{
	char	*temp;
	int		i;

	i = 0;
	while (cmd_split_array[i])
	{
		temp = replace_vars(main_env, cmd_split_array[i], 0, 10);
		free(cmd_split_array[i]);
		if (temp == NULL)
			return (1);
		cmd_split_array[i] = temp;
		i++;
	}
	return (0);
}

int	export_unset_error_exe(t_main_env **main_env, t_command *command, int flag)
{
	char	**cmd_split_array;

	if (command->parameters)
	{
		cmd_split_array = ft_like_a_split(command->parameters);
		if (cmd_split_array == NULL)
			return (error_handler_num(main_env, -10, "", ""));
		if (command_loop(main_env, cmd_split_array))
			return (free_str_array(cmd_split_array), \
					error_handler_num(main_env, -10, "", ""));
		if (cmd_split_array[0] != NULL)
			return (eval_export_input(main_env, cmd_split_array, flag));
		free_str_array(cmd_split_array);
		cmd_split_array = NULL;
	}
	if (command->option->opt_name[0] != '\0')
	{
		if (flag == 0)
			return (error_handler_num(main_env, -13, \
				": not a valid identifier", command->option->opt_name));
		else
			return (error_handler_num(main_env, -21, \
				": invalid option", command->option->opt_name));
	}
	return (0);
}

static int	handle_cd(t_command *command, t_main_env **main_env, char **cmd_prm)
{
	char		*dollar;

	if (command->parameters[0] == '\0')
	{
		free(command->parameters);
		command->parameters = ft_strdup(" $HOME");
		if (command->parameters == NULL)
			return (2);
	}
	dollar = replace_vars(main_env, command->parameters, 0, 0);
	if (dollar == NULL)
		return (2);
	if (dollar[0] != '\0' && dollar[0] == ' ' && dollar[1] == '\0')
		return (free(dollar), 1);
	(*cmd_prm) = ft_substr(dollar, skip_spaces(dollar), ft_strlen(dollar));
	free(dollar);
	if ((*cmd_prm) == NULL)
		return (2);
	return (0);
}

int	cd_error_exe(t_command *command, t_main_env **main_env)
{
	int			i;
	int			error;
	char		*cmdprm;

	error = handle_cd(command, main_env, &cmdprm);
	if (error == 2)
		return (error_handler_num(main_env, -10, "", ""));
	else if (error == 1)
		return (error_handler_num(main_env, -16, NULL, NULL));
	i = 0;
	while (cmdprm[i])
	{
		if (cmdprm[i] == ' ')
			return (free(cmdprm), error_handler_num(main_env, -15, "", ""));
		i++;
	}
	if (prep_path_ret_dir(main_env, check_path_status(cmdprm, 1), cmdprm) == 1)
	{
		return (free(cmdprm), 1);
	}
	free (cmdprm);
	return (0);
}
