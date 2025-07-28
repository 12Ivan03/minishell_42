/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_child_processes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerokhin <aerokhin@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 14:08:43 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/26 12:37:27 by aerokhin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	init_cp(t_cp *cp, int prev_fd)
{
	cp->has_in = 0;
	cp->has_out = 0;
	cp->file_fd_in = -1;
	cp->file_fd_out = -1;
	cp->error_flag = 0;
	cp->c_prev_fd = prev_fd;
}
