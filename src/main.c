/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerokhin <aerokhin@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 12:13:54 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/26 19:04:44 by aerokhin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	read_line_error_check(t_main_env **main_env, char **str)
{
	(*main_env)->list_words = lexer(main_env, *str);
	ft_free((void **)&(*str));
	if ((*main_env)->list_words == NULL)
		return ;
	(*main_env)->list_tokens = parsing(main_env, (*main_env)->list_words);
	if ((*main_env)->list_tokens == NULL)
		return (free_list_words(&(*main_env)->list_words));
	(*main_env)->export_error = 0;
	analyze_and_dispatch(main_env);
	free_list_words(&(*main_env)->list_words);
	free_list_tokens(&((*main_env)->list_tokens));
	free_packages_d(&(*main_env)->package);
	clear_here_doc_files(main_env);
}

void	error_check_rl(t_main_env **main_env, char **str, int *error_check)
{
	if (!(*error_check))
		read_line_error_check(main_env, str);
	else if ((*error_check) == 3)
	{
		ft_free((void **)&(*str));
		free_main_env(main_env);
		exit(2);
	}
}

void	read_line_loop(t_main_env **main_env, char **str, int *error_check)
{
	char	*prmpt;

	prmpt = prompt(main_env);
	if (!prmpt)
		(*str) = readline(TXT_GREEN PRG_NAME TXT_RES"/? >");
	else
		(*str) = readline(prmpt);
	free (prmpt);
	if (!(*str))
	{
		printf("exit\n");
		free_main_env(main_env);
		exit(0);
	}
	if ((*str)[0] != '\0')
	{
		(*main_env)->p_error = 0;
		(*error_check) = check_readline(main_env, str);
		add_history(*str);
		error_check_rl(main_env, str, error_check);
	}
	ft_free((void **)&(*str));
}

int	main(int argc, char *argv[], char **envp)
{
	char			*str;
	int				error_check;
	t_main_env		*main_env;

	(void)argc;
	(void)argv;
	error_check = 0;
	main_env = (t_main_env *)malloc(sizeof(t_main_env));
	if (!main_env)
		exit (error_handler_num(&main_env, -10, NULL, NULL));
	init_main(&main_env);
	error_check = read_our_env(envp, &main_env);
	if (error_check)
	{
		free_main_env(&main_env);
		exit (error_main());
	}
	set_up_signals(&main_env);
	str = NULL;
	while (1)
		read_line_loop(&main_env, &str, &error_check);
	return (0);
}
