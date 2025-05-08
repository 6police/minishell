# Color codes
RED = \033[0;31m
GREEN = \033[0;32m
CYAN = \033[0;36m
YELLOW = \033[0;33m
BLUE = \033[0;34m
NOCOLOR = \033[0m

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Name of the library
NAME = libft.a

# Directories
SRC_DIR = .
OBJ_DIR = ./obj

# Gather all .c files
SRC_FILES = ft_printf.c\
			ft_aux.c\
			ft_nbrlen.c\
			ft_parse_data.c\
			ft_parse_wrapper.c\
			ft_atoi.c\
			ft_substr.c\
			ft_tolower.c\
			ft_strnstr.c\
			ft_strrchr.c\
			ft_strtrim.c\
			ft_strmapi.c\
			ft_strncmp.c\
			ft_strlcat.c\
			ft_strlcpy.c\
			ft_strlen.c\
			ft_lstdelone.c\
			ft_lstiter.c\
			ft_lstlast.c\
			ft_lstmap.c\
			ft_lstnew.c\
			ft_lstsize.c\
			ft_memchr.c\
			ft_memcmp.c\
			ft_memcpy.c\
			ft_memmove.c\
			ft_memset.c\
			ft_putchar_fd.c\
			ft_toupper.c\
			ft_putendl_fd.c\
			ft_putnbr_fd.c\
			ft_putstr_fd.c\
			ft_split.c\
			ft_strchr.c\
			ft_striteri.c\
			ft_strjoin.c\
			ft_isprint.c\
			ft_lstadd_back.c\
			ft_lstadd_front.c\
			ft_lstclear.c\
			ft_isalnum.c\
			ft_isalpha.c\
			ft_isascii.c\
			ft_isdigit.c\
			ft_calloc.c\
			ft_bzero.c\
			ft_print_u.c\
			ft_print_xx.c\
			ft_write_nbr.c\
			ft_atol.c\
			ft_print_percent.c\
			ft_write_str.c\
			ft_print_id.c\
			ft_itoa_base.c\
			ft_printf_fd.c\
			ft_strcmp.c\
			ft_itoa.c\
			ft_strdup.c\
			get_next_line_utils.c\
			ft_to_uppers.c\
			ft_write.c\
			ft_print_padding.c\
			get_next_line.c\
			ft_print_type.c\
			ft_print_str.c\
			ft_print_char.c\
			ft_print_ptr.c\

# Convert source files to object files
OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

# Total number of source files and bar length
TOTAL_FILES := $(words $(SRC_FILES))
BAR_LENGTH := 50
BAR_SYMBOL := "▓"
PROGRESS := 0

# Rule to compile .c into .o with loading bar that grows with each file
# it prints BAR_SYMBOL for each 2% of the total files compiled
# it prints the progress in percentage
# it prints the name of the file being compiled
# it prints the progress bar

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@$(eval PROGRESS := $(shell echo $$(($(PROGRESS) + 1))))
	@$(eval PERCENT := $(shell echo $$(($(PROGRESS) * 100 / $(TOTAL_FILES)))))
	@$(eval BAR := $(shell echo $$(($(PROGRESS) * $(BAR_LENGTH) / $(TOTAL_FILES)))))
	@$(eval REST := $(shell echo $$(($(BAR_LENGTH) - $(BAR)))))
	@echo -n "\r\033[K"  # Clear the line
	@echo -n "$(CYAN)["  # Start the bar

	@for i in `seq 1 $(BAR)`; do \
		echo -n $(BAR_SYMBOL); \
	done


	@echo -n "] $(PERCENT)% $(RED)Compiling:$(NOCOLOR) $<"
#	@sleep 0.1  # Just to make the bar smooth

# Create the library from object files with progress bar
$(NAME): $(OBJ_FILES)
	@echo ""
	@echo "$(YELLOW)Creating $(NAME)..."
	@ar rcs $(NAME) $(OBJ_FILES)
	@sleep 0.2 # Just to let the loading bar finish smoothly
	@echo -n "\r\033[K" # Erase the loading bar
	@echo "$(GREEN)$(NAME) created successfully.$(NOCOLOR)"

# Build everything
all: $(NAME)

# Clean object files
clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(BLUE)Object files removed.$(NOCOLOR)"

# Clean object files and the library
fclean: clean
	@rm -f $(NAME)
	@echo "$(BLUE)$(NAME) removed.$(NOCOLOR)"

# Rebuild the library
re: fclean all

.PHONY: all clean fclean re
