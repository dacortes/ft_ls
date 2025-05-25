/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 09:52:46 by dacortes          #+#    #+#             */
/*   Updated: 2025/05/25 17:41:28 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "node.h"

/**
 * @brief Copies the contents of a struct dirent, including its name, into a 
 * newly allocated struct.
 *
 * This function creates a deep copy of the given `struct dirent` object.
 * It allocates memory for the new struct, including space for the `d_name`
 * field, and copies all data from the original struct to the new one.
 *
 * @param origin Pointer to the original `struct dirent` to be copied. 
 * 				If this is NULL, the function will return without performing
 * 				any operation.
 * @param copy Pointer to a pointer where the newly allocated and copied
 * 				`struct dirent` will be stored. If memory allocation fails,
 * 				the program will exit with an error message.
 *
 * @note The caller is responsible for freeing the memory allocated for the
 * 				copied struct.
 * @note If `origin` is NULL, no memory allocation or copying will occur.
 *
 * @warning If memory allocation fails, the program will terminate with
 * 				an error message.
 */
void	copy_struct_dirent(struct dirent *origin, struct dirent **copy)
{
	if (!origin)
		return ;
	*copy = ft_calloc(sizeof(struct dirent) + ft_strlen(origin->d_name) + 1, 1);
	if (!copy)
		exit(error_msg(1, MALLOC, "copy_dirent", ""));
	ft_memcpy(*copy, origin, sizeof(struct dirent));
	ft_strcpy((*copy)->d_name, origin->d_name);
}

/**
 * @brief Initializes the `t_node` structure with directory entry data.
 *
 * This function attempts to open a directory specified by the `file`
 * parameter, reads the first directory entry, and copies its data into the
 * `t_node` structure.
 *
 * @param node A double pointer to a `t_node` structure. Must not be NULL or
 * 				point to NULL.
 * @param dir A pointer to a `DIR` structure. Used to open the directory.
 * @param file A string representing the path to the directory to be opened.
 *
 * @return 
 * - `EXIT_SUCCESS` (0) if the operation is successful.
 * - Prints a warning and returns `EXIT_SUCCESS` if `node` or `*node` is NULL.
 * - Frees `*node` and returns an error message if the directory
 * 				cannot be opened.
 * - Closes the directory and returns `end_dir` if no entries are found.
 *
 * @note The function uses `opendir` to open the directory and `readdir` to read
 * the first entry. It also ensures proper cleanup by closing the directory
 * handle (`closedir`) in case of errors or after successful processing.
 */
short	init_struct_dirent(t_node **node, DIR *dir, char *file)
{
	struct dirent	*entry;

	if (!node || !*node)
		return (ft_printf(WARNING_POINTER, YELLOW, END, \
			"init_struct_dirent", "node"), EXIT_SUCCESS);
	dir = opendir(file);
	if (!dir)
		return (free(*node), error_msg(OPEN_DIR, 2, file, strerror(errno)));
	entry = readdir(dir);
	if (entry == NULL)
		return (closedir(dir), end_dir);
	copy_struct_dirent(entry, &(*node)->entry);
	closedir(dir);
	return (EXIT_SUCCESS);
}

/**
 * @brief Checks if a given file is a default directory (i.e., "." or "..").
 *
 * @param name_file The name of the file to check.
 * @param type The type of the file, typically obtained from directory
 * 			   entry metadata.
 *             This is expected to be compared against DT_DIR to determine if
 * 			   it is a directory.
 * @return A short integer:
 *         - 1 (true) if the file is a directory and its name is "." or "..".
 *         - 0 (false) otherwise.
 */
short	default_directories(char *name_file, unsigned char type)
{
	return (type == DT_DIR && (!ft_strncmp(name_file, ".", -1) \
		|| !ft_strncmp(name_file, "..", -1)));
}

/**
 * is_directory - Determines the type of a file or directory at a given path.
 * 
 * @node: A double pointer to a t_node structure where file metadata
 * will be stored.
 * @path: A string representing the path to the file or directory to check.
 * 
 * This function uses lstat to retrieve metadata about the file or directory
 * at the specified path and stores it in the `st` field of the t_nod
 * structure.
 * It then checks the file type using macros from <sys/stat.h>:
 * 
 * - If the file is a symbolic link, it returns `dir_link`.
 * - If the file is a directory, it returns `dir`.
 * - Otherwise, it returns `file`.
 * 
 * If lstat fails, an error message is printed using error_msg, and the function
 * returns an error code.
 * 
 * Return:
 * - `dir_link` if the path is a symbolic link.
 * - `dir` if the path is a directory.
 * - `file` if the path is a regular file or another type.
 * - An error code if lstat fails.
 */
int	is_directory(t_node **node, char *path)
{
	if (lstat(path, &(*node)->st) == ERROR)
		return (error_msg(OPEN_DIR, 2, path, strerror(errno)));
	if (S_ISLNK((*node)->st.st_mode))
		return (dir_link);
	else if (S_ISDIR((*node)->st.st_mode))
		return (dir);
	return (file);
}
