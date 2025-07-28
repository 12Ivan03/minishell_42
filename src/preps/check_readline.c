/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_readline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerokhin <aerokhin@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:25:24 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/26 18:56:21 by aerokhin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	child_loop_rl(t_main_env **main_env, char **str1, int *i)
{
	char	*rl;

	rl = readline(">");
	if (rl == NULL)
		exit (1);
	*str1 = join_and_free(str1, &rl);
	if ((*str1) == NULL)
		exit (error_handler_num(main_env, -10, "", ""));
	(*i) = skip_last_spaces((*str1));
	if (!is_correct_pipes(str1))
	{
		ft_free((void **)&(*str1));
		exit (2);
	}
	if (pipe_pipe((*str1)))
	{
		ft_free((void **)&(*str1));
		exit (1);
	}
}

void	readline_chilled(t_main_env **main_env, char **str, int pipe_fd[2])
{
	char	*str1;
	int		i;

	str1 = ft_strdup((*str));
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!str1)
		exit(error_handler_num(main_env, -10, "", ""));
	close(pipe_fd[0]);
	i = skip_last_spaces(str1);
	while (i >= 0 && is_pipe(str1[i]))
		child_loop_rl(main_env, &str1, &i);
	write(pipe_fd[1], str1, ft_strlen(str1));
	ft_free((void **)&str1);
	close(pipe_fd[1]);
	exit(0);
}

void	set_up_readline_child(t_main_env **main_env, pid_t pid, int status)
{
	waitpid(pid, &status, 0);
	if (status && WIFSIGNALED(status))
	{
		(*main_env)->exit_status = 128 + WTERMSIG(status);
		(*main_env)->p_error = 1;
		write(1, "\n", 1);
	}
	else if (status && WIFEXITED(status))
	{
		(*main_env)->exit_status = WEXITSTATUS(status) + 1;
		(*main_env)->p_error = 3;
	}
}

char	*check_child_readline(t_main_env **main_env, char *str)
{
	int		status;
	int		len_buf;
	pid_t	pid;
	int		pipe_fd[2];
	char	buffer[4096];

	if (pipe(pipe_fd) == -1)
		return (error_handler_null(main_env, -23, "pipe failed", ""));
	pid = fork();
	if (pid == -1)
		return (error_handler_null(main_env, -23, "fork failed", ""));
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (pid == 0)
		readline_chilled(main_env, &str, pipe_fd);
	close(pipe_fd[1]);
	set_up_readline_child(main_env, pid, status);
	set_up_signals(main_env);
	len_buf = read(pipe_fd[0], buffer, sizeof(buffer) - 1);
	close(pipe_fd[0]);
	if (len_buf < 0)
		return (error_handler_null(main_env, -10, "", ""));
	buffer[len_buf] = '\0';
	return (ft_strdup(buffer));
}

int	check_readline(t_main_env **main_env, char **str)
{
	int		i;
	char	*cpy_str;

	i = skip_spaces(*str);
	if (is_pipe((*str)[i]) || pipe_pipe(*str))
		return (error_handler_num(main_env, -24, NULL, NULL));
	if (!(*str) && pipe_pipe(*str))
		return (error_handler_num(main_env, -24, NULL, NULL));
	cpy_str = check_child_readline(main_env, *str);
	if (cpy_str == NULL)
		return (1);
	ft_free((void **)&(*str));
	(*str) = ft_strdup(cpy_str);
	ft_free((void **)&(cpy_str));
	if ((*main_env)->p_error == 3 && (*main_env)->exit_status == 2)
		return (error_handler_num(main_env, -26, \
				"syntax error: unexpected end of file\nexit", "") + 2);
	if ((*main_env)->p_error == 3 && (*main_env)->exit_status == 3)
		return (error_handler_num(main_env, -24, NULL, NULL));
	else if ((*main_env)->p_error == 1)
		return (1);
	return (0);
}
