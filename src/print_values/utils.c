/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:15:29 by dacortes          #+#    #+#             */
/*   Updated: 2025/07/01 13:20:42 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_values.h"

/**
 * Updates the maximum lengths of various fields in the t_size structure
 * based on the lengths of the corresponding fields in the given
 * t_line structure.
 *
 * This function compares the length of each field in the provided 
 * t_line (such as num_links, owner, group, bytes, date, and name) 
 * with the current maximum stored in the t_size structure. If the current 
 * field's length is greater, it updates the maximum. It also recalculates
 * the total maximum line length.
 *
 * @param line Pointer to a t_line structure containing the current file's 
 * 	field values.
 * @param size Pointer to a t_size structure where maximum field 
 * 	lengths are tracked and updated.
 */
void	update_max_lengths(t_line *line, t_size *size)
{
	size_t	len;

	len = ft_strlen(line->num_links);
	if (len > size->max_links)
		size->max_links = len;
	len = ft_strlen(line->owner);
	if (len > size->max_owner)
		size->max_owner = len;
	len = ft_strlen(line->group);
	if (len > size->max_group)
		size->max_group = len;
	len = ft_strlen(line->bytes);
	if (len > size->max_bytes)
		size->max_bytes = len;
	len = ft_strlen(line->date);
	if (len > size->max_date)
		size->max_date = len;
	len = ft_strlen(line->name);
	if (len > size->max_name)
		size->max_name = len;
	size->max_line = size->max_links + size->max_owner + \
	size->max_group + size->max_bytes + size->max_date + size->max_name + 10;
}

/**
 * fill_spaces_right - Copies a string into a destination buffer and
 * pads it with spaces on the right.
 * @dest: The destination buffer where the result will be stored.
 * @str: The source string to copy.
 * @width: The total width of the resulting string, including padding.
 *
 * This function copies the string @str into @dest and fills the remaining space
 * up to @width with spaces. The resulting string in
 * @dest will be null-terminated.
 * If the length of @str is greater than or equal to @width,
 * no padding is added.
 */
void	fill_spaces_right(char *dest, char *str, size_t width)
{
	size_t	i;

	i = ft_strlen(str);
	ft_strcpy(dest, str);
	while (i < width)
		dest[i++] = ' ';
	dest[i] = '\0';
}

/**
 * @brief Fills the destination buffer with left-padded spaces and copies 
 *  the input string.
 *
 * This function copies the string `str` into the buffer `dest`, left-padding
 * it with spaces so that the total length is at least `width` characters.
 * If `str` is longer than or equal to `width`, no padding is added.
 *
 * @param dest   The destination buffer where the padded string will be written.
 * @param str    The input string to be copied and padded.
 * @param width  The minimum width of the resulting string (including padding).
 */
void	fill_spaces_left(char *dest, char *str, size_t width)
{
	size_t	len;
	size_t	padding;

	len = ft_strlen(str);
	if (width > len)
		padding = width - len;
	else
		padding = 0;
	ft_memset(dest, ' ', padding);
	ft_strcpy(dest + padding, str);
}
