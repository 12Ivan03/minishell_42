/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerokhin <aerokhin@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:46:05 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/26 19:04:44 by aerokhin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	error_handler_nc_one(t_main_env **main_env, int n, \
							char *command, char *option)
{
	(*main_env)->exit_status = 1;
	if (n == -10)
		err_prt_three("malloc failed: ", option, " ", command);
	else if (n == -11)
	{
		if (!ft_strncmp("pwd", command, 3))
			err_prt_char("pwd: -", option[1], ": invalid option");
		else
			err_prt_char("env: invalid option: -- '", option[1], "'");
	}
	else if (n == -12)
	{
		if (!ft_strncmp("pwd", command, 3))
			err_prt_n(PRG_NAME"pwd: invalid option");
		else
			err_prt_two("env: '", option, "': No such file or directory");
	}
	else if (n == -13)
		err_prt_three("export: '", option, "' ", command);
	else if (n == -14)
		err_prt_two(PRG_NAME"cd: ", command, \
				": No such file or directory");
}

void	error_handler_nc_two(t_main_env **main_env, int n, \
							char *command, char *option)
{
	(*main_env)->exit_status = 1;
	if (n == -15)
		err_prt_two(PRG_NAME, command, ": too many arguments");
	else if (n == -16)
		err_prt_n(PRG_NAME"cd: HOME not set");
	else if (n == -17)
	{
		(*main_env)->exit_status++;
		err_prt_two(PRG_NAME"exit: ", command, \
						": numeric argument required");
	}
	else if (n == -18)
		err_prt_one("analyze and dispatch: Error creating ", command);
	else if (n == -19)
		err_prt_one("child_process ", command);
	else if (n == -20)
		err_prt_two(PRG_NAME, command, ": No such file or directory");
	else if (n == -21)
		err_prt_three("unset: '", option, "' ", command);
	else if (n == -22)
	{
		(*main_env)->exit_status = 127;
		err_prt_two(PRG_NAME, command, ": command not found");
	}
}

void	error_handler_nc_three(t_main_env **main_env, int n, \
							char *command, char *option)
{
	(*main_env)->exit_status = 1;
	if (n == -23)
		err_prt_n(command);
	else if (n == -24)
	{
		(*main_env)->exit_status = 2;
		err_prt_n(PRG_NAME"syntax error near unexpected token `|`");
	}
	else if (n == -25)
		err_prt_three(PRG_NAME, command, ": ", option);
	else if (n == -26)
	{
		(*main_env)->exit_status = 2;
		err_prt_one(PRG_NAME, command);
	}
	else if (n == -27)
		err_prt_one(PRG_NAME, command);
	else if (n == -28)
		err_prt_two(PRG_NAME"warning: here-document delimited "\
					"by end-of-file (wanted `", command, "')");
}

void	error_handler_nc_four(t_main_env **main_env, int n, \
							char *command, char *option)
{
	if (n == -29)
	{
		(*main_env)->exit_status = 258;
		err_prt_n(PRG_NAME"syntax error near unexpected token `newline'");
	}
	else if (n == -30)
		err_prt_three(PRG_NAME, "cd :", command, ": Permission denied");
	else if (n == -31)
		err_prt_two(PRG_NAME, command, ": Is a directory");
	else if (n == -32)
		err_prt_three(PRG_NAME, "cd :", command, ": Not a directory");
}
