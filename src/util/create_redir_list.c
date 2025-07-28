/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redir_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penchoivanov <penchoivanov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:33:55 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/13 10:48:06 by penchoivano      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	link_redir(t_node_file *node, t_package *temp)
{
	t_node_file	*temp_node;

	temp_node = ((t_node_file *)temp->redir);
	if (temp_node != NULL)
	{
		while (temp_node->next != NULL)
			temp_node = temp_node->next;
		temp_node->next = node;
		node->prev = temp_node;
	}
	else
		temp->redir = node;
}

int	init_redir_node(t_node_file	**node, int e_num)
{
	if ((*node) == NULL)
		return (1);
	(*node)->name = NULL;
	(*node)->redir_enum = e_num;
	(*node)->next = NULL;
	(*node)->prev = NULL;
	return (0);
}

int	create_redir_list(t_main_env **main_env, t_tokens enum_token, \
						void *token_value, t_package *temp)
{
	t_node_file	*node;
	int			error;

	error = 0;
	node = (t_node_file *)malloc(sizeof(t_node_file));
	if (init_redir_node(&node, enum_token))
		return (free(node), 1);
	if (enum_token == REDIRECTION_HERE_DOC)
	{
		error = handle_heredoc((t_re_here *)token_value, main_env);
		if (error == -100)
			return (free(node), 2);
		node->name = ft_strdup(((t_re_here *)token_value)->file_name);
		if (node->name == NULL)
			return (1);
	}
	else
	{
		node->name = replace_vars(main_env, \
							((t_re_input *)token_value)->file_name, 0, 0);
		if (node->name == NULL)
			return (free(node), 1);
	}
	link_redir(node, temp);
	return (0);
}
