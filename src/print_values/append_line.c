/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:09:52 by dacortes          #+#    #+#             */
/*   Updated: 2025/07/01 15:40:34 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clear.h"
#include "errors.h"
#include "print_values.h"

/**
 * Adds a string of permissions to the buffer pointed to by `cursor`,
 * advances the cursor past the copied permissions, and appends a space.
 *
 * @param cursor      A pointer to the current position in the output buffer.
 *                    After the function, it will point after the appended
 * 					  space.
 * @param permissions The string representing permissions to append.
 */
void	add_permissions(char **cursor, char *permissions)
{
	ft_strcpy(*cursor, permissions);
	*cursor += ft_strlen(permissions);
	*(*cursor)++ = ' ';
}

/**
 * @brief Appends the number of links to the output buffer with left padding 
 * 	and a trailing space.
 *
 * This function writes the string representation of the number 
 * of links (`num_links`) into the buffer pointed to by `*cursor`, 
 * left-padded with spaces to fit the specified `offset`. After writing,
 * it advances the `*cursor` pointer by `offset` and appends
 * a single space character.
 *
 * @param cursor   Pointer to the current position in the output buffer;
 * 	will be updated.
 * @param num_links String containing the number of links to append.
 * @param offset   Total width (including padding) to use 
 * 	for the number of links.
 */
void	add_links(char **cursor, char *num_links, size_t offset)
{
	fill_spaces_left(*cursor, num_links, offset);
	*cursor += offset;
	*(*cursor)++ = ' ';
}

/**
 * @brief Appends the owner's name to the current cursor position in a buffer,
 *        right-aligning it within a given offset and adding a trailing space.
 *
 * This function writes the owner's name into the buffer pointed to by *cursor,
 * right-aligned within the specified offset using fill_spaces_right.
 * After writing, it advances the cursor by the offset and appends a space
 * character.
 *
 * @param cursor  Double pointer to the current position in the buffer;
 * 	will be updated.
 * @param owner   The owner's name to append.
 * @param offset  The width to use for right-aligning the owner's name.
 */
void	add_owner(char **cursor, char *owner, size_t offset)
{
	fill_spaces_right(*cursor, owner, offset);
	*cursor += offset;
	*(*cursor)++ = ' ';
}

/**
 * @brief Appends a group name to the output buffer with right-aligned 
 * 	padding and a trailing space.
 *
 * This function writes the given group name into the buffer pointed to by 
 * `*cursor`, right-aligning it within a field of width `offset` by filling 
 * with spaces as needed.
 * After the group name, a single space character is appended.
 * The `*cursor` pointer
 * is advanced past the written field and the space.
 *
 * @param cursor Pointer to the current position in the output buffer;
 * 	updated after writing.
 * @param group  The group name string to append.
 * @param offset The total width of the field to fill (including padding).
 */
void	add_group(char **cursor, char *group, size_t offset)
{
	fill_spaces_right(*cursor, group, offset);
	*cursor += offset;
	*(*cursor)++ = ' ';
}

/**
 * @brief Appends a string of bytes to the cursor position in a buffer, 
 *        left-padding with spaces up to a specified offset, then adds a space.
 *
 * This function fills the space between the current cursor position and the
 * specified offset with spaces, copies the provided bytes string, advances
 * the cursor by the offset, and appends a single space character.
 *
 * @param cursor Pointer to the current position in the buffer 
 * 	(will be updated).
 * @param bytes  The string of bytes to append.
 * @param offset The total width to fill (including bytes and left-padding).
 */
void	add_bytes(char **cursor, char *bytes, size_t offset)
{
	fill_spaces_left(*cursor, bytes, offset);
	*cursor += offset;
	*(*cursor)++ = ' ';
}
