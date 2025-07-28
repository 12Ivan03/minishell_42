/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_and_dispatch_two.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:15:46 by ipavlov           #+#    #+#             */
/*   Updated: 2025/05/31 12:02:34 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	if_open(t_and *and, t_node_file *node_file)
{
	if (and->file_in != -100)
		close (and->file_in);
	and->file_in = open(node_file->name, O_RDONLY);
	if (and->file_in == -1)
		and->break_loop_exit = -1;
	and->has_in = 1;
}

static void	else_open(t_and *and, t_node_file *node_file)
{
	if (and->file_out != -100)
		close (and->file_out);
	if (node_file->redir_enum == REDIRECTION_OUTPUT)
	{
		and->file_out = open(node_file->name, \
						O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (and->file_out == -1)
			and->break_loop_exit = -1;
	}
	else if (node_file->redir_enum == REDIRECTION_APPEND)
	{
		and->file_out = open(node_file->name, \
						O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (and->file_out == -1)
			and->break_loop_exit = -1;
	}
	and->has_out = 1;
}

void	while_and(t_main_env **main_env, t_and *and, t_package *package)
{
	t_node_file	*node_file;
	int			w_or_r;
	int			eval;

	node_file = (t_node_file *)package->redir;
	while (node_file != NULL)
	{
		eval = node_file->redir_enum == 4 || node_file->redir_enum == 6;
		w_or_r = eval * R_OK + !eval * W_OK;
		if (eval)
			if_open(and, node_file);
		else
			else_open(and, node_file);
		if (and->break_loop_exit == -1)
		{
			and->error_flag = -1;
			check_permission_fail(main_env, node_file->name, w_or_r);
			break ;
		}
		node_file = node_file->next;
	}
}
