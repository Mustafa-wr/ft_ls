/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 21:09:44 by mradwan           #+#    #+#             */
/*   Updated: 2025/12/08 21:10:29 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	print_option_error(char c)
{
	write(2, "ls: illegal option -- ", 22);
	write(2, &c, 1);
	write(2, "\n", 1);
}

static int	parse_option_string(char *str, t_options *opts)
{
	int	j;

	j = 1;
	while (str[j])
	{
		if (str[j] == 'l')
			opts->l = 1;
		else if (str[j] == 'R')
			opts->c_r = 1;
		else if (str[j] == 'a')
			opts->a = 1;
		else if (str[j] == 't')
			opts->t = 1;
		else if (str[j] == 'r')
			opts->r = 1;
		else
			return (print_option_error(str[j]), 0);
		j++;
	}
	return (1);
}

int	parse_options(int ac, char **av, t_options *opts, int *start_index)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (av[i][0] == '-' && av[i][1] != '\0')
		{
			if (!parse_option_string(av[i], opts))
				return (0);
		}
		else
		{
			*start_index = i;
			return (1);
		}
		i++;
	}
	*start_index = ac;
	return (1);
}