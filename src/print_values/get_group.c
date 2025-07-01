/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_group.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 11:44:25 by dacortes          #+#    #+#             */
/*   Updated: 2025/07/01 12:13:50 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_values.h"
#include "errors.h"

/**
 * get_group - Retrieves the group name associated with a given group ID (gid).
 * @gid: The group ID for which to obtain the group name.
 *
 * This function uses the system's group database to find the group name
 * corresponding to the provided gid. It duplicates the group name string
 * and wraps it with protected_memory for safe memory handling.
 *
 * Return: A pointer to a newly allocated string containing the group name,
 *         or NULL if the group is not found or memory allocation fails.
 */
char	*get_group(unsigned int gid)
{
	struct group	*gr;

	gr = getgrgid(gid);
	return (protected_memory(ft_strdup(gr->gr_name), "get_group"));
}
