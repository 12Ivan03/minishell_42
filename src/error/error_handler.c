/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerokhin <aerokhin@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:12:24 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/23 13:11:55 by aerokhin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	error_main(void)
{
	printf(TXT_BOLD TXT_RED "error with initializing program\n"TXT_RES);
	return (1);
}

int	error_handler_num(t_main_env **main_env, int n, char *command, char *option)
{
	error_handler_nc(main_env, n, command, option);
	return (1);
}

void	*error_handler_null(t_main_env **main_env, int n, \
							char *command, char *option)
{
	error_handler_nc(main_env, n, command, option);
	return (NULL);
}

void	error_handler_nc(t_main_env **main_env, int n, \
						char *command, char *option)
{
	if (n >= -14)
		error_handler_nc_one(main_env, n, command, option);
	else if (n >= -22 && n < -14)
		error_handler_nc_two(main_env, n, command, option);
	else if (n >= -28 && n < -22)
		error_handler_nc_three(main_env, n, command, option);
	else if (n < -28)
		error_handler_nc_four(main_env, n, command, option);
}
