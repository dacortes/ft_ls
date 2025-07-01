/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_date.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 11:57:26 by dacortes          #+#    #+#             */
/*   Updated: 2025/07/01 12:12:31 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_values.h"
#include "errors.h"

/**
 * get_date - Returns a formatted date string from a given time value.
 * @mtime: Pointer to a time_t value representing the modification time.
 *
 * This function converts the given time value to a human-readable string
 * using ctime(), duplicates the string into protected memory, and removes
 * the trailing newline character. The resulting string must be freed by
 * the caller if protected_memory allocates memory dynamically.
 *
 * Return: A pointer to the formatted date string, or NULL on failure.
 */
char	*get_date(time_t *mtime)
{
	size_t	len;
	char	*str;

	str = protected_memory(ft_strdup(ctime(mtime)), "get_date");
	len = ft_strlen(str);
	if (len > 0)
		str[len - 1] = '\0';
	return (str);
}
