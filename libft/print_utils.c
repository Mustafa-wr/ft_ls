/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 00:43:51 by mradwan           #+#    #+#             */
/*   Updated: 2025/12/09 15:31:04 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putstr(char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (write(1, "(null)", 6));
	if (s)
		while (s[i] != '\0')
			write(1, &s[i++], 1);
	return (i);
}

int	printhex(unsigned long long num, int z)
{
	unsigned long long	x;
	char				a[100];
	int					reminder;
	int					i;
	int					j;

	x = num;
	i = 0;
	if (num == 0)
		return (ft_putchar('0'));
	while (x != 0)
	{
		reminder = x % 16;
		if (reminder < 10)
			a[i++] = 48 + reminder;
		else
			a[i++] = (reminder + 'A' - 10) + (z * 32);
		x = x / 16;
	}
	a[i] = 0;
	j = (int)ft_strlen(a);
	while (j >= 1)
		ft_putchar(a[--j]);
	return ((int)ft_strlen(a));
}

int	printpercentage(void)
{
	return (write (1, "%", 1));
}