/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:06:34 by dacortes          #+#    #+#             */
/*   Updated: 2025/07/04 06:40:03 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clear.h"
#include "errors.h"
#include "print_values.h"

/**
 * @brief Appends a date string followed by a space to the buffer pointed 
 * 	by cursor.
 *
 * This function copies the given date string to the location pointed
 * to by *cursor, advances the cursor by the length of the date, and
 * appends a space character.
 *
 * @param cursor A pointer to a char pointer representing the current
 * position in the buffer.
 *               After the function call, *cursor will point to the 
 * 				 position after the appended space.
 * @param date   The date string to append to the buffer.
 */
void	add_date(char **cursor, char *date)
{
	ft_strcpy(*cursor, date);
	*cursor += ft_strlen(date);
	*(*cursor)++ = ' ';
}

void	add_link_target(char **cursor, char *name, char *link_target)
{
	if (!link_target)
		return ;
	*cursor += ft_strlen(name);
	*(*cursor)++ = ' ';
	ft_strcpy(*cursor, link_target);
}

/**
 * @brief Creates a formatted line representing file information for display.
 *
 * This function allocates and constructs a formatted string containing file
 * metadata such as permissions, number of links, owner, group, size in bytes,
 * date, and file name. The resulting string is stored in the `line->line`
 * member and printed using `print_line`.
 *
 * @param line Pointer to a t_line structure containing file information and
 *             where the resulting formatted line will be stored.
 * @param size Structure containing maximum field widths for alignment.
 *
 * @note The function does nothing if `line` is NULL or if `size.max_line`
 * 	is zero.
 * @note Memory for the formatted line is allocated using `protected_memory` and
 *       must be managed appropriately.
 */
void	create_line(t_line *line, t_size size)
{
	size_t	offset;
	char	*cursor;
	size_t	len_link;

	if (!check_struct_line(line) || !size.max_line)
		return ;
	len_link = 0;
	if (line->link_target)
		len_link = ft_strlen(line->link_target) + 1;
	line->line = protected_memory(ft_calloc(size.max_line + 9 + len_link, \
		sizeof(char)), "create_line");
	cursor = line->line;
	add_permissions(&cursor, line->permissions);
	offset = size.max_links;
	add_links(&cursor, line->num_links, offset);
	offset = size.max_owner;
	add_owner(&cursor, line->owner, offset);
	offset = size.max_group;
	add_group(&cursor, line->group, offset);
	offset = size.max_bytes;
	add_bytes(&cursor, line->bytes, offset);
	add_date(&cursor, line->date);
	ft_strcpy(cursor, line->name);
	add_link_target(&cursor, line->name, line->link_target);
	print_line(line->line, "", size.max_line + 8 + len_link);
}

/**
 * handle_line_long_format - Processes and formats an array of 
 * t_line structures based on flags.
 * @flags:     Structure containing formatting flags, including
 * long_format.
 * @line:      Double pointer to an array of t_line structures 
 * to be processed.
 * @limit:     Number of elements in the line array.
 *
 * If the long_format flag is set in @flags, this function calculates 
 * the maximum field widths for formatting, formats each line accordingly,
 * and clears each line.
 * If memory allocation fails during clearing, the program exits with an 
 * error message.
 * After processing, the function frees the memory allocated
 * for the line array and sets the pointer to NULL.
 */
short	handle_line_long_format(t_flags flags, t_line **line, int limit)
{
	t_size	size;
	int		iter;

	if (flags.long_format == false)
		return (EXIT_SUCCESS);
	iter = 0;
	ft_bzero(&size, sizeof(size));
	while (iter < limit)
	{
		update_max_lengths(&(*line)[iter], &size);
		iter++;
	}
	iter = 0;
	while (iter < limit)
	{
		create_line(&(*line)[iter], size);
		clear_line(&(*line)[iter]);
		iter++;
	}
	return (EXIT_SUCCESS);
}

void	ignore_hidden_files(t_flags flags, t_line **line, int *iter)
{
	while (!flags.all && (*line)[*iter].name && (*line)[*iter].name[0] == '.')
	{
		free((*line)[*iter].name);
		(*iter)++;
	}
}

short	handle_line_basic(t_flags flags, t_line **line, int limit)
{
	char	*tmp;
	char	*str;
	int		iter;

	if (flags.long_format == true)
		return (EXIT_SUCCESS);
	iter = 0;
	while (iter < limit && !(*line)[iter].name)
		++iter;
	if (!(*line)[iter].name)
		return (EXIT_SUCCESS);
	ignore_hidden_files(flags, line, &iter);
	str = ft_strdup((*line)[iter].name);
	while (iter < limit)
	{
		if ((*line)[iter + 1].name)
		{
			ignore_hidden_files(flags, line, &iter);
			tmp = ft_strjoin(str, "  ");
			free(str);
			ignore_hidden_files(flags, line, &iter);
			str = ft_strjoin(tmp, (*line)[iter + 1].name);
			free(tmp);
		}
		free((*line)[iter].name);
		++iter;
	}
	print_line(str, "", ft_strlen(str));
	return (free(str), EXIT_SUCCESS);
}

short	handle_line(t_flags flags, t_line **line, int limit)
{
	handle_line_long_format(flags, line, limit);
	handle_line_basic(flags, line, limit);
	if (line && *line)
		free(*line);
	*line = NULL;
	return (EXIT_SUCCESS);
}