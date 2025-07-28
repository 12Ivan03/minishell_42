/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerokhin <aerokhin@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:00:48 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/07 15:58:57 by aerokhin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	init_copy_env(t_our_env **new_node, t_our_env *env)
{
	(*new_node) = (t_our_env *)malloc(sizeof(t_our_env));
	if ((*new_node) == NULL)
		return (1);
	(*new_node)->var_name = ft_strdup(env->var_name);
	if ((*new_node)->var_name == NULL)
	{
		free(*new_node);
		return (1);
	}
	(*new_node)->value = ft_strdup(env->value);
	if ((*new_node)->value == NULL)
	{
		free((*new_node)->var_name);
		free(*new_node);
		return (1);
	}
	(*new_node)->next = NULL;
	(*new_node)->prev = NULL;
	return (0);
}

t_our_env	*copy_env(t_our_env **our_env)
{
	t_our_env	*env;
	t_our_env	*new_node;
	t_our_env	*cpy_env;
	t_our_env	*tmp;

	cpy_env = NULL;
	env = (*our_env);
	while (env != NULL)
	{
		if (init_copy_env(&new_node, env))
			return (free_our_env(&cpy_env), NULL);
		if (cpy_env == NULL)
			cpy_env = new_node;
		else
		{
			tmp = cpy_env;
			while (tmp->next != NULL)
				tmp = tmp->next;
			tmp->next = new_node;
			new_node->prev = tmp;
		}
		env = env->next;
	}
	return (cpy_env);
}
