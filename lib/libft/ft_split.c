/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 17:00:07 by ipavlov           #+#    #+#             */
/*   Updated: 2024/10/19 16:27:02 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	count_str(char const *s, char c)
{
	int	i;
	int	how_many;
	int	in_group;

	in_group = 0;
	how_many = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && !in_group)
		{
			in_group = 1;
			how_many++;
		}
		else if (s[i] == c)
			in_group = 0;
		i++;
	}
	return (how_many);
}

static void	find_start_end_of_str(char const *s, char c, int *start, int *i)
{
	while (s[*i] == c && s[*i] != '\0')
		(*i)++;
	*start = *i;
	while (s[*i] != c && s[*i] != '\0')
		(*i)++;
}

static void	*free_str_from_substr(char **arr_ptrs, int arr_position)
{
	while (arr_position > 0)
	{
		free(arr_ptrs[--arr_position]);
	}
	free(arr_ptrs);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**arr_ptrs;
	int		i;
	int		start;
	int		arr_position;

	arr_ptrs = (char **)malloc((count_str(s, c) + 1) * sizeof(char *));
	if (arr_ptrs == NULL)
		return (NULL);
	arr_position = 0;
	start = 0;
	i = 0;
	while (s[i] != '\0')
	{
		find_start_end_of_str(s, c, &start, &i);
		if (start < i)
		{
			arr_ptrs[arr_position] = ft_substr(s, start, i - start);
			if (arr_ptrs[arr_position] == NULL)
				return (free_str_from_substr(arr_ptrs, arr_position));
			arr_position++;
		}
	}
	arr_ptrs[arr_position] = NULL;
	return (arr_ptrs);
}
