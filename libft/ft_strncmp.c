/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 17:11:27 by lnemor            #+#    #+#             */
/*   Updated: 2021/11/08 11:21:19 by lnemor           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *first, const char *second, size_t lenght)
{
	size_t	i;

	i = 0;
	while ((unsigned char)first[i] == (unsigned char)second[i]
		&& first[i] && second[i] && i < lenght - 1)
		i++;
	if (lenght > 0)
		return ((unsigned char)first[i] - (unsigned char)second[i]);
	return (0);
}
