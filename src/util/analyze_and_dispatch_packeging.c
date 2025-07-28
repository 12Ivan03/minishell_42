/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_and_dispatch_packeging.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerokhin <aerokhin@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 15:39:05 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/12 21:56:35 by aerokhin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	append_packeges(t_list_tokens **tokens, \
		t_package **temp, t_package **package)
{
	t_package		*temp_2;

	temp_2 = NULL;
	if ((*package) != NULL)
	{
		temp_2 = (*package);
		while (temp_2->next != NULL)
			temp_2 = temp_2->next;
		temp_2->next = (*temp);
		(*temp)->prev = temp_2;
	}
	else
		(*package) = (*temp);
	if ((*tokens) != NULL && (*tokens)->token == PIPE)
		(*tokens) = (*tokens)->next;
}

t_package	*prepare_packages(t_main_env **main_env)
{
	t_list_tokens	*tokens;
	t_package		*temp;
	t_package		*package;
	int				error;

	package = NULL;
	tokens = (*main_env)->list_tokens;
	while (tokens != NULL)
	{
		temp = init_package();
		if (temp == NULL)
			return (error_handler_null(main_env, -10, "prepare_packages", ""));
		while (tokens != NULL && tokens->token != PIPE)
		{
			error = populate_package(main_env, temp, tokens);
			if (error == 1)
				return (free_packages_d(&package), free_package(&temp), \
						error_handler_null(main_env, -10, "prepare_pack", ""));
			if (error == 2)
				return (free_packages_d(&package), free_package(&temp), NULL);
			tokens = tokens->next;
		}
		append_packeges(&tokens, &temp, &package);
	}
	return (package);
}
