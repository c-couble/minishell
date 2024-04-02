SRC = \
	  env/destroy_env.c \
	  env/get_envp.c \
	  env/init_env.c \
	  env/ms_getenv.c \
	  env/ms_getnenv.c \
	  env/ms_setenv.c \
	  env/print_env.c \
	  \
	  execution/execute_commands.c \
	  execution/execute_pipeline.c \
	  execution/execute_simple_command.c \
	  execution/execute_subshell.c \
	  execution/execution_structure.c \
	  execution/get_path.c \
	  execution/next_token.c \
	  execution/perform_redirections.c \
	  execution/run_command.c \
	  execution/simplify_tokens.c \
	  \
	  expansions/parameters/expand_substring.c \
	  expansions/parameters/expand_parameters.c \
	  expansions/parameters/treat_noquote.c \
	  \
	  expansions/quote_removal/quote_removal.c \
	  \
	  expansions/word_split/word_split.c \
	  \
	  expansions/perform_expansions.c \
	  \
	  lexer/init_lexer.c \
	  lexer/fill_lexer.c \
	  lexer/print_lexer.c \
	  lexer/clear_lexer.c \
	  lexer/clear_token.c \
	  lexer/add_newline_tok.c \
	  lexer/char_filter/is_blank.c \
	  lexer/char_filter/is_operand.c \
	  lexer/char_filter/is_word.c \
	  lexer/char_filter/is_quote.c \
	  lexer/char_filter/to_next_quote.c \
	  \
	  parser/validate_input.c \
	  \
 	  \
	  util/get_ifs.c \
	  util/next_char.c \
	  \
	  wildcard/expand_wildcards.c \
	  wildcard/fill_pattern.c \
	  wildcard/get_matching_filenames.c \
	  wildcard/is_wildcard_match.c \
	  wildcard/sort_filenames.c \
	  \
	  main.c \
	  parse_input.c \
