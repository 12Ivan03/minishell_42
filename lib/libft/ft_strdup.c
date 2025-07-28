/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:45:59 by ipavlov           #+#    #+#             */
/*   Updated: 2025/05/30 13:15:41 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

char	*ft_strdup(const char *s)
{
	int			lenstr;
	size_t		i;
	char		*cpy_str;

	lenstr = ft_strlen(s);
	cpy_str = (char *)malloc((lenstr + 1) * sizeof(char));
	if (cpy_str == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		cpy_str[i] = s[i];
		i++;
	}
	cpy_str[i] = '\0';
	return (cpy_str);
}
