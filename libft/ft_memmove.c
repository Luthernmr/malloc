/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 11:15:01 by lnemor            #+#    #+#             */
/*   Updated: 2021/11/04 14:49:22 by lnemor           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{	
	const char	*src1;
	char		*dest1;
	int			i;

	i = n - 1;
	dest1 = dest;
	src1 = src;
	if (!dest1 && !src)
		return (NULL);
	if (src1 <= dest1)
	{
		while (n > 0)
		{
			dest1[i] = src1[i];
			i--;
			n--;
		}
	}
	else
		ft_memcpy(dest, src, n);
	return (dest);
}
