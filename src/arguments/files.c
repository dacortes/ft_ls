/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 11:02:55 by dacortes          #+#    #+#             */
/*   Updated: 2025/05/18 17:03:57 by dacortes         ###   ########.fr       */
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
static int	get_size_files(char **args)
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

/**
 * add_array_files - Copies non-flag strings from the source array 
 * to the destination array.
 *
 * @src: A null-terminated array of strings to be processed.
 * @dst: A null-terminated array of strings where non-flag strings
 * will be copied.
 *
 * This function iterates through the `src` array and checks each
 * string to determine if it is a flag using the `is_flag` function.
 * If the string is not a flag, it is duplicated using `ft_strdup`
 * and added to the `dst` array. The function stops processing when
 * it encounters a null pointer in the `src` array.
 *
 * Return:
 * - EXIT_SUCCESS (0) if the operation completes successfully.
 * - EXIT_FAILURE (1) if either `src` or `dst` is NULL.
 */
static short	add_array_files(char **src, char **dst)
{
	int		iter;
	int		add;

	if (!src || !dst)
		return (EXIT_FAILURE);
	add = 0;
	iter = 0;
	while (src[iter])
	{
		if (is_flag(src[iter]) == false)
		{
			dst[add] = ft_strdup(src[iter]);
			add++;
		}
		iter++;
	}
	return (EXIT_SUCCESS);
}

/**
 * is_file - Filters and processes file arguments from a given array.
 *
 * @args: A null-terminated array of strings representing arguments.
 *        This array is expected to contain file paths or other data.
 *
 * Return: A dynamically allocated null-terminated array of strings
 *         containing only the file arguments, sorted in a specific order.
 *         Returns NULL if @args is NULL, memory allocation fails, or
 *         if the processing fails.
 *
 * Description:
 * - This function first determines the number of valid file arguments
 *   using the `get_size_files` function.
 * - It allocates memory for the resulting array of file arguments.
 * - If memory allocation fails, the program exits with an error message.
 * - The function populates the allocated array with file arguments
 *   using the `add_array_files` function.
 * - If the population fails, the function returns NULL.
 * - Finally, the array of file arguments is sorted using the `sort_files`
 *   function before being returned.
 *
 * Note:
 * - The caller is responsible for freeing the returned array and its
 *   contents to avoid memory leaks.
 * - The function may terminate the program if memory allocation fails.
 */
char	**is_file(char **args)
{
	char	**files;
	int		sizes;

	if (!args)
		return (NULL);
	sizes = get_size_files(args);
	files = ft_calloc(sizes + 1, sizeof(char *));
	if (!files)
		exit(error_msg(MALLOC, 1, "func: isfile() -> var: files", ""));
	if (add_array_files(args, files) == EXIT_FAILURE)
		return (NULL);
	sort_files(files, sizes);
	return (files);
}
