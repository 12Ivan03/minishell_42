/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 14:12:11 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/26 15:52:42 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	arr_len(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

int	ip_remove_quotes(t_main_env **main_env, char **arr)
{
	int		i;
	char	*c;

	i = 0;
	while (arr[i])
	{
		c = replace_vars(main_env, arr[i], 0, 0);
		if (c == NULL)
			return (free_str_array(arr), arr = NULL, 1);
		free(arr[i]);
		arr[i] = c;
		i++;
	}
	return (0);
}

int	prep_n_exec_check(t_main_env **main_env, char **split_params)
{
	int	i;

	i = 0;
	if (split_params[i] != NULL)
	{
		if (ip_remove_quotes(main_env, split_params))
			return (free_str_array(split_params), \
					error_handler_num(main_env, -10, "", ""));
		i++;
	}
	return (0);
}

int	prep_n_exec_prep_argv(t_program *token, char **argv, char **split_params)
{
	int	i;

	i = 1;
	argv[0] = ft_strdup(token->name);
	if (argv[0] == NULL)
		return (free_str_array(split_params), 1);
	while (split_params[i - 1])
	{
		argv[i] = ft_strdup(split_params[i - 1]);
		if (argv[i] == NULL)
			return (free_str_array(split_params), free_str_array(argv), 1);
		i++;
	}
	if (split_params == NULL && token->parameters[0] == '\0')
		i++;
	argv[i] = NULL;
	return (0);
}

int	prep_n_exec(t_main_env **main_env, t_program *token)
{
	char	*path;
	char	**argv;
	char	**split_params;

	if (token->name[0] == '\0')
		exit(0);
	path = is_program(main_env, token->name);
	if (path == NULL && ft_strchr(token->name, '/') == NULL)
		exit(error_handler_num(main_env, -22, token->name, "") + 126);
	else
		prep_path_exit_prg(main_env, check_path_status(path, 0), token->name);
	split_params = ft_like_a_split(token->parameters);
	if (split_params == NULL && token->parameters[0] != '\0')
		return (free(path), free_program(&token), 1);
	if (prep_n_exec_check(main_env, split_params))
		return (free(path), free_program(&token), 1);
	argv = (char **)malloc(sizeof(char *) * (arr_len(split_params) + 2));
	if (argv == NULL)
		return (free(path), free_program(&token), 1);
	if (prep_n_exec_prep_argv(token, argv, split_params))
		return (error_handler_num(main_env, -10, "", ""));
	free_str_array(split_params);
	execve(path, argv, convert_our2env(main_env));
	return (1);
}
