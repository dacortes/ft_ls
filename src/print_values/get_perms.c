/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_perms.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 13:13:27 by dacortes          #+#    #+#             */
/*   Updated: 2025/07/03 18:04:46 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_values.h"
#include "errors.h"

/**
 * get_type_file - Sets the file type character in the permissions string.
 * @mode: The file mode (typically st_mode from struct stat) indicating file 
 * 	type and permissions.
 * @perms: A character array where the first character will be set to represent
 * 	the file type.
 *
 * This function examines the file mode and sets perms[0] to a character
 * representing the file type, similar to the first character
 * in the output of 'ls -l':
 *   'd' for directory,
 *   'l' for symbolic link,
 *   'c' for character device,
 *   'b' for block device,
 *   'p' for FIFO (named pipe),
 *   's' for socket,
 *   '-' for regular file or unknown type.
 */
void	get_type_file(unsigned int mode, char *perms)
{
	if (S_ISDIR(mode))
		perms[0] = 'd';
	else if (S_ISLNK(mode))
		perms[0] = 'l';
	else if (S_ISCHR(mode))
		perms[0] = 'c';
	else if (S_ISBLK(mode))
		perms[0] = 'b';
	else if (S_ISFIFO(mode))
		perms[0] = 'p';
	else if (S_ISSOCK(mode))
		perms[0] = 's';
	else
		perms[0] = '-';
}

/**
 * @brief Sets the user permission characters in a permissions string.
 *
 * This function updates the `perms` array to reflect the read, write, 
 * and execute permissions for the user (owner) based on the provided 
 * `mode` (typically from a stat struct).
 * It handles special cases such as set-user-ID (SUID) bits.
 *
 * @param mode  The file mode bits (e.g., from struct stat.st_mode).
 * @param perms The permissions string to update. The function
 * 	sets perms[1], perms[2], and perms[3]
 * 	to represent user read, write, and execute (or SUID)
 * 	permissions, respectively.
 */
void	get_permissions_user(unsigned int mode, char *perms)
{
	perms[1] = "-r"[!!(mode & S_IRUSR)];
	perms[2] = "-w"[!!(mode & S_IWUSR)];
	perms[3] = "-xSs"[((!!(mode & S_ISUID)) << 1) | (!!(mode & S_IXUSR))];
}

/**
 * Sets the group permission characters in the provided permission string.
 *
 * @param mode  The file mode (permission bits) to check.
 * @param perms The permission string to modify. The group permission
 *              characters will be set at positions 4, 5, and 6:
 *              - perms[4]: 'r' if group has read permission, '-' otherwise.
 *              - perms[5]: 'w' if group has write permission, '-' otherwise.
 *              - perms[6]: 'x' if group has execute permission,
 *                           's' if set-group-ID is set and execute is set,
 *                           'S' if set-group-ID is set and execute is not set,
 *                           '-' otherwise.
 */
void	get_permissions_group(unsigned int mode, char *perms)
{
	perms[4] = "-r"[!!(mode & S_IRGRP)];
	perms[5] = "-w"[!!(mode & S_IWGRP)];
	perms[6] = "-xSs"[((!!(mode & S_ISGID)) << 1) | (!!(mode & S_IXGRP))];
}

/**
 * get_permissions_other - Sets the permission characters for "other"
 * users in a permission string.
 * @mode: The file mode (typically from stat.st_mode) containing permission
 * 	bits.
 * @perms: A character array where the permission characters will be set.
 *
 * This function fills the positions 7, 8, and 9 of the perms array with the
 * appropriate characters representing the read, write, and execute permissions
 * for "other" (world) users. It also handles the sticky bit (S_ISVTX) for the
 * execute position, using 'T' or 't' as appropriate.
 *
 * perms[7]: 'r' if S_IROTH is set, '-' otherwise.
 * perms[8]: 'w' if S_IWOTH is set, '-' otherwise.
 * perms[9]: 'x' if S_IXOTH is set, 't' if sticky bit and execute are set,
 *           'T' if sticky bit is set but execute is not, '-' otherwise.
 */
void	get_permissions_other(unsigned int mode, char *perms)
{
	perms[7] = "-r"[!!(mode & S_IROTH)];
	perms[8] = "-w"[!!(mode & S_IWOTH)];
	perms[9] = "-xTt"[((!!(mode & S_ISVTX)) << 1) | (!!(mode & S_IXOTH))];
}

/**
 * get_format_perms - Generates a string representation of file permissions.
 * @mode: The file mode (typically from a stat struct) containing type
 * 	and permission bits.
 *
 * This function fills a static character array with the file type and
 * permission bits (user, group, other) in a format similar to that used
 * by the 'ls -l' command.
 * It calls helper functions to set the file type and permissions in the array.
 * The resulting string is duplicated and protected before being returned.
 *
 * Return: A dynamically allocated string representing the file's permissions.
 *         The caller is responsible for freeing the returned string.
 */
char	*get_format_perms(unsigned int mode)
{
	static char	perms[10];

	get_type_file(mode, perms);
	get_permissions_user(mode, perms);
	get_permissions_group(mode, perms);
	get_permissions_other(mode, perms);
	return (protected_memory(ft_strdup(perms), "get_format_perms"));
}
