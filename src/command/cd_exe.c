/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_exe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:42:01 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/21 15:17:03 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	change_cd_env(t_main_env **main_env, \
							t_our_env **find_node, char *cwd)
{
	if (find_env_node(&(*main_env)->our_env, " PWD", find_node))
	{
		free((*find_node)->value);
		(*find_node)->value = ft_strdup(cwd);
		if ((*find_node)->value == NULL)
			return (1);
	}
	free((*main_env)->curr_dir);
	(*main_env)->curr_dir = ft_strdup(cwd);
	if ((*main_env)->curr_dir == NULL)
		return (1);
	return (0);
}

static int	change_oldpwd_env(t_main_env **main_env, \
							t_our_env **find_oldpwd_node, char *tmp)
{
	if (find_env_node(&(*main_env)->our_env, " OLDPWD", find_oldpwd_node))
	{
		free((*find_oldpwd_node)->var_name);
		free((*find_oldpwd_node)->value);
		if (tmp[0] == '\0')
		{
			(*find_oldpwd_node)->var_name = ft_strdup("OLDPWD");
			(*find_oldpwd_node)->value = ft_strdup("");
		}
		else
		{
			(*find_oldpwd_node)->var_name = ft_strdup("OLDPWD=");
			(*find_oldpwd_node)->value = ft_strdup(tmp);
		}
		if ((*find_oldpwd_node)->var_name == NULL)
			return (free_main_env(main_env), \
				error_handler_num(main_env, -10, "cd", ""));
		if ((*find_oldpwd_node)->value == NULL)
			return (free_main_env(main_env), \
				error_handler_num(main_env, -10, "cd", ""));
	}
	return (0);
}

static int	change_dir_env(t_main_env **main_env)
{
	char		cwd[1024];
	t_our_env	*find_node;
	t_our_env	*find_oldpwd_node;
	char		*tmp;

	tmp = NULL;
	find_node = NULL;
	find_oldpwd_node = NULL;
	if ((*main_env)->curr_dir != NULL)
	{
		tmp = ft_strdup((*main_env)->curr_dir);
		if (tmp == NULL)
			return (free_main_env(main_env), 1);
	}
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (free(tmp), error_handler_num(main_env, -23, "getcwd fail", ""));
	if (change_cd_env(main_env, &find_node, cwd))
		return (free(tmp), error_handler_num(main_env, -10, "cd", ""));
	if (change_oldpwd_env(main_env, &find_oldpwd_node, tmp))
		return (free(tmp), error_handler_num(main_env, -10, "cd", ""));
	free((*main_env)->prev_dir);
	(*main_env)->prev_dir = ft_strdup(tmp);
	if ((*main_env)->prev_dir == NULL)
		return (free(tmp), 1);
	return (free(tmp), 0);
}

int	cd_exe(t_command *command, t_main_env **main_env)
{
	int			check;
	char		*cmd_prm;
	char		*dollar;

	check = 0;
	dollar = replace_vars(main_env, command->parameters, 0, 0);
	if (dollar == NULL)
		return (error_handler_num(main_env, -10, "cd_exe", ""));
	if (dollar[0] == ' ' && dollar[1] == '\0')
		return (free(dollar), error_handler_num(main_env, -16, NULL, NULL));
	cmd_prm = ft_substr(dollar, skip_spaces(dollar), ft_strlen(dollar));
	free(dollar);
	if (!cmd_prm)
		return (error_handler_num(main_env, -10, "cd ", "cmd_prm"));
	if (access(cmd_prm, F_OK) == 0)
	{
		check = chdir(cmd_prm);
		if (check)
			return (1);
		change_dir_env(main_env);
	}
	free(cmd_prm);
	return (0);
}
