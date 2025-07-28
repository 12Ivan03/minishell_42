/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_our2env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerokhin <aerokhin@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:55:17 by ipavlov           #+#    #+#             */
/*   Updated: 2025/05/30 15:41:55 by aerokhin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	env_len(t_our_env *env)
{
	int	i;

	i = 0;
	while (env != NULL)
	{
		env = env->next;
		i++;
	}
	return (i);
}

char	**convert_our2env(t_main_env **main_env)
{
	int			len;
	char		**res;
	t_our_env	*our_env;
	int			i;

	len = env_len((*main_env)->our_env);
	res = (char **)malloc((len + 1) * sizeof(char *));
	i = 0;
	our_env = (*main_env)->our_env;
	while (our_env)
	{
		res[i] = ft_strjoin(our_env->var_name, our_env->value);
		if (res[i] == NULL)
		{
			free_str_array(res);
			return (NULL);
		}
		our_env = our_env->next;
		i++;
	}
	res[i] = NULL;
	return (res);
}
