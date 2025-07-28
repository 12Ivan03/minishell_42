/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_our_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 12:38:12 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/02 17:10:05 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_our_env	*create_node_env(t_main_env **main_env, char *str)
{
	t_our_env	*env_node;
	int			i;

	env_node = (t_our_env *)malloc(sizeof(t_our_env));
	if (env_node == NULL)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	i++;
	env_node->var_name = ft_substr(str, 0, i);
	if (env_node->var_name == NULL)
		return (error_handler_null(main_env, -10, NULL, NULL));
	env_node->value = ft_substr(str, i, ft_strlen(str));
	if (env_node->value == NULL)
		return (free(env_node->var_name), \
				error_handler_null(main_env, -10, NULL, NULL));
	env_node->next = NULL;
	env_node->prev = NULL;
	return (env_node);
}

int	create_list_env(t_main_env **main_env, char *str, t_our_env **env)
{
	t_our_env	*env_str;
	t_our_env	*env_list;

	env_str = create_node_env(main_env, str);
	if (env_str == NULL)
		return (1);
	if (*env == NULL)
		*env = env_str;
	else
	{
		env_list = *env;
		while (env_list->next != NULL)
			env_list = env_list->next;
		env_str->prev = env_list;
		env_list->next = env_str;
	}
	return (0);
}

int	pwd_oldpwd_home_cmp(t_main_env **main_env, char **envp, int *i)
{
	if (ft_strncmp("PWD", envp[(*i)], 3) == 0)
	{
		(*main_env)->curr_dir = ft_substr(envp[(*i)], 4, \
			ft_strlen(envp[(*i)]) - 1);
		if ((*main_env)->curr_dir == NULL)
			return (1);
	}
	else if (ft_strncmp("OLDPWD", envp[(*i)], 6) == 0)
	{
		(*main_env)->prev_dir = ft_substr(envp[(*i)], 7, \
			ft_strlen(envp[(*i)]) - 1);
		if ((*main_env)->prev_dir == NULL)
			return (1);
	}
	else if (ft_strncmp("HOME", envp[(*i)], 4) == 0)
	{
		(*main_env)->home_dir = ft_substr(envp[(*i)], 5, \
			ft_strlen(envp[(*i)]) - 1);
		if ((*main_env)->home_dir == NULL)
			return (1);
	}
	return (0);
}

int	read_our_env(char **envp, t_main_env **main_env)
{
	int	i;
	int	error;

	error = 0;
	(*main_env)->real_env = envp;
	i = 0;
	while (envp[i])
	{
		error = create_list_env(main_env, envp[i], &(*main_env)->our_env);
		if (error)
			return (1);
		error = pwd_oldpwd_home_cmp(main_env, envp, &i);
		if (error)
			return (1);
		i++;
	}
	return (0);
}
