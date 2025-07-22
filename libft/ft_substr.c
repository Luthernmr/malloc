/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 15:00:04 by lnemor            #+#    #+#             */
/*   Updated: 2021/11/08 15:58:00 by lnemor           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*new;
	size_t	lenstr;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	lenstr = ft_strlen(str) - start;
	if ((start >= ft_strlen(str)))
		return (ft_strdup(""));
	if (len > lenstr)
		len = lenstr;
	new = (char *)malloc(sizeof(char) * ((unsigned int)len + 1));
	if (!new)
		return (NULL);
	while (str[i + start] && j < (unsigned int)len)
	{
		new[j++] = str[i++ + start];
	}
	new[j] = '\0';
	return (new);
}
