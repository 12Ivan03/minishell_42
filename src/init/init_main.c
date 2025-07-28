/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerokhin <aerokhin@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:38:47 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/21 14:48:50 by aerokhin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	init_main(t_main_env **main_env)
{
	(*main_env)->list_words = NULL;
	(*main_env)->list_tokens = NULL;
	(*main_env)->curr_dir = NULL;
	(*main_env)->prev_dir = NULL;
	(*main_env)->home_dir = NULL;
	(*main_env)->here_doc_index = 0;
	(*main_env)->real_env = NULL;
	(*main_env)->package = NULL;
	(*main_env)->our_env = NULL;
	(*main_env)->p_error = 0;
	(*main_env)->export_error = 0;
	(*main_env)->exit_status = 0;
}
