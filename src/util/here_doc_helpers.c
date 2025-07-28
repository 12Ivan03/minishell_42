/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerokhin <aerokhin@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:46:51 by aerokhin          #+#    #+#             */
/*   Updated: 2025/06/03 14:40:25 by aerokhin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	putendln_and_free(char **str, int fd)
{
	if (str)
	{
		ft_putendl_fd(*str, fd);
		free(*str);
	}
}

char	*trim_tab(char *line)
{
	char	*trimmed;
	int		i;

	if (!line)
		return (NULL);
	i = 0;
	while (line[i] == '\t')
		i++;
	trimmed = ft_strdup(&line[i]);
	if (!trimmed)
	{
		free(line);
		return (NULL);
	}
	free(line);
	return (trimmed);
}

char	*take_heredoc_path(int src)
{
	char	*path;
	char	*index_str;
	char	*full_path;

	index_str = ft_itoa(src);
	if (!index_str)
		return (NULL);
	path = ft_strjoin(".heredoc_", index_str);
	free(index_str);
	if (!path)
		return (NULL);
	full_path = ft_strjoin("/tmp/", path);
	free(path);
	return (full_path);
}

char	*get_processed_line(char *line, t_main_env **main_env, int var_flag)
{
	if (!var_flag)
		return (replace_vars(main_env, line, 0, 1));
	else
		return (ft_strdup(line));
}
