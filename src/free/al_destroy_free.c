/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   al_destroy_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerokhin <aerokhin@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 21:34:41 by aerokhin          #+#    #+#             */
/*   Updated: 2025/06/12 21:30:42 by aerokhin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_str_array(char **arr)
{
	int	i;

	i = 0;
	if (arr == NULL)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	if (arr)
	{
		free(arr);
		arr = NULL;
	}
}

void	free_list_words(t_list_words **list_words)
{
	t_list_words	*tmp;

	if (*list_words == NULL)
		return ;
	while (*list_words)
	{
		tmp = (*list_words)->next;
		if ((*list_words)->word)
			free((*list_words)->word);
		free((*list_words));
		*list_words = tmp;
	}
}

void	free_list_tokens(t_list_tokens **tokens)
{
	t_list_tokens	*temp;

	if (*tokens == NULL)
		return ;
	while ((*tokens) != NULL)
	{
		temp = (*tokens)->next;
		if ((*tokens)->value)
			free_token_void(tokens);
		free((*tokens));
		(*tokens) = temp;
	}
}

void	free_our_env(t_our_env **our_env)
{
	t_our_env	*tmp;

	while (*our_env)
	{
		tmp = (*our_env)->next;
		if ((*our_env)->var_name)
			free((*our_env)->var_name);
		if ((*our_env)->value)
			free((*our_env)->value);
		free((*our_env));
		(*our_env) = tmp;
	}
	our_env = NULL;
}

void	free_node_file(t_node_file **node)
{
	t_node_file	*tmp;

	while (*node != NULL)
	{
		tmp = (*node)->next;
		if ((*node)->name)
			free((*node)->name);
		free((*node));
		(*node) = tmp;
	}
	(*node) = NULL;
}
