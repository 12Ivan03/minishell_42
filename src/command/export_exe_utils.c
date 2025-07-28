/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_exe_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penchoivanov <penchoivanov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 13:22:56 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/13 13:08:52 by penchoivano      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	cpy_w_b_helper(char *str, int *i, int *count)
{
	while (str[(*i)])
	{
		if (str[(*i)] == '"' || str[(*i)] == '$' || str[(*i)] == '\\')
			(*count)++;
		(*count)++;
		(*i)++;
	}
}

char	*cpy_with_baskslash(t_main_env **main_env, char *str)
{
	int		i;
	int		j;
	int		count;
	char	*cpy;

	count = 0;
	i = 0;
	cpy_w_b_helper(str, &i, &count);
	cpy = (char *)malloc((count + 1) * sizeof(char));
	if (cpy == NULL)
		return (error_handler_null(main_env, -10, "Word ", "function"));
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '$' || str[i] == '\\')
			cpy[j++] = '\\';
		cpy[j++] = str[i++];
	}
	cpy[j] = '\0';
	return (cpy);
}

int	compare_var_name(t_our_env *our_env, char *var)
{
	t_our_env	*env;
	int			i;

	i = 0;
	env = our_env;
	if (env->var_name && var)
	{
		while (env->var_name[i] && var[i])
		{
			if (env->var_name[i] > var[i])
				break ;
			else if (env->var_name[i] < var[i])
				break ;
			i++;
		}
		if (env->var_name[i] != '=' && env->var_name[i] != '\0')
			return (0);
		if (var[i] != '\0')
			return (0);
	}
	return (1);
}

static void	find_env_node_helper(char *params, char **var, int *i)
{
	if (params[0] == ' ')
		(*var) = ft_substr(params, 1, (*i) - 1);
	else
		(*var) = ft_substr(params, 0, (*i));
}

int	find_env_node(t_our_env **our_env, char *params, t_our_env	**find_node)
{
	int			i;
	char		*var;
	t_our_env	*env;

	env = *our_env;
	i = 0;
	while (params[i] && params[i] != '+' && \
			params[i] != '=' && params[i] != ' ')
		i++;
	find_env_node_helper(params, &var, &i);
	if (var == NULL)
		return (-1);
	while (env != NULL)
	{
		if (compare_var_name(env, var) == 1)
		{
			free(var);
			(*find_node) = env;
			return (1);
		}
		env = env->next;
	}
	free(var);
	return (0);
}
