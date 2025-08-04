/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 11:04:20 by dacortes          #+#    #+#             */
/*   Updated: 2025/08/04 11:17:49 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"
#include "errors.h"
#include "arguments.h"

int	get_regular_files_number(struct dirent **files, int sizes)
{
	struct stat	st;
	int			count;
	int			iter;

	iter = 0;
	count = 0;
	while (iter < sizes)
	{
		if (lstat(files[iter]->d_name, &st) == -1)
		{
			error_msg(OPEN_DIR, 2, files[iter]->d_name, strerror(errno));
			++iter;
			continue ;
		}
		if (!S_ISDIR(st.st_mode))
			++count;
		++iter;
	}
	return (count);
}

void	get_regular(t_flags flags, struct dirent **fls, int sizes, t_line **ln)
{
	struct stat	st;
	int			iter;
	int			add;

	iter = 0;
	add = 0;
	while (iter < sizes)
	{
		if (lstat(fls[iter]->d_name, &st) == -1)
			continue ;
		if (!S_ISDIR(st.st_mode))
		{
			get_format(flags, fls[iter]->d_name, fls[iter]->d_name, \
				&(*ln)[add]);
			++add;
		}
		++iter;
	}
}
