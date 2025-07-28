/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penchoivanov <penchoivanov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:39:36 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/13 13:08:25 by penchoivano      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	new_line_or_not(t_command *command, char **temp)
{
	if (ft_strncmp(command->option->opt_name, "-n", \
		ft_strlen(command->option->opt_name)) != 0)
		printf("%s", (*temp));
	else
		printf("%s\n", (*temp));
}

int	echo_exe(t_command *command, t_main_env **main_env)
{
	char		*res;
	char		*temp;
	int			i;

	res = replace_vars(main_env, command->parameters, 0, 0);
	if (res[0] == ' ')
		i = 1;
	else
		i = 0;
	temp = ft_substr(res, i, ft_strlen(res));
	free(res);
	if (command->parameters[0] == ' ' && command->parameters[1] == '-' && \
		command->parameters[2] == 'n' && command->parameters[3] == '\0')
		return (1);
	new_line_or_not(command, &temp);
	free(temp);
	return (0);
}
