/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 17:17:06 by lnemor            #+#    #+#             */
/*   Updated: 2021/11/08 13:37:13 by lnemor           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *sch, size_t lenght)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (sch[i] == '\0')
		return ((char *)str);
	if (lenght == 0)
		return (0);
	while (str[i] && i < lenght)
	{
		if (sch[j] == str[i])
		{
			while ((sch[j] == str[i + j]) && i + j < lenght)
			{
				if (sch[j + 1] == '\0')
					return ((char *)str + i);
				j++;
			}
			j = 0;
		}
		i++;
	}
	return (NULL);
}
