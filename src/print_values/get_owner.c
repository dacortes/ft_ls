/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_owner.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 11:40:01 by dacortes          #+#    #+#             */
/*   Updated: 2025/08/04 10:02:51 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_values.h"
#include "errors.h"

/**
 * get_owner - Retrieves the username associated with a given user ID (uid).
 * @uid: The user ID for which to obtain the username.
 *
 * This function uses the getpwuid() function to look up the passwd structure
 * corresponding to the provided uid. It then duplicates the username string
 * (pw_name) and wraps it with protected_memory for memory safety.
 *
 * Return: A pointer to a newly allocated string containing the username,
 *         or NULL if the user cannot be found or memory allocation fails.
 *         The caller is responsible for freeing the returned string.
 */
char	*get_owner(unsigned int uid)
{
	struct passwd	*pw;

	pw = getpwuid(uid);
	if (!pw || !pw->pw_name)
		return (NULL);
	return (protected_memory(ft_strdup(pw->pw_name), "get_user"));
}
