/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_exe_utils_two.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:24:06 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/20 12:16:49 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_arr_len(char **arr)
{
	int	i;
	int	res;

	res = 0;
	i = 0;
	while (arr[i])
	{
		res++;
		i++;
	}
	return (res);
}

int	shall_you_pass(char *str)
{
	int	i;

	i = 1;
	if (ft_isalpha(str[0]) || str[0] == '_')
	{
		while (str[i])
		{
			if (str[i] == '=')
				return (0);
			if (str[i] == '+' && str[i + 1] == '=')
				return (1);
			if (!ft_isalnum(str[i]) && str[i] != '_')
				return (-1);
			i++;
		}
	}
	else
		return (-1);
	return (0);
}

static int	eval_export_input_helper(t_main_env **main_env, \
						char **cmd_split_array, int flag, int *i)
{
	int	j;

	j = 1;
	while (cmd_split_array[(*i)][j] && (ft_isalnum(cmd_split_array[(*i)][j]) \
			|| cmd_split_array[(*i)][j] == '_'))
		j++;
	if (cmd_split_array[(*i)][j] != '+' && cmd_split_array[(*i)][j] != '=' \
		&& cmd_split_array[(*i)][j] != '\0')
	{
		if (flag == 0)
		{
			error_handler_nc(main_env, -13, ": not a valid identifier", \
							cmd_split_array[(*i)]);
			(*main_env)->export_error = 1;
		}
		free(cmd_split_array[(*i)]);
		cmd_split_array[(*i)] = ft_strdup("");
		if (cmd_split_array[(*i)] == NULL)
			return (error_handler_num(main_env, -10, "", ""), 1);
	}
	return (0);
}

void	if_helper(t_main_env **m, char **csa, int i)
{
	error_handler_num(m, -13, ": not a valid identifier", csa[i]);
	(*m)->export_error = 1;
}

int	eval_export_input(t_main_env **m, char **csa, int flag)
{
	int	i;

	i = 0;
	while (csa[i])
	{
		if (ft_isalpha(csa[i][0]) || csa[i][0] == '_')
		{
			if (eval_export_input_helper(m, csa, flag, &i) == 1)
				return (free_str_array(csa), 1);
		}
		else
		{
			if (flag == 0)
				if_helper(m, csa, i);
			free(csa[i]);
			csa[i] = ft_strdup("");
			if (csa[i] == NULL)
				return (free_str_array(csa), \
					error_handler_num(m, -10, "", ""));
		}
		i++;
	}
	return (free_str_array(csa), 0);
}
