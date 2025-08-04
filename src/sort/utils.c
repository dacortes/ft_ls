/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:27:33 by dacortes          #+#    #+#             */
/*   Updated: 2025/08/04 13:44:42 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"
#include "clear.h"
#include "errors.h"
#include "print_values.h"

void	has_flag_all(t_flags flags, char *curr_root_dir, char *curr_dir, \
	t_line *add)
{
	char	*full_path;

	if (flags.all == false)
		return ;
	full_path = create_full_path(curr_root_dir, curr_dir);
	get_format(flags, full_path, curr_dir, add);
	if (full_path)
	{
		free(full_path);
		full_path = NULL;
	}
}

int	ignore_current_dir(t_flags flags, struct dirent **files, int *i)
{
	if (!flags.all && files[*i]->d_name[0] == '.')
	{
		++(*i);
		return (true);
	}
	return (false);
}

int	select_state(t_flags flags, t_node **curr, struct stat *st, DIR **dir)
{
	if (flags.args == true && lstat((*curr)->entry->d_name, st) == -1)
	{
		free((*curr)->entry);
		free((*curr));
		return (true);
	}
	if (flags.args == true && !S_ISDIR(st->st_mode))
	{
		free((*curr)->entry);
		free((*curr));
		return (true);
	}
	if (S_ISDIR(st->st_mode))
		print_line((*curr)->entry->d_name, ":", \
			ft_strlen((*curr)->entry->d_name));
	*dir = init_dir((*curr)->entry->d_name);
	if (!*dir)
	{
		free((*curr)->entry);
		free((*curr));
		return (true);
	}
	return (false);
}
