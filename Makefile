CC = gcc
NAME=minishell

INCLUDE = -I include -I utils/libft
CFLAGS = $(INCLUDE) #-Wall -Werror -Wextra

SRC_DIR = ./src/
SRC_FILES = main.c

UTILS_DIR = ./utils/

BUILT_INT_DIR = $(SRC_DIR)builtins/
BUILT_INS = echo.c pwd.c cd.c export.c ft_exit.c unset.c env.c

PARSER_IN_DIR = $(SRC_DIR)parser/
PARSER_INS =	parser.c get-cmd-name.c get-input-redir.c get-output-redir.c \
				get-args.c parse-semicolon.c parse-pipe.c parse-and.c parse-or.c \
				expand-string.c

GENERATOR_DIR = generator/
GENERATOR =	index.c

EXECUTER_IN_DIR = $(SRC_DIR)executer/
EXECUTER_INS =	errors.c executer.c get_command_path.c get_env_path.c \
				init_pipes.c redir_handler.c ft_exec.c utils.c

UTILS_INT_DIR = $(UTILS_DIR)
UTILS_INS = env_array_to_list.c env_list_to_array.c \
			env_list_delete.c sort.c env_list_insert.c 2d_array_free.c \
			env_list_get.c ft_strcmp.c

GET_NEXT_LINE_INT_DIR = $(UTILS_DIR)/get_next_line/
GET_NEXT_LINE_INS = get_next_line.c get_next_line_utils.c

CFILES = $(addprefix $(SRC_DIR), $(SRC_FILES))
CFILES += $(addprefix $(BUILT_INT_DIR), $(BUILT_INS))
CFILES += $(addprefix $(UTILS_INT_DIR), $(UTILS_INS))
CFILES += $(addprefix $(PARSER_IN_DIR), $(PARSER_INS))
CFILES += $(addprefix $(GENERATOR_DIR), $(GENERATOR))
CFILES += $(addprefix $(EXECUTER_IN_DIR), $(EXECUTER_INS))
CFILES += $(addprefix $(GET_NEXT_LINE_INT_DIR), $(GET_NEXT_LINE_INS))


OFILES = $(patsubst %.c, %.o, $(CFILES))

LIBFT_DIR = ./utils/libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OFILES)
	@echo "$(green)source files compiled successfully \n $(reset)"
	@echo "$(yellow)linking object files.. $(reset)"
	@$(CC) $(CFLAGS) $(OFILES) $(LIBFT) -o $(NAME)
	@echo "$(green)All done, binary file path: $(NAME)$(reset)"

fsanitize: CFLAGS += -fsanitize=address -g
fsanitize: re all
	@echo "$(red)fsanitize activated $(reset)"

debug: CFLAGS += -g
debug: re all

error: CFLAGS += -Wall -Werror -Wextra
error: re all

$(LIBFT):
	@echo "$(yellow)Compiling libft... $(reset)"
	@$(MAKE) bonus -C $(LIBFT_DIR)
	@echo "$(green)libft compiled \n$(reset)"

%.o:%.c
	@echo "$(yellow)Compiling $(reset)$<"
	@$(CC) $(CFLAGS) -c $< -o $@

re: fclean all 

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR)

clean:
	@echo "$(yellow)Cleaning object files... $(reset)"
	@rm -f $(OFILES)
	@echo "$(green)object files cleaned \n $(reset)"
	@echo "$(yellow)cleaning libft... $(reset)"
	@$(MAKE) clean -C $(LIBFT_DIR) 
	@echo "$(green)libft cleaned \n $(reset)"

.PHONY: clean fclean re

# colors
yellow=`tput setaf 3`
green=`tput setaf 2`
red=`tput setaf 1`
reset=`tput sgr0`
