/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_exe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerokhin <aerokhin@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 13:51:30 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/09 16:42:10 by aerokhin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	shall_you_pass_unset(char *str)
{
	int	i;

	i = 1;
	if (ft_isalpha(str[0]) || str[0] == '_')
	{
		while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
			i++;
		if (str[i] != '\0')
			return (0);
	}
	else
		return (0);
	return (1);
}

static int	unset_env_strcmp(t_main_env **main_env, char **params, int *i)
{
	if (!ft_strncmp(params[(*i)], "PWD", 3))
	{
		if ((*main_env)->curr_dir != NULL)
			free((*main_env)->curr_dir);
		(*main_env)->curr_dir = ft_strdup("");
		if ((*main_env)->curr_dir == NULL)
			return (1);
	}
	else if (!ft_strncmp(params[(*i)], "OLDPWD", 6))
	{
		if ((*main_env)->prev_dir != NULL)
			free((*main_env)->prev_dir);
		(*main_env)->prev_dir = ft_strdup("");
		if ((*main_env)->prev_dir == NULL)
			return (1);
	}
	return (0);
}

static void	found_helper_node(t_our_env **our_env, char **params, int i)
{
	t_our_env	*find_node;
	int			found_node;

	find_node = NULL;
	found_node = find_env_node(our_env, params[i], &find_node);
	if (found_node)
	{
		if ((*our_env)->var_name == find_node->var_name)
			(*our_env) = find_node->next;
		if (find_node->prev != NULL)
			find_node->prev->next = find_node->next;
		if (find_node->next != NULL)
			find_node->next->prev = find_node->prev;
		free(find_node->value);
		free(find_node->var_name);
		find_node->next = NULL;
		find_node->prev = NULL;
		free(find_node);
	}
}

int	unset_exe(t_main_env **main_env, t_command *command, t_our_env **our_env)
{
	char		**params;
	char		*temp;
	int			i;

	params = ft_like_a_split(command->parameters);
	if (params == NULL)
		return (1);
	i = 0;
	while (params[i])
	{
		if (shall_you_pass_unset(params[i]))
		{
			if (unset_env_strcmp(main_env, params, &i))
				return (1);
			temp = replace_vars(main_env, params[i], 0, 10);
			if (temp == NULL)
				return (free_str_array(params), 1);
			free(params[i]);
			params[i] = temp;
			found_helper_node(our_env, params, i);
		}
		i++;
	}
	free_str_array(params);
	return (0);
}
