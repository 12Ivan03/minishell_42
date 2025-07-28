/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ip_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 12:37:50 by ipavlov           #+#    #+#             */
/*   Updated: 2025/05/24 11:53:02 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_list_tokens	*parsing(t_main_env **main_env, t_list_words *list_words)
{
	t_list_tokens	*temp;

	temp = NULL;
	while (list_words != NULL)
	{
		if (link_t_token(main_env, &temp, &list_words))
		{
			free_list_tokens(&(*main_env)->list_tokens);
			printf("error with parsing\n");
			return (NULL);
		}
		if (list_words != NULL)
			list_words = list_words->next;
	}
	return (temp);
}
