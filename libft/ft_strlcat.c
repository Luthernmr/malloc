/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 14:25:38 by lnemor            #+#    #+#             */
/*   Updated: 2021/11/08 11:40:21 by lnemor           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	size_dest;
	size_t	size_src;

	i = 0;
	j = ft_strlen(dest);
	size_dest = ft_strlen(dest);
	size_src = ft_strlen(src);
	if (size == 0)
		return (size_src);
	while (src[i] && j < size - 1)
	{
		dest[j] = src[i];
		j++;
		i++;
	}
	if (size < size_dest)
		return (size_src + size);
	dest[j] = '\0';
	return (size_dest + size_src);
}
