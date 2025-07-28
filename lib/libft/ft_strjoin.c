/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 13:34:56 by ipavlov           #+#    #+#             */
/*   Updated: 2025/03/25 18:56:54 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static void	ft_join(const char *s1, const char *s2, char **str_cat)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (s1[i] != '\0')
	{
		(*str_cat)[j] = s1[i];
		i++;
		j++;
	}
	i = 0;
	while (s2[i] != '\0')
	{
		(*str_cat)[j] = s2[i];
		i++;
		j++;
	}
	(*str_cat)[j] = '\0';
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str_cat;
	size_t	size_all;

	size_all = ft_strlen(s1) + ft_strlen(s2);
	str_cat = (char *)malloc((size_all + 1) * sizeof(char));
	if (str_cat == NULL)
	{
		return (NULL);
	}
	ft_join(s1, s2, &str_cat);
	return (str_cat);
}
