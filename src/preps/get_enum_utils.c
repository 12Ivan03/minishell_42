/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_enum_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:58:05 by ipavlov           #+#    #+#             */
/*   Updated: 2025/05/23 16:59:20 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	built_in_command(char *str)
{
	int			i;
	const char	*built_in[] = {"echo", "cd", "pwd", "export", \
								"unset", "env", "exit", NULL};

	i = 0;
	while (built_in[i])
	{
		if (!ft_strncmp(str, built_in[i], ft_strlen(built_in[i]) + 1))
			return (1);
		i++;
	}
	return (0);
}

int	detect_program(t_list_words	**list_words)
{
	if ((*list_words)->prev == NULL)
		return (1);
	if ((*list_words)->prev != NULL && (*list_words)->prev->word[0] == '|')
		return (1);
	return (0);
}
