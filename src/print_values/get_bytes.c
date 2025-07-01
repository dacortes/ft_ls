/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bytes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 11:54:48 by dacortes          #+#    #+#             */
/*   Updated: 2025/07/01 12:11:01 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_values.h"
#include "errors.h"

/**
 * get_bytes - Converts a file size to a string representation.
 * @st_size: The file size in bytes (as a long long integer).
 *
 * This function converts the given file size to a string using ft_ltoa,
 * and wraps the result with protected_memory for memory safety.
 *
 * Returns: A pointer to the newly allocated string representing the file size.
 *          The caller is responsible for freeing the returned string if needed.
 */
char	*get_bytes(long long st_size)
{
	return (protected_memory(ft_ltoa(st_size), "get_bytes"));
}
