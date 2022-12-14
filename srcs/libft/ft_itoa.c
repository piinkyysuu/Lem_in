/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 14:30:56 by itkimura          #+#    #+#             */
/*   Updated: 2022/11/09 10:34:03 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	number_of_digit(int n)
{
	int	len;

	len = 0;
	if (n < 0)
		len++;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		len;
	long	nb;
	char	*str;

	if (n == 0)
		return (ft_strdup("0"));
	len = number_of_digit(n) + 1;
	str = (char *)malloc(sizeof(char) * len);
	if (!str)
		return (0);
	nb = n;
	if (nb < 0)
	{
		nb *= -1;
		str[0] = '-';
	}
	str[--len] = '\0';
	while (nb)
	{
		str[--len] = nb % 10 + '0';
		nb /= 10;
	}
	return (str);
}
