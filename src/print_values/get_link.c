/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_link.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 10:15:41 by dacortes          #+#    #+#             */
/*   Updated: 2025/07/03 10:52:50 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_values.h"
#include "errors.h"

/**
 * get_link - Retrieves the target of a symbolic link as a formatted string.
 * @mode: The file mode (typically from stat), used to check if the file is 
 * 	a symlink.
 * @full_path: The full path to the file to check and read if it is a symlink.
 *
 * If the file specified by @full_path is a symbolic link, this function reads 
 * the link's target and returns a newly allocated string in the 
 * format "-> target".
 * If the file is not a symbolic link or an error occurs, NULL is returned.
 *
 * The returned string is allocated using protected_memory and must be 
 * freed by the caller.
 *
 * Return: A pointer to the formatted string on success, or NULL on failure.
 */
char	*get_link(unsigned int mode, char *full_path)
{
	char	target[PATH_MAX];
	ssize_t	len;

	if (!S_ISLNK(mode))
		return (NULL);
	len = readlink(full_path, target, sizeof(target) - 1);
	if (len == ERROR)
		return (NULL);
	target[len] = '\0';
	return (protected_memory(ft_strjoin("-> ", target), "get_link"));
}
