/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerokhin <aerokhin@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:57:04 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/26 19:06:05 by aerokhin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <libft.h>
# include <tokens.h>
# include <time.h>

# define TXT_RED "\x1b[31m"
# define TXT_GREEN "\x1b[32m"
# define TXT_YELLOW "\x1b[33m"
# define TXT_BLUE "\x1b[34m"
# define TXT_BOLD "\x1b[1m"
# define TXT_UNDERL "\x1b[4m"
# define TXT_ITAL "\x1b[3m"
# define TXT_RES "\x1b[0m"

# define CHECK_OK		0
# define ERR_NOT_EXIST	-1
# define ERR_NO_PERM	-2
# define ERR_IS_DIR		-3
# define ERR_NOT_DIR	-4

# define MAX_LEN_PROMPT 35

# define PRG_NAME "minihell: "

typedef struct s_list_words
{
	char					*word;
	int						space_before;
	struct s_list_words		*next;
	struct s_list_words		*prev;
}	t_list_words;

typedef struct s_our_env
{
	char					*var_name;
	char					*value;
	struct s_our_env		*next;
	struct s_our_env		*prev;
}	t_our_env;

typedef struct s_list_tokens
{
	t_tokens				token;
	void					*value;
	struct s_list_tokens	*next;
	struct s_list_tokens	*prev;
}	t_list_tokens;

typedef struct s_main_env
{
	t_list_words			*list_words;
	t_list_tokens			*list_tokens;
	char					*curr_dir;
	char					*prev_dir;
	char					*home_dir;
	int						here_doc_index;
	char					**real_env;
	struct s_package		*package;
	t_our_env				*our_env;
	int						exit_status;
	int						export_error;
	int						p_error;
}	t_main_env;

typedef struct s_word
{
	char	*str;
	int		space_before;
}	t_word;

typedef struct s_string
{
	char	*str;
	int		space_before;
}	t_string;

typedef struct s_command
{
	char			*command;
	struct s_opt	*option;
	char			*parameters;
}	t_command;

typedef struct s_program
{
	char			*name;
	char			*parameters;
}	t_program;

typedef struct s_re_input
{
	char			*file_name;
}	t_re_input;

typedef struct s_re_output
{
	char	*file_name;
}	t_re_output;

typedef struct s_re_here
{
	char	*stop_word;
	int		variable;
	int		tab;
	char	*file_name;
}	t_re_here;

typedef struct s_re_append
{
	char	*file_name;
}	t_re_append;

typedef struct s_env_var
{
	char	*var_name;
	char	*value;
	char	*rest;
	int		fl;
}	t_env_var;

typedef struct s_opt
{
	char	*opt_name;
}	t_opt;

typedef struct s_node_file
{
	char				*name;
	t_tokens			redir_enum;
	struct s_node_file	*prev;
	struct s_node_file	*next;
}	t_node_file;

typedef struct s_package
{
	t_command					*command;
	t_program					*program;
	int							flag;
	t_node_file					*redir;
	struct s_package			*prev;
	struct s_package			*next;
}	t_package;

typedef struct s_and
{
	int			count_pipes;
	int			prev_fd;
	int			pipe_fd[2];
	int			status;
	int			count_children;
	int			i;
	int			error_flag;
	int			save_fd_in;
	int			save_fd_out;
	int			file_in;
	int			file_out;
	int			has_in;
	int			has_out;
	int			break_loop_exit;
	int			were_in_loop;
	pid_t		pid;
}	t_and;

typedef struct s_cp
{
	int			file_fd_in;
	int			file_fd_out;
	int			has_in;
	int			has_out;
	int			error_flag;
	int			c_prev_fd;
}	t_cp;

typedef struct s_ijk
{
	size_t		i;
	size_t		j;
	size_t		k;
}	t_ijk;

int				ip_remove_quotes(t_main_env **main_env, char **arr);
int				arr_len(char **argv);
int				prep_n_exec(t_main_env **main_env, t_program *token);
int				read_our_env(char **envp, t_main_env **main_env);
int				create_list_env(t_main_env **main_env, char *str, \
												t_our_env **env);
t_our_env		*create_node_env(t_main_env **main_env, char *str);
int				error_main(void);
void			error_handler_nc(t_main_env **main_env, int n, \
										char *command, char *option);
void			error_handler_nc_one(t_main_env **main_env, int n, \
										char *command, char *option);
void			error_handler_nc_two(t_main_env **main_env, int n, \
										char *command, char *option);
void			error_handler_nc_three(t_main_env **main_env, int n, \
										char *command, char *option);
void			error_handler_nc_four(t_main_env **main_env, int n, \
										char *command, char *option);
int				shall_you_pass(char *str);

int				error_handler_num(t_main_env **main_env, \
					int n, char *command, char *option);
void			*error_handler_null(t_main_env **main_env, \
					int n, char *command, char *option);
void			free_main_env(t_main_env **main_env);
void			free_list_words(t_list_words **list_words);
void			free_list_tokens(t_list_tokens **list_tokens);
void			free_token_void(t_list_tokens **token);
void			free_our_env(t_our_env **our_env);
void			free_command(t_command **command);
void			free_program(t_program **program);
void			free_package(t_package **package);
void			free_packages_d(t_package **packages);
void			free_word(t_word *word);
void			free_string(t_string *string);
void			free_re_in(t_re_input **input);
void			free_re_out(t_re_output **output);
void			free_re_here(t_re_here **here);
void			free_re_app(t_re_append **append);
void			free_node_file(t_node_file **node);
void			free_str_array(char **arr);
void			ft_close(int fd);
void			clear_here_doc_files(t_main_env **main_env);
void			init_main(t_main_env **main_env);
int				init_command_function(t_command	**command, char *str);
int				init_program_function(t_program	**program, char *str);
t_package		*init_package(void);
void			init_cp(t_cp *cp, int prev_fd);
int				is_meta_char(char c);
int				is_quote(char c);
int				built_in_command(char *str);
int				build_in_error_seeker(t_main_env **main_env, \
										t_command *command);
int				cd_error_exe(t_command *command, t_main_env **main_env);
int				export_unset_error_exe(t_main_env **main_env, \
								t_command *command, int flag);
int				pwd_env_error_exe(t_main_env **main_env, \
										t_command *command);
int				eval_export_input(t_main_env **main_env, \
									char **cmd_split_array, int flag);
int				shall_you_pass(char *str);
int				ft_arr_len(char **arr);
char			*cpy_with_baskslash(t_main_env **main_env, char *str);
int				pwd_env_exe(t_command *command, t_main_env **main_env);
int				print_export_env(t_main_env **main_env);
t_our_env		*copy_env(t_our_env **our_env);
t_list_tokens	*parsing(t_main_env **main_env, t_list_words *list_words);
void			*word_function(t_main_env **main_env, char *str);
void			*string_function(t_main_env **main_env, char *str);
void			*command_function(t_main_env **main_env, char *str, \
									t_list_words	**list_words);
void			*program_function(t_main_env **main_env, char *str, \
									t_list_words	**list_words);
int				command_option_determination(t_command	**command, \
									t_list_words **list_words);
int				command_parameters_populate(t_command **command, \
									t_list_words **list_words, char **tmp);
void			*option_function(t_main_env **main_env, char *str);
int				program_loop_helper(t_program **program, \
									t_list_words **list_words, char **tmp);
void			*re_in_function(t_main_env **main_env, \
									t_list_words	**list_words);
void			*re_out_function(t_main_env **main_env, \
									t_list_words	**list_words);
void			*re_here_function(t_main_env **main_env, \
									t_list_words	**list_words);
void			*re_app_function(t_main_env **main_env, \
									t_list_words	**list_words);
int				analyze_and_dispatch(t_main_env **main_env);
char			*gather_prev_and_next(char *name, char *opt, char *param);
int				populate_package(t_main_env **main_env, t_package *temp, \
									t_list_tokens *tokens);
void			while_and(t_main_env **main_env, t_and *and, \
													t_package *package);
t_and			loca_init_and(t_main_env **main_env);
int				check_permission_fail(t_main_env **main_env, char *file_name, \
																	int flag);
int				check_error_path(t_main_env **main_env, t_package *package);
t_package		*prepare_packages(t_main_env **main_env);
char			**convert_our2env(t_main_env **main_env);
int				is_white_space(char c);
char			*join_and_free(char **s1, char **s2);
char			*ft_str3join(char *s1, char *s2, char *s3);
int				count_characters_before(char *str, char c, int start);
char			*repeat_char(char c, int n);
int				link_t_word(t_list_words **list_words, char *word, \
							int space_before);
int				link_t_token(t_main_env **main_env, t_list_tokens **list_token, \
							t_list_words **list_words);
int				create_redir_list(t_main_env **main_env, \
							t_tokens enum_token, void *token_value, \
													t_package *temp);
int				detect_program(t_list_words **list_words);
int				handle_heredoc(t_re_here *redir, t_main_env **main_env);
int				check_readline(t_main_env **main_env, char **str);
int				pipe_pipe(char *str);
int				is_pipe(char c);
t_list_words	*lexer(t_main_env **main_env, char *str);
int				word_env_var(t_main_env **main_env, t_list_words **list_words, \
														char *str, size_t *i);
int				word_more_n_less(t_main_env **main_env, \
							t_list_words **list_words, char *str, size_t *i);
int				word_option(t_main_env **main_env, t_list_words **list_words, \
													char *str, size_t *i);
int				word_string(t_main_env **main_env, t_list_words **list_words, \
													char *str, size_t *i);
t_list_tokens	*parsing(t_main_env **main_env, t_list_words *list_words);
int				build_in_exe(t_main_env **main_env, t_command *command, \
								pid_t *child_pids);
int				export_exe(t_command *command, t_main_env **main_env);
int				update_rewrite_env(t_main_env **main_env, \
						t_our_env *node_plus_env, char *comd_prms, int flag);
int				append_to_our_env(t_main_env **main_env, \
													char *command, int pass);
int				find_env_node(t_our_env **our_env, char *params, \
										t_our_env	**find_node);
int				append_env_value(t_main_env **main_env, \
									t_our_env *node_plus_env, char *cpy_cmd);
int				rewrite_env_value(t_our_env *node_plus_env, char *cpy_cmd);
int				eval_export_input(t_main_env **main_env, \
									char **cmd_split_array, int flag);
int				shall_you_pass(char *str);
int				unset_exe(t_main_env **main_env, t_command *command, \
												t_our_env **our_env);
int				cd_exe(t_command *command, t_main_env **main_env);
int				echo_exe(t_command *command, t_main_env **main_env);
int				exit_exe(t_command *command, t_main_env **main_env);
int				child_process(t_main_env **main_env, t_package *package, \
								int prev_fd, int *pipe_fd);
char			*get_env_value(t_main_env **main_env, char *name);
char			*is_program(t_main_env **main_env, char *cmd);
char			*replace_vars(t_main_env **main_env, \
							char *src, int flag, int chng_tld);
char			*handle_single_quotes(t_main_env **main_env, \
							char *str, size_t *i, int flag);
char			*handle_double_quotes(t_main_env **main_env, \
							char *str, size_t *i, int flag);
char			**ft_like_a_split(char *str);
char			*prompt(t_main_env **main_env);
char			*read_curr_dir(void);
int				skip_spaces(char *str);
int				skip_last_spaces(char *str);
char			*remove_quotes_n_join(t_main_env **main_env, \
								char *str, int start, int end);
t_env_var		*get_var_info_substr(t_main_env **main_env, \
						char *str, size_t start, size_t *var_len);
char			*add_quotes(t_main_env **main_env, char *str, char c);
void			set_up_signals(t_main_env **main_env);
void			sig_in_handler_parent(int in_sig);
void			sig_out_handler(int out_sig);
t_command		*ft_command_dup(t_command *command);
t_program		*ft_program_dup(t_program *program);
int				is_white_space(char c);
int				is_meta_char(char c);
int				is_quote(char c);
void			skip_text(char *str, size_t *i);
void			skip_quotes(char *str, size_t *i);
void			skip_till_quotes(char *str, size_t *i, char c);
void			skip_whitespace(char *str, size_t *i);
void			skip_till_specchars(char *str, size_t *i);
void			skip_till_meta_quotes(char *str, size_t *i);
int				skip_if_quotes(char *str, size_t *i);
char			*handle_no_closing_quote(char *str, size_t *i, size_t j);
int				handle_curly_var(char *str, size_t i, \
							size_t *var_len, char **temp);
char			*copy_substr(char *str, size_t *i, size_t len);
int				handle_var_name(char *str, \
									size_t i, size_t *var_len, char **temp);
int				expand_var_value(t_main_env **main_env, \
									t_env_var *env_var, char *temp);
int				expand_question_sign(t_main_env **main_env, char *str, \
									size_t *var_len, t_env_var *env_var);
char			*expand_env_var(t_main_env **main_env, \
									char *str, size_t *i, int flag);
char			*expand_text(t_main_env **main_env, \
									char *str, size_t *i, int flag);
void			free_env_var(t_env_var *env_var);
t_env_var		*init_env_var(void);
void			here_doc_child(t_re_here *rd, t_main_env **main_env, int fd);
void			putendln_and_free(char **str, int fd);
char			*trim_tab(char *line);
char			*take_heredoc_path(int src);
char			*get_processed_line(char *line, \
								t_main_env **main_env, int var_flag);
char			*more_single_double(char *str, size_t *i);
void			ft_free(void **ptr);
void			print_our_env(t_our_env **our_env);
void			err_prt_n(char *str);
void			err_prt_one(char *str, char *str1);
void			err_prt_two(char *str, char *str1, char *str2);
void			err_prt_three(char *str, char *str1, char *str2, char *str3);
void			err_prt_char(char *str, char c, char *str1);
void			prep_path_exit_prg(t_main_env **main_env, int status_err, \
									char *path);
int				prep_path_ret_dir(t_main_env **main_env, int status_err, \
									char *path);
int				check_path_status(char *path, int dir_or_not);
int				is_correct_pipes(char **str);
void			free_heredoc_data(t_re_here *rd);
int				check_here_stop_word(t_re_here *redir, t_main_env **main_env);
void			exit_here_doc(int fd, int tmp);
int				result_heredoc(t_main_env **main_env, \
								int status, int heredoc_stat);

#endif
