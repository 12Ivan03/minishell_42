/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 10:33:59 by ipavlov           #+#    #+#             */
/*   Updated: 2024/10/21 14:19:30 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t			total;
	size_t			i;
	void			*ptr;
	unsigned char	*s;

	total = nmemb * size;
	if (nmemb > 0 && size > 0)
	{
		if (!(total % nmemb == 0) || !(total % size == 0))
			return (NULL);
	}
	ptr = malloc(total);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	s = (unsigned char *)ptr;
	while (i < total)
	{
		s[i] = 0;
		i++;
	}
	return (ptr);
}
