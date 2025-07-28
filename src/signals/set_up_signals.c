/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:41:41 by ipavlov           #+#    #+#             */
/*   Updated: 2025/05/23 15:56:51 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	set_up_signals(t_main_env **main_env)
{
	struct sigaction	action;
	struct sigaction	quit_action;

	ft_memset(&action, 0, sizeof(struct sigaction));
	action.sa_handler = &sig_in_handler_parent;
	sigemptyset(&action.sa_mask);
	action.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &action, NULL) == -1)
	{
		perror("sigaction SIGINT");
		free_main_env(main_env);
		exit(1);
	}
	ft_memset(&quit_action, 0, sizeof(struct sigaction));
	quit_action.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &quit_action, NULL) == -1)
	{
		perror("sigaction SIGQUIT");
		free_main_env(main_env);
		exit(1);
	}
}
