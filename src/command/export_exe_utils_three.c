/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_exe_utils_three.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerokhin <aerokhin@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:27:43 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/07 16:23:15 by aerokhin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	append_env_value(t_main_env **main_env, \
						t_our_env *node_plus_env, char *cpy_cmd)
{
	char	*cpy;

	cpy = ft_strdup(node_plus_env->value);
	if (cpy == NULL)
		return (free(cpy_cmd), \
				error_handler_num(main_env, -10, "append_env_value", ""));
	free(node_plus_env->value);
	node_plus_env->value = ft_strjoin(cpy, cpy_cmd);
	free(cpy_cmd);
	free(cpy);
	if (node_plus_env->value == NULL)
		return (error_handler_num(main_env, -10, "append_env_value", ""));
	return (0);
}

int	rewrite_env_value(t_our_env *node_plus_env, char *cpy_cmd)
{
	free(node_plus_env->value);
	node_plus_env->value = cpy_cmd;
	return (0);
}

static char	*update_rewrite_env_helper(t_main_env **main_env, \
						t_our_env *node_plus_env, char *comd_prms, int i)
{
	char	*cpy_cmd;

	cpy_cmd = NULL;
	if (node_plus_env->var_name[ft_strlen(node_plus_env->var_name) - 1] \
		!= '=' && comd_prms[i] != '\0')
	{
		cpy_cmd = ft_strjoin(node_plus_env->var_name, "=");
		if (cpy_cmd == NULL)
			return (error_handler_null(main_env, -10, "rewrite_env", ""));
		free(node_plus_env->var_name);
		node_plus_env->var_name = ft_strdup(cpy_cmd);
		if (node_plus_env->var_name == NULL)
			return (error_handler_null(main_env, -10, "rewrite_env", ""));
		free(cpy_cmd);
	}
	cpy_cmd = ft_substr(comd_prms, i + 1, ft_strlen(comd_prms));
	if (cpy_cmd == NULL)
		return (error_handler_null(main_env, -10, "rewrite_env", ""));
	return (cpy_cmd);
}

int	update_rewrite_env(t_main_env **main_env, t_our_env *node_plus_env, \
							char *comd_prms, int flag)
{
	int		i;
	int		check;
	char	*cpy_cmd;
	char	*copy;

	check = 0;
	i = 1;
	while (comd_prms[i] && comd_prms[i] != '=')
		i++;
	cpy_cmd = update_rewrite_env_helper(main_env, node_plus_env, comd_prms, i);
	if (cpy_cmd == NULL)
		return (1);
	copy = cpy_with_baskslash(main_env, cpy_cmd);
	if (copy == NULL)
		return (1);
	free(cpy_cmd);
	if (flag == 1)
		check = append_env_value(main_env, node_plus_env, copy);
	else
		check = rewrite_env_value(node_plus_env, copy);
	if (check)
		return (1);
	return (0);
}

int	append_to_our_env(t_main_env **main_env, char *command, int pass)
{
	char	*cpy_command;
	char	*cpy;
	int		i;
	int		j;

	j = 0;
	i = 0;
	cpy = (char *)ft_calloc((ft_strlen(command) + pass + 1), \
			sizeof(char));
	if (cpy == NULL)
		return (error_handler_num(main_env, -10, "", ""));
	while (command[i])
	{
		if (command[i] == '+')
			i++;
		cpy[j++] = command[i++];
	}
	cpy_command = cpy_with_baskslash(main_env, cpy);
	free(cpy);
	if (cpy_command == NULL)
		return (error_handler_num(main_env, -10, "append_env", NULL));
	create_list_env(main_env, cpy_command, &(*main_env)->our_env);
	free(cpy_command);
	cpy_command = NULL;
	return (0);
}
