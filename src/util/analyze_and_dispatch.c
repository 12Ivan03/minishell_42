/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_and_dispatch.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:10:05 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/26 18:17:50 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	command_in_parent(t_main_env **main_env, t_and *and, \
							t_package *package, pid_t *child_pids)
{
	and->were_in_loop = 1;
	and->error_flag = build_in_error_seeker(main_env, package->command);
	and->save_fd_in = dup(STDIN_FILENO);
	and->save_fd_out = dup(STDOUT_FILENO);
	if (package->redir != NULL)
		while_and(main_env, and, package);
	if (and->has_in)
	{
		dup2(and->file_in, STDIN_FILENO);
		ft_close(and->file_in);
	}
	if (and->has_out)
	{
		dup2(and->file_out, STDOUT_FILENO);
		ft_close(and->file_out);
	}
	if (and->error_flag == 0)
		build_in_exe(main_env, package->command, child_pids);
	dup2(and->save_fd_in, STDIN_FILENO);
	dup2(and->save_fd_out, STDOUT_FILENO);
	ft_close(and->save_fd_in);
	ft_close(and->save_fd_out);
}

static void	checking_point(t_main_env **main_env, t_package *package, \
							t_and *and, int *pipe_fd)
{
	if (package->next != NULL)
	{
		if (pipe(pipe_fd) == -1)
			error_handler_nc(main_env, -18, "Pipe", NULL);
	}
	and->pid = fork();
	if (and->pid == -1)
		error_handler_nc(main_env, -18, "Child", NULL);
	signal(SIGINT, SIG_IGN);
}

static void	program_in_children(t_main_env **main_env, t_and *and, \
								pid_t *child_pids, t_package *package)
{
	int	pipe_fd[2];

	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
	and->were_in_loop = 1;
	checking_point(main_env, package, and, pipe_fd);
	if (and->pid == 0)
		child_process(main_env, package, and->prev_fd, pipe_fd);
	child_pids[and->count_children] = and->pid;
	and->count_children++;
	if (and->prev_fd != -1)
		close(and->prev_fd);
	if (package->next != NULL)
	{
		ft_close(pipe_fd[1]);
		and->prev_fd = pipe_fd[0];
	}
	else
	{
		ft_close(pipe_fd[0]);
		ft_close(pipe_fd[1]);
		ft_close(and->prev_fd);
	}
	if (package->next == NULL)
		ft_close(and->prev_fd);
}

static void	nanny_for_all_children(t_main_env **main_env, \
						t_and *and, pid_t *child_pids)
{
	while (and->i < and->count_children)
	{
		if (and->i < and->count_pipes)
			waitpid(child_pids[and->i], &and->status, 0);
		if (WTERMSIG(and->status) == SIGQUIT)
			printf("Quit (core dumped)\n");
		if (WIFEXITED(and->status) && WEXITSTATUS(and->status) == 126)
			(*main_env)->exit_status = 126;
		if (WIFEXITED(and->status) && WEXITSTATUS(and->status) == 127)
			(*main_env)->exit_status = 127;
		else if (and->i == and->count_children - 1)
		{
			if (WIFSIGNALED(and->status))
			{
				(*main_env)->exit_status = 128 + WTERMSIG(and->status);
				write(1, "\n", 1);
			}
			else if (WIFEXITED(and->status))
				(*main_env)->exit_status = WEXITSTATUS(and->status);
		}
		and->i++;
	}
	free(child_pids);
}

int	analyze_and_dispatch(t_main_env **main_env)
{
	t_and			and;
	pid_t			*child_pids;
	t_package		*package;

	and = loca_init_and(main_env);
	child_pids = (pid_t *)malloc(and.count_pipes * sizeof(pid_t));
	(*main_env)->package = prepare_packages(main_env);
	package = (*main_env)->package;
	while (package != NULL)
	{
		if (and.count_pipes == 1 && package->command != NULL)
		{
			command_in_parent(main_env, &and, package, child_pids);
			if (and.error_flag == 2 || and.error_flag == -1)
				return (free(child_pids), 0);
		}
		else
			program_in_children(main_env, &and, child_pids, package);
		and.error_flag = 0;
		package = package->next;
	}
	if (and.were_in_loop && !(*main_env)->export_error)
		(*main_env)->exit_status = 0;
	nanny_for_all_children(main_env, &and, child_pids);
	return (set_up_signals(main_env), 0);
}
