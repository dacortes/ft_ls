/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 11:02:55 by dacortes          #+#    #+#             */
/*   Updated: 2025/05/25 18:11:36 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"
#include "errors.h"
#include "arguments.h"

/**
 * get_size_files - Calculates the number of non-flag arguments in a list.
 * @args: A null-terminated array of strings representing the arguments.
 *
 * This function iterates through the provided array of arguments and counts
 * the number of elements that are not flags. Flags are determined by the
 * `is_flag` function, which returns `false` for non-flag arguments.
 *
 * Return: The count of non-flag arguments in the array.
 *         Returns -1 if the input array is NULL.
 */
int	get_size_files(char **args)
{
	int	iter;
	int	sizes;

	if (!args)
		return (-1);
	iter = 0;
	sizes = 0;
	while (args[iter])
	{
		if (is_flag(args[iter]) == false)
			sizes++;
		iter++;
	}
	return (sizes);
}

static short	add_array_files(char **src, struct dirent **dst)
{
	int	iter;
	int	add;

	if (!src || !dst)
		return (EXIT_FAILURE);
	add = 0;
	iter = 0;
	while (src[iter])
	{
		if (is_flag(src[iter]) == false)
		{
			dst[add] = ft_calloc(sizeof(struct dirent), 1);
			if (!dst[add])
				exit(error_msg(MALLOC, 1, "add_array_files", ""));
			ft_strcpy(dst[add]->d_name, src[iter]);
			add++;
		}
		iter++;
	}
	return (EXIT_SUCCESS);
}

struct dirent	**is_file(t_flags flags, char **args, int sizes)
{
	struct dirent	**entries;

	if (!sizes || sizes < 0)
		return (NULL);
	entries = ft_calloc(sizes + 1, sizeof(struct dirent *));
	if (add_array_files(args, entries) == EXIT_FAILURE)
		return (NULL);
	sort_entries(entries, sizes, flags);
	return (entries);
}
