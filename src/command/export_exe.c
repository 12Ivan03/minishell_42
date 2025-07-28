/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_exe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penchoivanov <penchoivanov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:55:57 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/13 13:09:02 by penchoivano      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	skip_var_name(char *cmd_s_arr)
{
	int	j;

	j = 0;
	while (cmd_s_arr[j] != '+' && cmd_s_arr[j] != '=' && \
			cmd_s_arr[j] != '\0')
		j++;
	return (j);
}

static int	prepare_while_helper(t_main_env **main_env, char **cmd_s_arr, \
					int pass, int *i)
{
	char		*prm_name;
	t_our_env	*find_node;
	int			found_node;
	int			j;

	find_node = NULL;
	j = skip_var_name(cmd_s_arr[(*i)]);
	prm_name = ft_substr(cmd_s_arr[(*i)], 0, j);
	if (prm_name == NULL)
		return (free_str_array(cmd_s_arr), 1);
	found_node = find_env_node(&(*main_env)->our_env, prm_name, &find_node);
	free(prm_name);
	if (found_node == -1)
		return (1);
	if (found_node == 0)
		append_to_our_env(main_env, cmd_s_arr[(*i)], pass);
	else if (found_node && cmd_s_arr[(*i)][j] == '\0')
		return ((*i)++, 2);
	else
		update_rewrite_env(main_env, find_node, cmd_s_arr[(*i)], \
			(found_node && cmd_s_arr[(*i)][j] == '+'));
	return (0);
}

static int	prepare_export(t_main_env **main_env, char **cmd_s_arr)
{
	int			pass;
	int			i;
	int			loop_eval;

	loop_eval = 0;
	i = 0;
	pass = -1;
	while (cmd_s_arr[i])
	{
		pass = shall_you_pass(cmd_s_arr[i]);
		if (pass != -1)
		{
			if (cmd_s_arr[i][0])
			{
				loop_eval = prepare_while_helper(main_env, cmd_s_arr, pass, &i);
				if (loop_eval == 1)
					return (error_handler_num(main_env, -10, "", "") - 1);
				else if (loop_eval == 2)
					continue ;
			}
		}
		i++;
	}
	return (0);
}

static void	export_direction(t_main_env **main_env, char **cmd_split_array)
{
	if (cmd_split_array[0] != NULL)
		prepare_export(main_env, cmd_split_array);
	else
		print_export_env(main_env);
}

int	export_exe(t_command *command, t_main_env **main_env)
{
	char		**cmd_split_array;
	char		*temp;
	int			i;

	i = 0;
	cmd_split_array = ft_like_a_split(command->parameters);
	if (cmd_split_array == NULL)
		return (error_handler_num(main_env, -10, "", "") - 1);
	if (cmd_split_array)
	{
		while (cmd_split_array[i])
		{
			temp = replace_vars(main_env, cmd_split_array[i], 0, 0);
			free(cmd_split_array[i]);
			if (temp == NULL)
				return (free_str_array(cmd_split_array), \
						error_handler_num(main_env, -10, "", "") - 1);
			cmd_split_array[i] = temp;
			i++;
		}
	}
	export_direction(main_env, cmd_split_array);
	return (free_str_array(cmd_split_array), 0);
}
