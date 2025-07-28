/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_extra_helper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:14:35 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/26 17:21:35 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_heredoc_data(t_re_here *rd)
{
	if (rd->stop_word)
		free(rd->stop_word);
	if (rd->file_name)
		free(rd->file_name);
	free(rd);
}

int	check_here_stop_word(t_re_here *redir, t_main_env **main_env)
{
	if (redir->stop_word == NULL)
		return (error_handler_num(main_env, -29, "", ""));
	return (0);
}

void	exit_here_doc(int fd, int tmp)
{
	ft_close(fd);
	exit(tmp);
}

int	result_heredoc(t_main_env **main_env, int status, int heredoc_stat)
{
	if (status && heredoc_stat == -100)
		return (-100);
	set_up_signals(main_env);
	return (0);
}
