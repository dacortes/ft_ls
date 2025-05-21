/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 09:52:46 by dacortes          #+#    #+#             */
/*   Updated: 2025/05/21 16:02:11 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "node.h"

void	copy_struct_dirent(struct dirent	*origin, struct dirent	**copy)
{
	if (!origin)
		return ;
	*copy = ft_calloc(sizeof(struct dirent) + ft_strlen(origin->d_name) + 1, 1);
	if (!copy)
		exit(error_msg(1, MALLOC, "copy_dirent", ""));
	ft_memcpy(*copy, origin, sizeof(struct dirent));
	ft_strcpy((*copy)->d_name, origin->d_name);
}

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

short	default_directories(char *name_file, unsigned char type)
{
	return (type == DT_DIR && (!ft_strncmp(name_file, ".", -1)
		|| !ft_strncmp(name_file, "..", -1)));
}

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
