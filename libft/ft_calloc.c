/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 10:17:53 by lnemor            #+#    #+#             */
/*   Updated: 2021/11/08 10:31:52 by lnemor           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t elementCount, size_t elementSize)
{
	char	*dest;

	dest = malloc(elementCount * elementSize);
	if (!dest)
		return (NULL);
	ft_memset(dest, 0, elementCount * elementSize);
	return (dest);
}
