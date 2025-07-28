/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_and_dispatch_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:04:35 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/26 18:18:39 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	how_many_pipes(t_main_env **main_env)
{
	int				count_pipes;
	t_list_tokens	*tokens;

	count_pipes = 1;
	tokens = (*main_env)->list_tokens;
	while (tokens != NULL)
	{
		if (tokens->token == PIPE)
			count_pipes++;
		tokens = tokens->next;
	}
	return (count_pipes);
}

t_and	loca_init_and(t_main_env **main_env)
{
	t_and	and;

	and.count_children = 0;
	and.count_pipes = how_many_pipes(main_env);
	and.error_flag = 0;
	and.file_in = -100;
	and.file_out = -100;
	and.i = 0;
	and.pid = -1;
	and.has_in = 0;
	and.has_out = 0;
	and.prev_fd = -1;
	and.save_fd_in = 0;
	and.save_fd_out = 1;
	and.status = 0;
	and.break_loop_exit = 0;
	and.were_in_loop = 0;
	return (and);
}

int	check_permission_fail(t_main_env **main_env, char *file_name, int flag)
{
	int	error;

	error = 0;
	if (flag == R_OK)
		error = access(file_name, R_OK) == -1 && access(file_name, F_OK) == 0;
	else if (flag == W_OK)
		error = access(file_name, W_OK) == -1 && access(file_name, F_OK) == 0;
	if (error == 1)
	{
		error_handler_nc(main_env, -25, file_name, "Permission denied");
		return (1);
	}
	else
		error_handler_nc(main_env, -20, file_name, "");
	return (1);
}

// int	check_permission_fail(t_main_env **main_env, char *file_name, int flag)
// {
// 	int	error;

// 	error = 0;
// 	if (flag == R_OK)
// 		error = access(file_name, R_OK) == -1 && access(file_name, F_OK) == 0;
// 	else if (flag == W_OK)
// 		error = access(file_name, W_OK) == -1 && access(file_name, F_OK) == 0;
// 	err_prt_three("check_permission_fail:   ", file_name, " ", ft_itoa(error));
// 	if (error == 1)
// 	{
// 		error_handler_nc(main_env, -25, file_name, "Permission denied");
// 		return (1);
// 	}
// 	else
// 		error_handler_nc(main_env, -20, file_name, "");
// 	return (1);
// }

// int	check_error_path(t_main_env **main_env, t_package *package)
// {
// 	char	*path;
// 	path = NULL;
// 	if (package->program != NULL && package->program->name != NULL)
// 		path = is_program(main_env, package->program->name);
// 	if (path != NULL)
// 		return (0);
// 	return (1);
// }
