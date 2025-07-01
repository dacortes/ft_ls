/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_name.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 12:07:19 by dacortes          #+#    #+#             */
/*   Updated: 2025/07/01 12:14:58 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_values.h"
#include "errors.h"

/**
 * @brief Returns a dynamically allocated copy of the given name string,
 *        with memory allocation protected by the protected_memory function.
 *
 * This function duplicates the input string 'name' using ft_strdup,
 * and then passes the result to protected_memory for error handling.
 *
 * @param name The input string to duplicate.
 * @return A pointer to the newly allocated string, or handles errors as defined
 *         by protected_memory.
 */
char	*get_name(char	*name)
{
	return (protected_memory(ft_strdup(name), "get_name"));
}
