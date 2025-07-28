/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:12:15 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/26 18:16:41 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	child_readi_loop_if(t_main_env **main_env, t_node_file *node, \
							t_cp *cp, int *pipe_fd)
{
	if (cp->file_fd_in != -1)
		close (cp->file_fd_in);
	cp->file_fd_in = open(node->name, O_RDONLY);
	if (cp->file_fd_in == -1)
	{
		ft_close(pipe_fd[0]);
		ft_close(pipe_fd[1]);
		ft_close(cp->c_prev_fd);
		exit(check_permission_fail(main_env, node->name, R_OK));
	}
	cp->has_in = 1;
}

void	child_readi_loop_else(t_main_env **main_env, t_node_file *node, \
							t_cp *cp, int *pipe_fd)
{
	if (cp->file_fd_out != -1)
		close(cp->file_fd_out);
	if (node->redir_enum == REDIRECTION_OUTPUT)
		cp->file_fd_out = open(node->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (node->redir_enum == REDIRECTION_APPEND)
		cp->file_fd_out = open(node->name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (cp->file_fd_out == -1)
	{
		ft_close(pipe_fd[0]);
		ft_close(pipe_fd[1]);
		ft_close(cp->c_prev_fd);
		exit(check_permission_fail(main_env, node->name, W_OK));
	}
	cp->has_out = 1;
}

void	child_redir_loop(t_main_env **main_env, t_package *package, \
						t_cp *cp, int *pipe_fd)
{
	t_node_file	*node;

	node = (t_node_file *)package->redir;
	while (node != NULL)
	{
		if (node->redir_enum == REDIRECTION_INPUT || \
			node->redir_enum == REDIRECTION_HERE_DOC)
			child_readi_loop_if(main_env, node, cp, pipe_fd);
		else
			child_readi_loop_else(main_env, node, cp, pipe_fd);
		node = node->next;
	}
}

void	check_redir_pipes(t_cp *cp, t_package *package, \
							int prev_fd, int *pipe_fd)
{
	if (cp->has_in)
	{
		dup2(cp->file_fd_in, STDIN_FILENO);
		ft_close(cp->file_fd_in);
	}
	else if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		ft_close(prev_fd);
	}
	if (cp->has_out)
	{
		dup2(cp->file_fd_out, STDOUT_FILENO);
		ft_close(cp->file_fd_out);
	}
	else if (package->next != NULL)
		dup2(pipe_fd[1], STDOUT_FILENO);
	ft_close(pipe_fd[0]);
	ft_close(pipe_fd[1]);
	ft_close(prev_fd);
}

int	child_process(t_main_env **main_env, t_package *package, \
					int prev_fd, int *pipe_fd)
{
	t_cp	cp;

	init_cp(&cp, prev_fd);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	if (package->redir != NULL)
		child_redir_loop(main_env, package, &cp, pipe_fd);
	check_redir_pipes(&cp, package, prev_fd, pipe_fd);
	if (package->command != NULL && package->program == NULL)
		cp.error_flag = build_in_error_seeker(main_env, package->command);
	if (package->command != NULL && cp.error_flag != -1)
		build_in_exe(main_env, package->command, NULL);
	else if (package->program != NULL)
		prep_n_exec(main_env, package->program);
	free_main_env(main_env);
	exit (0);
}
