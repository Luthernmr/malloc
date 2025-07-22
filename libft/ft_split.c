/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 16:07:44 by lnemor            #+#    #+#             */
/*   Updated: 2021/11/10 19:13:33 by lnemor           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

static int	ft_free_all(char **dest, int i)
{
	while (i > 0)
	{
		free(dest[i]);
		i--;
	}
	free(dest);
	return (-1);
}

static int	ft_count_strs(char const *str, char c)
{
	size_t	count;
	size_t	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i] != c && str[i])
			count++;
		while (str[i] != c && str[i])
			i++;
	}
	return (count);
}
// rrrr 

static char	*ft_copy_str(const char *str, char c, int count)
{
	char	*dest;
	size_t	i;

	i = 0;
	dest = malloc(sizeof(char) * count + 1);
	if (!dest)
		return (NULL);
	while (str[i] && str[i] != c)
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static char	**ft_make_split(char **dest, const char *str, char c)
{
	size_t	i;
	size_t	j;
	size_t	count;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == c && str[i] != '\0')
			i++;
		else
		{
			count = 0;
			while (str[i + count] != c && str[i + count] != '\0')
				count++;
			dest[j] = ft_copy_str(str + i, c, count);
			if (dest[j] == NULL)
				ft_free_all(dest, j);
			i += count;
			j++;
		}
	}
	return (dest);
}

char	**ft_split(char const *str, char c)
{
	char	**dest;
	size_t	nb_word;

	if (!str)
		return (NULL);
	nb_word = ft_count_strs(str, c);
	dest = (char **)malloc(sizeof(char *) * (nb_word + 1));
	if (!dest)
		return (NULL);
	ft_make_split(dest, str, c);
	dest[nb_word] = NULL;
	return (dest);
}
