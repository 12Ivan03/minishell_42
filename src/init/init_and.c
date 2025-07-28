/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 15:31:17 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/07 16:38:13 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_package	*init_package(void)
{
	t_package	*create;

	create = (t_package *)malloc(sizeof(t_package));
	if (create == NULL)
		return (NULL);
	create->command = NULL;
	create->program = NULL;
	create->flag = 0;
	create->redir = NULL;
	create->prev = NULL;
	create->next = NULL;
	return (create);
}
