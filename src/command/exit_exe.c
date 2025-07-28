/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:31:58 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/21 13:21:08 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	find_first_space_position(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	return (i);
}

static int	eval_i_for_params(char *parameters)
{
	if (parameters[0] == '-' || parameters[0] == '+')
		return (1);
	else
		return (0);
}

static int	exit_helper_eval(t_main_env **main_env, char *temp, \
							char *parameters, int i)
{
	if (parameters[i])
	{
		temp = ft_substr(parameters, 0, \
						find_first_space_position(parameters));
		if (ft_isdigit(parameters[i]))
		{
			while (parameters[i] && ft_isdigit(parameters[i]) == 1)
				i++;
			if (ft_isalpha(parameters[i]))
				return (error_handler_nc(main_env, -17, temp, NULL), \
						free(temp), 0);
			if (parameters[i] == ' ' && \
			ft_isalpha(parameters[i + 1]) == 1)
				return (error_handler_nc(main_env, -15, "exit", NULL), \
						free(temp), 2);
		}
		else
			return (error_handler_nc(main_env, -17, temp, NULL), \
					free(temp), 0);
		free(temp);
	}
	return (1);
}

int	exit_exe(t_command *command, t_main_env **main_env)
{
	int		eval_error;
	char	*temp;
	char	*parameters;
	int		i;

	if (command->parameters[0] == '\0')
		return (0);
	temp = replace_vars(main_env, command->parameters, 0, 0);
	if (!temp)
		return (error_handler_nc(main_env, -10, "exit exe", ""), 0);
	parameters = ft_substr(temp, skip_spaces(temp), ft_strlen(temp));
	if (!parameters)
		return (free(temp), error_handler_num(main_env, -10, "exit", ""));
	printf("exit\n");
	eval_error = exit_helper_eval(main_env, temp, \
					parameters, eval_i_for_params(parameters));
	free(temp);
	i = ft_atoi(parameters);
	if (eval_error == 0)
		return (free(parameters), 0);
	else if (eval_error == 2)
		return (free(parameters), 2);
	(*main_env)->exit_status = ft_atoi(parameters);
	free(parameters);
	return (0);
}
