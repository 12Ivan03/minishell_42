/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_joins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerokhin <aerokhin@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 20:31:53 by aerokhin          #+#    #+#             */
/*   Updated: 2025/05/30 15:34:29 by aerokhin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*join_and_free(char **s1, char **s2)
{
	char	*joined;

	if (!*s1 || !*s2)
		return (NULL);
	joined = ft_strjoin(*s1, *s2);
	if (!joined)
	{
		free(*s1);
		free(*s2);
		return (NULL);
	}
	free(*s1);
	free(*s2);
	*s1 = NULL;
	*s2 = NULL;
	return (joined);
}

char	*ft_str3join(char *s1, char *s2, char *s3)
{
	size_t		len;
	char		*res;
	size_t		i;
	size_t		j;

	len = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	res = (char *)ft_calloc((len + 1), sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	j = -1;
	while (++j < ft_strlen(s1))
		res [i++] = s1[j];
	j = -1;
	while (++j < ft_strlen(s2))
		res [i++] = s2[j];
	j = -1;
	while (++j < ft_strlen(s3))
		res [i++] = s3[j];
	return (res);
}
