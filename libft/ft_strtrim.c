/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 16:27:02 by lnemor            #+#    #+#             */
/*   Updated: 2021/11/08 16:44:50 by lnemor           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_from_start(const char *str, const char *set)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(str))
	{
		if (ft_strchr(set, str[i]) == 0)
			break ;
		i++;
	}
	return (i);
}

static int	ft_from_end(const char *str, const char *set)
{
	size_t	i;
	size_t	length;

	i = 0;
	length = ft_strlen(str);
	while (i < length)
	{
		if (ft_strchr(set, str[length - i - 1]) == 0)
			break ;
		i++;
	}
	return (length - i);
}

char	*ft_strtrim(const char *str, const char *set)
{
	char	*dest;
	size_t	to_start;
	size_t	to_end;
	int		i;

	if (!str || !set)
		return (NULL);
	i = 0;
	to_start = ft_from_start(str, set);
	to_end = ft_from_end(str, set);
	if (to_start == ft_strlen(str))
		return (ft_calloc(1, sizeof(char)));
	dest = malloc(sizeof(char) * (to_end - to_start + 1));
	if (!dest)
		return (NULL);
	if (str[i] == '\0')
		return (dest);
	ft_strlcpy(dest, &str[to_start], to_end - to_start + 1);
	return (dest);
}
