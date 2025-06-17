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

void	print_entries(struct dirent	**entries, int size)
{
	int	iter;

	if (!size || !entries || !*entries)
	{
		ft_printf(WARNING_POINTER, YELLOW, END, \
			"print_entries", "files");
		return ;
	}
	iter = 0;
	while(iter < size)
	{
		ft_printf("%sentires%s[%d] %s\n", BLUE, END, iter, entries[iter]->d_name);
		iter++;
	}
}

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
			char *full_path = create_full_path(curr->entry->d_name, entries[i]->d_name);
			if (entries[i]->d_type == DT_DIR)
			{
				add = ft_calloc(1, sizeof(t_node));
				if (!add)
					exit(error_msg(MALLOC, 1, "loop_recursive", ""));
				add->entry = ft_calloc(1, sizeof(struct dirent) + ft_strlen(full_path) + 1);
                ft_strcpy(add->entry->d_name, full_path);
				push_stack(stack, add);
				// ft_printf("Added directory to stack: %s\n", entries[i]->d_name);
			}
			if (full_path)
				free(full_path);
			i--;
		}
		clear_entries(entries, entry_count, true);
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

struct dirent	**curr_directory(t_flags flags, char *name, int *entry_count)
{
	struct dirent	**entries;
	DIR				*dir;

	(void)flags;
	dir = init_dir(name);
	if (!dir)
		return (NULL);
	entries = NULL;
	*entry_count = read_dir_entries(dir, &entries);
	return (entries);
}

int main(int ac, char **av)
{
	struct dirent	**files;
	t_flags			flags;
	int				size_files;
	
	files = NULL;
	size_files = 0;
	if (has_flags(&flags, ac, &av[1]) == false && ac == 1)
	{
		ft_printf("enlisto sin flags en el directorio actual\n");
		// files = 
		files = curr_directory(flags, "./", &size_files);
	}
	else
	{
		//hay que tener encuenta si son argumentos listados como parametro de entrada 
		//si es asi este debe mostrar primero los archivos regurares organizados por el tiempo
		size_files = get_size_files(&av[1]);
		files = is_file(flags, &av[1], size_files);
	}
	if (!files)
		return (0);
	print_entries(files, size_files);
	// exec_recursive_flag(flags, files[0]->d_name);
	clear_entries(files, size_files, false);
	return (EXIT_SUCCESS);
}
