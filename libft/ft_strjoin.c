/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 15:59:32 by lnemor            #+#    #+#             */
/*   Updated: 2021/11/08 16:25:35 by lnemor           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*dest;
	size_t	csize;

	if (!s1 || !s2)
		return (NULL);
	csize = ft_strlen(s1) + ft_strlen(s2);
	i = 0;
	j = 0;
	dest = (char *)malloc(sizeof(char) * csize + 1);
	if (!dest || !s1 || !s2)
		return (NULL);
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		dest[i] = s2[j++];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
