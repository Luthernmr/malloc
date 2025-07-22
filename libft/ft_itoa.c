/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 10:05:57 by lnemor            #+#    #+#             */
/*   Updated: 2021/11/12 15:16:31 by lnemor           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len_str(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
	{
			len = 1;
	}
	while (n != 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

static char	*convert(char *str, unsigned int num, long int len)
{
	while (num > 0)
	{
		str[len - 1] = (num % 10) + '0';
		num = num / 10;
		len--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char			*str;
	size_t			i;
	long int		len;
	unsigned int	num;

	i = 0;
	len = len_str(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (n == 0)
		(str[i] = '0');
	if (n < 0)
	{
		n = n * -1;
		str[i] = '-';
	}
	num = n;
	str = convert(str, num, len);
	return (str);
}
