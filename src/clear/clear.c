/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 10:51:36 by dacortes          #+#    #+#             */
/*   Updated: 2025/07/01 13:06:46 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clear.h"

short	clear_array(char **ptr)
{
	int	iter;

	if (!ptr || !*ptr)
		return (false);
	iter = 0;
	while (ptr[iter])
	{
		free(ptr[iter]);
		ptr[iter] = NULL;
		iter++;
	}
	free(ptr);
	return (true);
}

short	clear_entries(struct dirent **entries, int size, short is_loop)
{
	int	iter;

	if (!entries || !*entries)
		return (false);
	iter = 0;
	while (iter < size)
	{
		free(entries[iter]);
		entries[iter] = NULL;
		iter++;
	}
	if (is_loop == false)
		free(entries);
	return (true);
}

short	clear_line(t_line *line)
{
	if (!line)
		return (false);
	free(line->permissions);
	free(line->num_links);
	free(line->owner);
	free(line->group);
	free(line->bytes);
	free(line->date);
	free(line->name);
	free(line->line);
	return (true);
}
