/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   al_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerokhin <aerokhin@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 10:21:29 by aerokhin          #+#    #+#             */
/*   Updated: 2025/06/26 19:04:44 by aerokhin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*read_curr_dir(void)
{
	char	*curr_dir;

	curr_dir = getcwd(NULL, 0);
	if (!curr_dir)
		return (NULL);
	else
		return (curr_dir);
}

char	*prompt(t_main_env **main_env)
{
	char	*prompt;
	char	*tmp;
	char	*curr_dir;

	curr_dir = read_curr_dir();
	if (curr_dir == NULL)
		return (NULL);
	if (ft_strlen(curr_dir) > MAX_LEN_PROMPT)
	{
		tmp = ft_substr(curr_dir, ft_strlen(curr_dir) - (MAX_LEN_PROMPT - 4), \
		MAX_LEN_PROMPT - 4);
		if (!tmp)
		{
			free (curr_dir);
			return (error_handler_null(main_env, -10, "prompt error", ""));
		}
		prompt = ft_str3join(TXT_GREEN PRG_NAME TXT_RES "...", tmp, " > ");
		free (tmp);
	}
	else
		prompt = ft_str3join(TXT_GREEN PRG_NAME TXT_RES, curr_dir, " > ");
	free (curr_dir);
	if (!prompt)
		return (error_handler_null(main_env, -10, "prompt error", ""));
	return (prompt);
}
