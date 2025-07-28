/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   al_check_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 14:46:19 by aerokhin          #+#    #+#             */
/*   Updated: 2025/06/26 18:18:52 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	prep_path_exit_prg(t_main_env **main_env, int status_err, char *path)
{
	if (status_err == ERR_NOT_EXIST)
	{
		error_handler_nc(main_env, -20, path, "");
		free_main_env(main_env);
		exit(127);
	}
	else if (status_err == ERR_IS_DIR || status_err == ERR_NO_PERM)
	{
		if (status_err == ERR_IS_DIR)
			error_handler_nc(main_env, -31, path, "");
		else if (status_err == ERR_NO_PERM)
			error_handler_nc(main_env, -25, path, "Permission denied");
		free_main_env(main_env);
		exit(126);
	}
}

int	prep_path_ret_dir(t_main_env **main_env, int status_err, char *path)
{
	if (status_err == ERR_NOT_EXIST)
	{
		error_handler_nc(main_env, -20, path, "");
		return (1);
	}
	else if (status_err == ERR_NOT_DIR || status_err == ERR_NO_PERM)
	{
		if (status_err == ERR_NOT_DIR)
			error_handler_nc(main_env, -32, path, "");
		else if (status_err == ERR_NO_PERM)
			error_handler_nc(main_env, -25, path, "Permission denied");
		return (1);
	}
	return (0);
}

int	check_path_status(char *path, int dir_or_not)
{
	struct stat	sb;

	if (access(path, F_OK) != 0)
		return (ERR_NOT_EXIST);
	if (stat(path, &sb) != 0)
		return (ERR_NOT_EXIST);
	if (dir_or_not == 0)
	{
		if (S_ISDIR(sb.st_mode))
			return (ERR_IS_DIR);
		if (access(path, X_OK) != 0)
			return (ERR_NO_PERM);
	}
	else if (dir_or_not == 1)
	{
		if (S_ISREG(sb.st_mode))
			return (ERR_NOT_DIR);
		if (access(path, X_OK | R_OK) != 0)
			return (ERR_NO_PERM);
	}
	return (CHECK_OK);
}
