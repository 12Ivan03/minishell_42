/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:10:18 by ipavlov           #+#    #+#             */
/*   Updated: 2024/10/21 13:26:46 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	s_len;

	s_len = ft_strlen(s);
	if ((char)c == '\0')
	{
		return ((char *) &s[s_len]);
	}
	while (s_len > 0)
	{
		if (s[s_len - 1] == (char)c)
		{
			return ((char *) &s[s_len - 1]);
		}
		s_len--;
	}
	return (NULL);
}
