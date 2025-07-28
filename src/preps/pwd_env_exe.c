/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_env_exe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:16:38 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/16 14:57:18 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	pwd_env_exe_helper(t_main_env **main_env, t_command *command, \
								char *pwd)
{
	if (!ft_strncmp("pwd", command->command, 3))
	{
		if (getcwd(pwd, 1024))
			printf("%s\n", pwd);
		else
			error_handler_nc(main_env, -23, "failed: getcwd", NULL);
	}
}

int	pwd_env_exe(t_command *command, t_main_env **main_env)
{
	char		pwd[1024];
	t_our_env	*env;

	env = (*main_env)->our_env;
	pwd_env_exe_helper(main_env, command, pwd);
	if (!ft_strncmp("env", command->command, 3))
	{
		while (env != NULL)
		{
			if (env->var_name[ft_strlen(env->var_name) - 1] == '=')
			{
				printf("%s", env->var_name);
				if (env->value[0] != '\0')
					printf("%s", env->value);
				printf("\n");
			}
			env = env->next;
		}
	}
	return (0);
}
