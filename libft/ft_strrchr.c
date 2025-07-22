/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 17:02:09 by lnemor            #+#    #+#             */
/*   Updated: 2021/11/08 11:22:43 by lnemor           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int chr)
{
	int	i;

	i = ft_strlen(str);
	while (i >= 0)
	{
		if ((unsigned char)str[i] == (unsigned char)chr)
			return ((char *)str + i);
		i--;
	}
	return (NULL);
}
