/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   al_destroy_free_main.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 21:34:41 by aerokhin          #+#    #+#             */
/*   Updated: 2025/06/26 16:57:54 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_package(t_package **package)
{
	if (!package || !*package)
		return ;
	if ((*package)->command != NULL)
		free_command(&(*package)->command);
	if ((*package)->program != NULL)
		free_program(&(*package)->program);
	if ((*package)->redir != NULL)
		free_node_file(&(*package)->redir);
	free((*package));
}

void	free_packages_d(t_package **packages)
{
	t_package	*tmp;

	tmp = NULL;
	if (!packages || !*packages)
		return ;
	while ((*packages))
	{
		tmp = (*packages)->next;
		free_package((packages));
		(*packages) = tmp;
	}
}

void	free_main_env(t_main_env **main_env)
{
	if ((*main_env)->curr_dir != NULL)
		ft_free((void **)&(*main_env)->curr_dir);
	if ((*main_env)->prev_dir != NULL)
		ft_free((void **)&(*main_env)->prev_dir);
	if ((*main_env)->home_dir != NULL)
		ft_free((void **)&(*main_env)->home_dir);
	if ((*main_env)->list_words != NULL)
		free_list_words(&(*main_env)->list_words);
	if ((*main_env)->list_tokens != NULL)
		free_list_tokens(&(*main_env)->list_tokens);
	if ((*main_env)->our_env != NULL)
		free_our_env(&(*main_env)->our_env);
	if ((*main_env)->package != NULL)
		free_packages_d(&(*main_env)->package);
	if ((*main_env)->real_env)
		(*main_env)->real_env = NULL;
	ft_free((void **)&(*main_env));
}

void	ft_close(int fd)
{
	if (fd != -1)
		close(fd);
}

void	clear_here_doc_files(t_main_env **main_env)
{
	int	i;

	if ((*main_env)->here_doc_index > 0)
	{
		i = 1;
		while (i <= (*main_env)->here_doc_index)
			unlink(take_heredoc_path(i++));
		(*main_env)->here_doc_index = 0;
	}
}
