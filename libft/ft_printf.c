/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 00:43:18 by mradwan           #+#    #+#             */
/*   Updated: 2025/12/09 15:28:49 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	printptr(unsigned long long pointer)
{
	int	c;

	c = ft_putstr("0x");
	return (c + printhex(pointer, 1));
}

int	ft_putnbr(int n)
{
    int	len;

    len = 0;
    if (n <= 2147483647)
    {
        if (n < 0)
        {
            if (n == -2147483648)
                return (ft_putstr("-2147483648"));
            len += ft_putchar('-');
            n = n * -1;
        }
        if (n <= 9)
            len += ft_putchar(n + '0');
        if (n > 9)
        {
            len += ft_putnbr(n / 10);
            len += ft_putnbr(n % 10);
        }
    }
    return (len);
}

int	ft_putunnbr(unsigned int n)
{
	int	len;

	len = 0;
	if (n < 0)
	{
		len += ft_putchar('-');
		n = n * -1;
	}
	if (n <= 9)
		len += ft_putchar(n + '0');
	if (n > 9)
	{
		len += ft_putnbr(n / 10);
		len += ft_putnbr(n % 10);
	}
	return (len);
}

int	ft_format(va_list args, const char format, int printl)
{
	if (format == 'c')
		printl = ft_putchar(va_arg(args, int));
	else if (format == 's')
		printl = ft_putstr(va_arg(args, char *));
	else if (format == '%')
		printl = printpercentage();
	else if (format == 'p')
		printl = printptr(va_arg(args, unsigned long long));
	else if (format == 'x')
		printl = printhex(va_arg(args, unsigned int), 1);
	else if (format == 'X')
		printl = printhex(va_arg(args, unsigned int), 0);
	else if (format == 'd' || format == 'i')
		printl = ft_putnbr(va_arg(args, int));
	else if (format == 'u')
		printl = ft_putunnbr(va_arg(args, unsigned int));
	return (printl);
}
// i is print lenght

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		num_chars;

	va_start(args, format);
	num_chars = 0;
	i = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			num_chars += ft_format(args, format[i + 1], num_chars);
			i++;
		}
		else
			num_chars += ft_putchar(format[i]);
		i++;
	}
	va_end(args);
	return (num_chars);
}

// #include <stdio.h>

// int main(void)
// {
// 	ft_printf("%u\n", -11);
// 	printf("%u\n", -11);
// }