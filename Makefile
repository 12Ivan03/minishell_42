CC = cc
CFLAGS = -g -I./lib/libft -I./include
# -Wall -Wextra -Werror
LIB_READLINE = -L/usr/lib -lreadline

BUILD_PATH = ./build
SRC_PATH = ./src

SRC_FILES = src/main.c \
			src/minilib/ft_skippers_1.c \
			src/minilib/ft_skippers_2.c \
			src/minilib/al_env_handlers_1.c \
			src/minilib/al_env_handlers_2.c \
			src/minilib/al_env_expanders.c\
			src/minilib/ft_joins.c \
			src/minilib/ft_chars.c \
			src/minilib/al_prg_path.c \
			src/minilib/al_check_path.c \
			src/minilib/al_env_string.c \
			src/minilib/ft_like_a_split.c  \
			src/minilib/is_white_space.c \
			src/minilib/convert_our2env.c \
			src/init/init_main.c \
			src/init/init_cmd_fun.c \
			src/init/init_and.c \
			src/init/init_child_processes.c \
			src/free/al_destroy_free.c \
			src/free/al_destroy_free_main.c \
			src/free/ip_destroy_free_main_1.c \
			src/free/ip_destroy_free_main_2.c \
			src/free/ip_destroy_free_main_3.c \
			src/util/al_quotes.c \
			src/util/al_prompt.c \
			src/util/al_print_helper_3.c \
			src/util/here_doc.c \
			src/util/here_doc_helpers.c \
			src/util/here_doc_extra_helper.c \
			src/util/analyze_and_dispatch.c \
			src/util/analyze_and_dispatch_two.c \
			src/util/analyze_and_dispatch_utils.c \
			src/util/analyze_and_dispatch_packeging.c \
			src/util/analyze_and_dispatch_packeging_helper_one.c \
			src/util/analyze_and_dispatch_packeging_helper_two.c \
			src/util/create_redir_list.c \
			src/preps/build_in_exe.c \
			src/preps/build_in_error_seeker.c \
			src/preps/build_in_error_seeker_helper.c \
			src/preps/al_lexer.c \
			src/preps/al_lexer_words.c \
			src/preps/al_lexer_words_helpers.c \
			src/preps/create_word_l.c \
			src/preps/ip_parsing.c \
			src/preps/create_token_l.c \
			src/preps/token_utils.c \
			src/preps/token_utils_two.c \
			src/preps/token_utils_cmd_fun.c \
			src/preps/read_our_env.c \
			src/preps/get_enum_utils.c \
			src/preps/pwd_env_exe.c \
			src/preps/check_readline.c \
			src/preps/check_pipes.c \
			src/command/export_exe.c \
			src/command/export_exe_utils.c \
			src/command/export_exe_utils_two.c \
			src/command/export_exe_utils_three.c \
			src/command/unset_exe.c \
			src/command/export_print.c \
			src/command/export_print_helper.c \
			src/command/cd_exe.c \
			src/command/echo_exe.c \
			src/command/exit_exe.c \
			src/processes/child_process.c \
			src/processes/child_process_helper.c \
			src/error/error_handler.c \
			src/error/error_print.c \
			src/error/error_handler_helper.c \
			src/signals/set_up_signals.c \
			src/signals/signal_handler.c \

# Преобразуем путь .c -> build/xxx.o
OBJ_FILES = $(SRC_FILES:.c=.o)
OBJ_FILES := $(OBJ_FILES:src/%=$(BUILD_PATH)/%)

NAME = minishell
LIBFT = ./lib/libft/libft.a

all: $(NAME)

# Правило компиляции: build/xxx.o из src/xxx.c
$(BUILD_PATH)/%.o: src/%.c
	@mkdir -p $(dir $@)
	@echo "Compiling $< to $@"
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C lib/libft --silent

$(NAME): $(OBJ_FILES) $(LIBFT)
	@echo "Linking objects to create $(NAME)"
	@$(CC) $(CFLAGS) $(OBJ_FILES) $(LIBFT) -o $(NAME) $(LIB_READLINE)

clean:
	@rm -rf $(BUILD_PATH)
	@$(MAKE) -C lib/libft clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C lib/libft fclean

re: fclean all

.PHONY: all clean fclean re
