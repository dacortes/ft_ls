################################################################################
#                               BOLD COLORS                                    #
################################################################################

END = \033[m
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
PURPLE = \033[35m
CIAN = \033[36m

################################################################################
#  FONT                                                                        #
################################################################################

LIGTH = \033[1m
DARK = \033[2m
ITALIC = \033[3m

################################################################################
#                               VARIABLES                                      #
################################################################################

NAME = ft_ls
CC = gcc
RMV = rm -rf
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address # -O3

TOTAL_FILES = $(words $(SOURCES))

DIRECTORY_OBJ = .obj
DIRECTORY_DEP = .dep
DIRECTORY_SRC = src

SUB_DIRECTORIES = arguments clear errors node print_values sort
SOURCES = \
	arguments/entries.c arguments/files.c arguments/flag.c \
	clear/clear.c \
	errors/memory_error.c errors/print_errors.c \
	print_values/append_line.c print_values/create_line.c \
	print_values/get_bytes.c print_values/get_date.c \
	print_values/get_group.c print_values/get_link.c \
	print_values/get_name.c print_values/get_num_link.c \
	print_values/get_owner.c print_values/get_perms.c \
	print_values/print_files.c print_values/print_flags.c \
	print_values/utils.c \
	node/clear.c node/handler_nodes.c node/handler_data.c \
	sort/directory.c sort/quicksort.c sort/recursive.c sort/sort_files.c \
	main.c

INCLUDES = $(addprefix -I, ./include)
OBJECTS = $(addprefix $(DIRECTORY_OBJ)/, $(SOURCES:.c=.o))
DEPENDENCIES = $(addprefix $(DIRECTORY_DEP)/, $(SOURCES:.c=.d))

LIBFT = ./lib/libft/
LIBFT_A = $(LIBFT)libft.a
INCLUDES += -I$(LIBFT)

################################################################################
#                               MAKE RULES                                     #
################################################################################

DIRS_TO_CREATE = $(DIRECTORY_OBJ) $(DIRECTORY_DEP)
all: libft libs dir $(NAME)

libft:
	@if [ ! -d "./lib/libft/.git" ]; then \
        git clone git@github.com:dacortes/libft.git ./lib/libft; \
        git submodule update --init --recursive; \
    elif [ -d "./lib/libft/.git" ]; then \
        echo "$(YELLOW)$(LIGTH)[ Warnig ]$(END) libft: already exists and is a valid git repository."; \
    else \
        echo "$(YELLOW)$(LIGTH)[ Warnig ]$(END) libft: already exists and is not an empty directory."; \
    fi

libs:
	make bonus -C $(LIBFT) --no-print-directory

libsclean:
	make -C $(LIBFT) clean --no-print-directory

libsfclean:
	make -C $(LIBFT) fclean --no-print-directory

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJECTS) $(LIBFT_A) -o $(NAME)
	@echo "\n✅ ==== $(BLUE)$(LIGTH)Project $(NAME) compiled!$(END) ==== ✅"

$(DIRECTORY_OBJ)/%.o:$(DIRECTORY_SRC)/%.c Makefile
	@printf "  $(LIGTH)Compiling $(BLUE)$<$(END)      "
	@$(CC) $(CFLAGS) $(INCLUDES) -MMD -MF $(DIRECTORY_DEP)/$*.d -c $< -o $@
	@$(call progress,$<)

dir:
	@for DIR in $(DIRS_TO_CREATE); do \
		if [ ! -d $$DIR ]; then \
			mkdir -p $$DIR; \
			$(foreach SUB, $(SUB_DIRECTORIES), mkdir -p $$DIR/$(SUB);) \
			printf "$(BLUE)$(LIGTH)Creating directory:$(END) $$DIR\n"; \
		else \
			printf "$(BLUE)$(LIGTH)Directory already exists:$(END) $$DIR\n"; \
		fi \
	done

clean: libsclean
	@for DIR in $(DIRS_TO_CREATE); do \
		if [ -d $$DIR ]; then \
			$(RMV) $$DIR; \
			printf "$(BLUE)$(LIGTH)Directory$(END) $$DIR $(BLUE)$(LIGTH)removed$(END)\n"; \
		else \
			printf "$(LIGTH)The directory does not exist:$(END) $$DIR\n"; \
		fi \
	done
	echo "✅ ==== $(PURPLE)$(LIGTH)$(NAME) object files cleaned!$(END) ==== ✅"

fclean: clean libsfclean
	$(RMV) $(NAME)
	echo "✅ ==== $(PURPLE)$(LIGTH)$(NAME) executable files and name cleaned!$(END) ==== ✅"

define progress
	@$(eval COMPILED_FILES=$(shell expr $(COMPILED_FILES) + 1))
	@bash -c 'PROG_BAR_WIDTH=50; \
	PROGRESS=$$(($(COMPILED_FILES) * $$PROG_BAR_WIDTH / $(TOTAL_FILES))); \
	EMPTY=$$(($$PROG_BAR_WIDTH - $$PROGRESS)); \
	PROGRESS=$$((PROGRESS < 0 ? 0 : PROGRESS)); \
	EMPTY=$$((EMPTY < 0 ? 0 : EMPTY)); \
	printf "\r$(ligth)[$(GREEN)"; \
	for ((i = 0; i < $$PROGRESS; i++)); do echo -n "█"; done; \
	for ((i = 0; i < $$EMPTY; i++)); do echo -n " "; done; \
	printf "$(END)$(ligth)] "; \
	printf "%d%%$(END)" $$((100 * $(COMPILED_FILES) / $(TOTAL_FILES)));'
endef

-include $(DEPENDENCIES)
re: fclean all
.PHONY: all clean progress fclean test dir libs libft
COMPILED_FILES=0
.SILENT:
