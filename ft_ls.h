/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:59:14 by mradwan           #+#    #+#             */
/*   Updated: 2025/12/08 17:04:23 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H

# include <dirent.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>

# define FT_LS_H

# define FLAG_L

typedef struct s_options
{
	int l; // long format    (-l)
	int c_r; // recursive      (-R)
	int a; // all/hidden     (-a)
	int r; // reverse        (-r)
	int t; // time sort      (-t)
}	t_options;

#endif