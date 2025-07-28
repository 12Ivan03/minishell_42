/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in_error_seeker.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 19:22:02 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/26 14:59:17 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	build_in_error_seeker(t_main_env **main_env, t_command *command)
{
	if (!ft_strncmp("pwd", command->command, 3) \
		|| !ft_strncmp("env", command->command, 3))
		if (pwd_env_error_exe(main_env, command))
			return (-1);
	if (!ft_strncmp("export", command->command, 6))
		if (export_unset_error_exe(main_env, command, 0))
			return (-1);
	if (!ft_strncmp("unset", command->command, 5))
		if (export_unset_error_exe(main_env, command, 1))
			return (-1);
	if (!ft_strncmp("cd", command->command, 5))
		if (cd_error_exe(command, main_env))
			return (-1);
	if (!ft_strncmp("exit", command->command, 4))
		return (exit_exe(command, main_env));
	return (0);
}
