/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 21:47:25 by aerokhin          #+#    #+#             */
/*   Updated: 2025/06/26 17:21:07 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	heredoc_status(int status, t_main_env **main_env)
{
	if (WIFSIGNALED(status))
	{
		(*main_env)->exit_status = 128 + WTERMSIG(status);
		write(1, "\n", 1);
		return (-100);
	}
	else if (WIFEXITED(status))
	{
		(*main_env)->exit_status = WEXITSTATUS(status);
		return (0);
	}
	return (0);
}

int	handle_heredoc(t_re_here *redir, t_main_env **main_env)
{
	int		fd;
	int		status;
	pid_t	pid;

	if (check_here_stop_word(redir, main_env))
		return (-100);
	(*main_env)->here_doc_index++;
	redir->file_name = take_heredoc_path((*main_env)->here_doc_index);
	if (!redir->file_name)
		return (perror("heredoc malloc"), 1);
	fd = open(redir->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (free(redir->file_name), \
			error_handler_num(main_env, -10, "heredoc open", NULL));
	pid = fork();
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (pid == 0)
		here_doc_child(redir, main_env, fd);
	ft_close(fd);
	(*main_env)->exit_status = 0;
	waitpid(pid, &status, 0);
	return (result_heredoc(main_env, status, heredoc_status(status, main_env)));
}

void	here_doc_child(t_re_here *rd, t_main_env **main_env, int fd)
{
	char	*line;
	char	*processed;

	signal(SIGINT, SIG_DFL);
	while (1)
	{
		line = readline("> ");
		if (!line)
			exit_here_doc(fd, \
					error_handler_num(main_env, -28, rd->stop_word, NULL));
		if (rd->tab)
			line = trim_tab(line);
		if (ft_strlen(line) == ft_strlen(rd->stop_word) && \
			ft_strncmp(line, rd->stop_word, ft_strlen(rd->stop_word)) == 0)
		{
			free(line);
			break ;
		}
		processed = get_processed_line(line, main_env, rd->variable);
		if (processed)
			putendln_and_free(&processed, fd);
		free(line);
	}
	exit_here_doc(fd, 1);
}
