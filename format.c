/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 12:00:00 by mradwan           #+#    #+#             */
/*   Updated: 2025/12/09 17:06:58 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	set_file_type(char *perms, mode_t mode)
{
	if (S_ISDIR(mode))
		perms[0] = 'd';
	else
		perms[0] = '-';
}

static void	set_owner_perms(char *perms, mode_t mode)
{
	if (mode & S_IRUSR)
		perms[1] = 'r';
	else
		perms[1] = '-';
	if (mode & S_IWUSR)
		perms[2] = 'w';
	else
		perms[2] = '-';
	if (mode & S_IXUSR)
		perms[3] = 'x';
	else
		perms[3] = '-';
}

static void	set_group_perms(char *perms, mode_t mode)
{
	if (mode & S_IRGRP)
		perms[4] = 'r';
	else
		perms[4] = '-';
	if (mode & S_IWGRP)
		perms[5] = 'w';
	else
		perms[5] = '-';
	if (mode & S_IXGRP)
		perms[6] = 'x';
	else
		perms[6] = '-';
}

static void	set_other_perms(char *perms, mode_t mode)
{
	if (mode & S_IROTH)
		perms[7] = 'r';
	else
		perms[7] = '-';
	if (mode & S_IWOTH)
		perms[8] = 'w';
	else
		perms[8] = '-';
	if (mode & S_IXOTH)
		perms[9] = 'x';
	else
		perms[9] = '-';
}

char	*format_permissions(mode_t mode)
{
	char	*perms;

	perms = malloc(11);
	if (!perms)
		return (NULL);
	set_file_type(perms, mode);
	set_owner_perms(perms, mode);
	set_group_perms(perms, mode);
	set_other_perms(perms, mode);
	perms[10] = '\0';
	return (perms);
}
