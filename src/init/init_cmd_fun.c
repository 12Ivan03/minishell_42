/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd_fun.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerokhin <aerokhin@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:39:13 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/09 14:51:19 by aerokhin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	init_command_function(t_command	**command, char *str)
{
	(*command) = (t_command *)malloc(sizeof(t_command));
	if (!(*command))
		return (1);
	(*command)->command = ft_strdup(str);
	if ((*command)->command == NULL)
		return (1);
	(*command)->option = (t_opt *)malloc(sizeof(t_opt));
	if ((*command)->option == NULL)
		return (1);
	return (0);
}

int	init_program_function(t_program	**program, char *str)
{
	(*program) = (t_program *)malloc(sizeof(t_program));
	if (!(*program))
		return (1);
	(*program)->name = ft_strdup(str);
	if ((*program)->name == NULL)
		return (1);
	(*program)->parameters = (char *)ft_calloc(1, sizeof(char));
	if ((*program)->parameters == NULL)
		return (1);
	return (0);
}
