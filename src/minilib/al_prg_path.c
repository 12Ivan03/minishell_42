/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   al_prg_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerokhin <aerokhin@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 21:32:43 by aerokhin          #+#    #+#             */
/*   Updated: 2025/06/23 12:49:25 by aerokhin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <string.h>

static char	*check_n_return(char *str)
{
	char	*tmp;

	if (str == NULL)
		tmp = ft_strdup("");
	else
		tmp = ft_strdup(str);
	if (!tmp)
		return (NULL);
	else
		return (tmp);
}

static char	*return_fixed(t_main_env **main_env, char *name)
{
	if (ft_strncmp("HOME=", name, ft_strlen(name)) == 0)
	{
		if (!(*main_env)->home_dir)
			return (check_n_return(NULL));
		else
			return (check_n_return((*main_env)->home_dir));
	}
	else if (!ft_strncmp("PWD=", name, 4))
	{
		if (!(*main_env)->curr_dir)
			return (check_n_return(NULL));
		else
			return (check_n_return((*main_env)->curr_dir));
	}
	else if (!ft_strncmp("OLDPWD=", name, 7))
	{
		if (!(*main_env)->prev_dir)
			return (check_n_return(NULL));
		else
			return (check_n_return((*main_env)->prev_dir));
	}
	return (NULL);
}

static char	*return_cmd(char *cmd)
{
	if (access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	else
		return (NULL);
}

char	*get_env_value(t_main_env **main_env, char *name)
{
	t_our_env	*tmp;

	if (ft_strncmp("HOME=", name, ft_strlen(name)) == 0 || \
		ft_strncmp("PWD=", name, ft_strlen(name)) == 0 || \
		ft_strncmp("OLDPWD=", name, ft_strlen(name)) == 0)
		return (return_fixed(main_env, name));
	tmp = (*main_env)->our_env;
	while (tmp)
	{
		if (ft_strncmp(tmp->var_name, name, ft_strlen(name)) == 0)
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (ft_strdup(""));
}

char	*is_program(t_main_env **main_env, char *cmd)
{
	char		*path_value;
	char		**paths;
	char		*full_path;
	int			i;
	struct stat	sb;

	if (ft_strchr(cmd, '/'))
		return (return_cmd(cmd));
	path_value = get_env_value(main_env, "PATH=");
	if (!path_value)
		return (NULL);
	paths = ft_split(path_value, ':');
	if (!paths)
		return (free(path_value), NULL);
	i = -1;
	while (paths[++i])
	{
		full_path = ft_str3join(paths[i], "/", cmd);
		if (check_path_status(full_path, 0) == CHECK_OK)
			return (free(path_value), free_str_array(paths), full_path);
		free(full_path);
	}
	return (free(path_value), free_str_array(paths), NULL);
}
