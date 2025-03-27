# build all
all: libs build bonus

# Colors
GREEN = \033[0;32m
RED = \033[0;31m
CYAN = \033[0;36m
BLUE = \033[0;34m
YELLOW = \033[0;33m
NOCOLOR = \033[0m

# Name of the project
NAME = minishell 

# Compiler
CC = cc

# Flags
CFLAGS = -Wall -Wextra -Werror -g
POSTCC = -I $(INC_DIR) -I $(LIB_DIR) -L/usr/lib/x86_64-linux-gnu -L/usr/lib -lreadline -lncurses

# Directories
SRC_DIR = ./src
OBJ_DIR = ./obj
INC_DIR = ./inc
LIB_DIR = $(INC_DIR)/lib_ft

# Object directory
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Rule to build the included library
LIBS = $(LIB_DIR)/libft.a

# Source and bonus files
SRC_FILES = $(shell find $(SRC_DIR) -type f -name "*.c")

# Object files
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES)) 

# Total number of files and bar length
TOTAL_FILES := $(words $(SRC_FILES))
BAR_SYMBOL := ▓
BAR_LENGTH := 50
PROGRESS := 0

# Rule to compile .c into .o with progress bar
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)  # Create the directory if it doesn't exist
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

# Rule to compile the included library
$(LIBS):
	@make -C $(LIB_DIR) #> /dev/null 2>&1
	@echo "$(GREEN)Library built successfully.$(NOCOLOR)"

# Rule to compile the project
$(NAME): $(OBJ_FILES)
	@echo ""
	@echo "$(YELLOW)Creating $(NAME)..."
	@$(CC) $(CFLAGS) $(POSTCC) $(OBJ_FILES) -o $(NAME) -L/usr/lib/x86_64-linux-gnu -lreadline -lncurses $(LIBS)
	@sleep 0.2 # Just to let the loading bar finish smoothly
	@echo -n "\r\033[K" # Erase the loading bar
	@echo "$(GREEN)$(NAME) created successfully.$(NOCOLOR)"

# build only the library
libs: $(LIBS)

# build the project
build: $(NAME)

# clean the object files
clean:
	@rm -rf $(OBJ_DIR)
	@make clean -C $(LIB_DIR) > /dev/null 2>&1
	@echo "$(BLUE)Object files removed.$(NOCOLOR)"
	@echo "$(GREEN)Clean done.$(NOCOLOR)"

# clean the object files and the project
fclean: clean
	@rm -f $(NAME) $(BONUS)
	@make fclean -C $(LIB_DIR) > /dev/null 2>&1
	@echo "$(BLUE)Project removed.$(NOCOLOR)"
	@echo "$(GREEN)Full clean done.$(NOCOLOR)"

# clean and rebuild the project
re: fclean all

# run the project
run: build
	@./$(NAME)

.PHONY: all clean fclean re run libs build bonus
