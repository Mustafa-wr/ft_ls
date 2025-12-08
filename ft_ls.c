/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:52:32 by mradwan           #+#    #+#             */
/*   Updated: 2025/12/08 18:14:35 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	parse_options(int ac, char **av, t_options *opts, int *start_index)
{
	int	i;
	int j;

	j = 1;
	i = 0;
	if (ac < 2)
	{
		*start_index = 1;
		return (2);  // No options provided
	}
	if (av[1][0] != '-')
	{
		i = 1;
		while (av[i])
		{
			while (av[i][j])
			{
				if (av[i][j] == 'l')
					opts->l = 1;
				else if (av[i][j] == 'R')
					opts->c_r = 1;
				else if (av[i][j] == 'a')
					opts->a = 1;
				else if (av[i][j] == 't')
					opts->t = 1;
				else if (av[i][j] == 'r')
					opts->r = 1;
				else
					return (0);
			}
		}
	}
	else
		start_index = 1;
	return (1);
}

int	main(int ac, char **av)
{
	DIR				*d;
	struct dirent	*ent;
    int				start_index;
	
	t_options opts = {0};
	start_index = 0;
    if (!parse_options(ac, av, &opts, &start_index))
        return (write(2, "ls: illegal option -- ", strlen("ls: illegal option -- ")) ,1);
	d = opendir(".");
	if (!d)
	{
		perror("opendir");
		return (1);
	}
	ent = readdir(d);
	while (ent != NULL)
	{
		if (ent->d_name[0] != '.')
		{
			write(1, ent->d_name, strlen(ent->d_name));
			write(1, "\n", 1);
		}
		ent = readdir(d);
	}
	closedir(d);
	return (0);
}
