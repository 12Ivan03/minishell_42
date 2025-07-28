/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in_exe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 15:33:37 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/16 13:36:04 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	exit_free(t_main_env **main_env, int error_flag, pid_t *child_pids)
{
	ft_free((void **)&child_pids);
	free_main_env(main_env);
	exit(error_flag);
}

int	build_in_exe(t_main_env **main_env, t_command *command, pid_t *child_pids)
{
	int			error_flag;

	error_flag = (*main_env)->exit_status;
	if (!ft_strncmp("pwd", command->command, 3) \
		|| !ft_strncmp("env", command->command, 3))
		if (!pwd_env_exe(command, main_env))
			return (1);
	if (!ft_strncmp("export", command->command, 6))
		if (!export_exe(command, main_env))
			return (1);
	if (!ft_strncmp("unset", command->command, 5))
		if (!unset_exe(main_env, command, &(*main_env)->our_env))
			return (1);
	if (!ft_strncmp("cd", command->command, 2))
		if (!cd_exe(command, main_env))
			return (1);
	if (!ft_strncmp("echo", command->command, 4))
		if (echo_exe(command, main_env))
			return (1);
	if (!ft_strncmp("exit", command->command, 4))
		exit_free(main_env, error_flag, child_pids);
	return (0);
}
