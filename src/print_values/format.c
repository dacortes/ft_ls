/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 13:13:27 by dacortes          #+#    #+#             */
/*   Updated: 2025/06/22 13:43:54 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_values.h"

void	get_type_file(unsigned int mode, char *perms)
{
	if (S_ISDIR(mode))
		perms[0] = 'd';
	else if (S_ISLNK(mode))
		perms[0] = 'l';
	else if (S_ISCHR(mode))
		perms[0] = 'c';
	else if (S_ISBLK(mode))
		perms[0] = 'b';
	else if (S_ISFIFO(mode))
		perms[0] = 'p';
	else if (S_ISSOCK(mode))
		perms[0] = 's';
	else
		perms[0] = '-';
}

void	get_permissions_user(unsigned int mode, char *perms)
{
	perms[1] = "-r"[!!(mode & S_IRUSR)];
	perms[2] = "-w"[!!(mode & S_IWUSR)];
	perms[3] = "-xSs"[((!!(mode & S_ISUID)) << 1) | (!!(mode & S_IXUSR))];
}

void	get_permissions_group(unsigned int mode, char *perms)
{
	perms[4] = "-r"[!!(mode & S_IRGRP)];
	perms[5] = "-w"[!!(mode & S_IWGRP)];
	perms[6] = "-xSs"[((!!(mode & S_ISGID)) << 1) | (!!(mode & S_IXGRP))];
}

void	get_permissions_other(unsigned int mode, char *perms)
{
	perms[7] = "-r"[!!(mode & S_IROTH)];
	perms[8] = "-w"[!!(mode & S_IWOTH)];
	perms[9] = "-xTt"[((!!(mode & S_ISVTX)) << 1) | (!!(mode & S_IXOTH))];
}

char	*get_format(unsigned int mode)
{
	static char	perms[10];

	get_type_file(mode, perms);
	get_permissions_user(mode, perms);
	get_permissions_group(mode, perms);
	get_permissions_other(mode, perms);
	ft_printf("*%s*\n", perms);
	return (perms);
}
