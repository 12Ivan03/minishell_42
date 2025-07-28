/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 13:43:42 by ipavlov           #+#    #+#             */
/*   Updated: 2024/10/22 14:01:09 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	is_in_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

static void	check_the_set(size_t *start, size_t *end, \
						char const *set, char const *s1)
{
	while (is_in_set(s1[*start], set))
		(*start)++;
	while (is_in_set(s1[*end], set) && *end > *start)
		(*end)--;
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	new_len;
	char	*new_str;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = 0;
	end = ft_strlen(s1) - 1;
	check_the_set(&start, &end, set, s1);
	if (end < start)
	{
		new_str = (char *)malloc(1 * sizeof(char));
		if (new_str == NULL)
			return (NULL);
		new_str[0] = '\0';
		return (new_str);
	}
	new_len = end - start + 2;
	new_str = (char *)malloc(new_len * sizeof(char));
	if (new_str == NULL)
		return (NULL);
	ft_strlcpy(new_str, &s1[start], new_len);
	return (new_str);
}
