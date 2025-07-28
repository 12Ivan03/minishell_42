/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerokhin <aerokhin@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:07:18 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/07 16:10:29 by aerokhin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

size_t	node_len(t_our_env **env)
{
	t_our_env	*env_len;
	size_t		i;

	i = 0;
	env_len = (*env);
	while (env_len != NULL)
	{
		env_len = env_len->next;
		i++;
	}
	return (i);
}

static void	actual_hell(t_our_env **env_sort, t_our_env **env, \
						t_our_env *next_node, t_ijk var)
{
	if (ft_strlen((*env_sort)->var_name) > \
		ft_strlen((*env_sort)->next->var_name))
		var.k = ft_strlen((*env_sort)->var_name);
	else
		var.k = ft_strlen((*env_sort)->next->var_name);
	if (ft_strncmp((*env_sort)->var_name, \
		(*env_sort)->next->var_name, var.k) == 1)
	{
		next_node = (*env_sort)->next;
		if ((*env_sort)->prev != NULL)
			(*env_sort)->prev->next = next_node;
		else
			(*env) = next_node;
		if (next_node->next != NULL)
			next_node->next->prev = (*env_sort);
		(*env_sort)->next = next_node->next;
		next_node->prev = (*env_sort)->prev;
		next_node->next = (*env_sort);
		(*env_sort)->prev = next_node;
		(*env_sort) = next_node;
	}
}

void	sort_env(t_our_env **env)
{
	t_ijk		var;
	size_t		len_node;
	t_our_env	*env_sort;
	t_our_env	*next_node;

	next_node = NULL;
	len_node = node_len(env);
	var = (t_ijk){0, 0, 0};
	while (var.i < len_node)
	{
		env_sort = (*env);
		var.j = 0;
		while (env_sort->next != NULL && var.j < len_node - var.i)
		{
			actual_hell(&env_sort, env, next_node, var);
			env_sort = env_sort->next;
			var.j++;
		}
		var.i++;
	}
}

int	print_export_env(t_main_env **main_env)
{
	t_our_env	*env;
	t_our_env	*env_copy;

	env = copy_env(&(*main_env)->our_env);
	if (env == NULL)
		return (error_handler_num(main_env, -10, "", ""));
	sort_env(&env);
	env_copy = env;
	while (env != NULL)
	{
		printf("declare -x %s", env->var_name);
		if (env->value[0] != '\0')
			printf("\"%s\"", env->value);
		else if (env->var_name[ft_strlen(env->var_name) - 1] == '=')
			printf("\"\"");
		printf("\n");
		env = env->next;
	}
	free_our_env(&env_copy);
	return (0);
}
