#include "clear.h"
#include "errors.h"
#include "arguments.h"
#include "print_values.h"
#include "sort.h"


/*
	◦ write
	◦ opendir
	◦ readdir
	◦ closedir
	◦ stat
	◦ lstat
	◦ getpwuid
	◦ getgrgid
	◦ listxattr
	◦ getxattr
	◦ time
	◦ ctime
	◦ readlink
	◦ malloc
	◦ free
	◦ perror
	◦ strerror
	◦ exit
*/

// #include "libft.h"
// #include "ft_printf.h"
// #include <errno.h>
#include <pwd.h>
#include <string.h>
#include <sys/stat.h>


DIR	*init_dir(char *file)
{
	DIR *dir;

	dir = opendir(file);
	if (!dir)
		return (error_msg(OPEN_DIR, 2, file, strerror(errno)), NULL);
	return (dir);
}

short	is_readdir(struct dirent **entry, DIR		*dir)
{
	*entry = readdir(dir);
	if (!*entry)
		return (false);
	return (true);
}

int	read_dir_entries(DIR *dir, struct  dirent ***entries)
{
	struct dirent	*entry;
	struct dirent	**tmp;
	int				i;

	i = 0;
	while (is_readdir(&entry, dir))
	{
		tmp = ft_realloc(*entries, sizeof(struct  dirent *) * i, sizeof(struct  dirent *) * (i + 1));
		if (!tmp)
			exit(error_msg(MALLOC, 1, "read_dir_entries", ""));
		*entries = tmp;
		// ft_printf("---*****%p\n", *entries);
		copy_struct_dirent(entry, &(*entries)[i]);
		i++;
	}
	return (i);
}

void	print_entries(struct dirent	**entries, int size)
{
	int	iter;

	iter = 0;
	while(iter < size)
	{
		ft_printf("%sentires%s[%d] %s\n", BLUE, END, iter, entries[iter]->d_name);
		iter++;
	}
}

// short	loop_recursive(t_flags flags, t_stack *stack)
// {
// 	struct dirent	**entries;
// 	t_node			*curr;
// 	t_node			*add;
// 	DIR				*dir;
// 	int				entry_count;
// 	int				i;

// 	(void)flags;
// 	entry_count = 0;
// 	entries = NULL;
// 	while (stack->size > 0)
// 	{
// 		curr = copy_node(stack, true);
// 		ft_printf("Exploring: %s\n", curr->entry->d_name);
// 		dir = init_dir(curr->entry->d_name);
// 		if (!dir)
// 			continue ;
// 		entry_count = read_dir_entries(dir, &entries);
// 		sort_entries(entries, entry_count, flags);
// 		// print_entries(entries, entry_count);
// 		i = 0;
// 		while (i < entry_count)
// 		{
// 			if (default_directories(entries[i]->d_name, entries[i]->d_type))
// 			{
// 				++i;
// 				continue;
// 			}
// 			char *tmp;
// 			int len = ft_strlen(curr->entry->d_name);
// 			if (curr->entry->d_name[len] != '/')
// 				tmp = ft_addend_char(curr->entry->d_name, '/');
// 			else
// 				tmp = ft_strdup(curr->entry->d_name);
// 			char *full_path = ft_strjoin(tmp, entries[i]->d_name);
// 			if (tmp)
// 				free(tmp);
// 			if (entries[i]->d_type == DT_DIR)
// 			{
// 				add = ft_calloc(1, sizeof(t_node));
// 				if (!add)
// 					exit(error_msg(MALLOC, 1, "loop_recursive", ""));
// 				add->entry = ft_calloc(1, sizeof(struct dirent) + strlen(full_path) + 1);
//                 ft_strcpy(add->entry->d_name, full_path);
// 				push_stack(stack, add);
// 				// ft_printf("Added directory to stack: %s\n", entries[i]->d_name);
// 			}
// 			else
// 			{
// 				// ft_printf("File: %s\n", entries[i]->d_name);
// 			}
// 			if (full_path)
// 				free(full_path);
// 			i++;
// 		}
// 		i = 0;
// 		while (i < entry_count)
// 		{
// 			free(entries[i]);
// 			i++;
// 		}
// 		closedir(dir);
// 		free(curr->entry);
// 		free(curr);
// 	}
// 	if (entries)
// 		free(entries);
// 	return (true);
// }

short	loop_recursive(t_flags flags, t_stack *stack)
{
	struct dirent	**entries;
	t_node			*curr;
	t_node			*add;
	DIR				*dir;
	int				entry_count;
	int				i;

	(void)flags;
	entry_count = 0;
	entries = NULL;
	while (stack->size > 0)
	{
		curr = copy_node(stack, true);
		ft_printf("Exploring: %s\n", curr->entry->d_name);
		dir = init_dir(curr->entry->d_name);
		if (!dir)
			continue ;
		entry_count = read_dir_entries(dir, &entries);
		sort_entries(entries, entry_count, flags);
		// print_entries(entries, entry_count);
		i = entry_count - 1;
		while (i >= 0)
		{
			if (default_directories(entries[i]->d_name, entries[i]->d_type))
			{
				--i;
				continue;
			}
			char *tmp;
			int len = ft_strlen(curr->entry->d_name);
			if (curr->entry->d_name[len] != '/')
				tmp = ft_addend_char(curr->entry->d_name, '/');
			else
				tmp = ft_strdup(curr->entry->d_name);
			char *full_path = ft_strjoin(tmp, entries[i]->d_name);
			if (tmp)
				free(tmp);
			if (entries[i]->d_type == DT_DIR)
			{
				add = ft_calloc(1, sizeof(t_node));
				if (!add)
					exit(error_msg(MALLOC, 1, "loop_recursive", ""));
				add->entry = ft_calloc(1, sizeof(struct dirent) + strlen(full_path) + 1);
                ft_strcpy(add->entry->d_name, full_path);
				push_stack(stack, add);
				// ft_printf("Added directory to stack: %s\n", entries[i]->d_name);
			}
			if (full_path)
				free(full_path);
			i--;
		}
		i = 0;
		while (i < entry_count)
		{
			free(entries[i]);
			i++;
		}
		closedir(dir);
		free(curr->entry);
		free(curr);
	}
	if (entries)
		free(entries);
	return (true);
}

short	exec_recursive_flag(t_flags flags, char *start_dir)
{
	t_stack	stack;
	t_node	*root;

	if (!start_dir)
		return (false);
	ft_bzero(&stack, sizeof(t_stack));
	root = ft_calloc(1, sizeof(t_node));
	if (!root)
		exit(error_msg(MALLOC, 1, "exec_recursive_flag", ""));
    root->entry = ft_calloc(1, sizeof(struct dirent) \
		+ ft_strlen(start_dir) + 1);
	if (!root)
		exit(error_msg(MALLOC, 1, "exec_recursive_flag", ""));
    ft_strcpy(root->entry->d_name, start_dir);
	push_stack(&stack, root);
	loop_recursive(flags, &stack);
	clear_stack(&stack);
	return (stack.status);
}

int main(int ac, char **av)
{
	t_flags flags;
	char	**files;
	
	files = NULL;
	if (has_flags(&flags, ac, &av[1]) == false && ac == 1)
		ft_printf("enlisto sin flags\n");
	else
		files = is_file(&av[1]);
	if (!files)
		return (0);

	exec_recursive_flag(flags, files[0]);
	print_array_files(files);
	clear_array(files);
	return (EXIT_SUCCESS);
}
