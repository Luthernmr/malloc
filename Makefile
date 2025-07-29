NAME = libft_malloc_$(HOSTTYPE).so
SYMLINK = libft_malloc.so
CC = gcc
CFLAGS = -Wall -Wextra -Werror -fPIC -Iincludes
SRCS = src/malloc.c src/free.c src/realloc.c src/show_alloc_mem.c src/show_alloc_mem_ex.c
OBJS = $(SRCS:src/%.c=%.o)
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

# Test files
TEST_SRCS = tests/test_utils.c tests/test_basic.c tests/test_sizes.c tests/test_multiple.c \
            tests/test_edge_cases.c tests/test_memory_content.c tests/test_realloc.c \
            tests/test_show_alloc_mem.c tests/test_show_alloc_mem_ex.c tests/test_multithread.c
TEST_OBJS = $(TEST_SRCS:tests/%.c=tests/%.o)

MAIN_SRC = main.c
MAIN_EXEC = main

ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

all: $(NAME) $(SYMLINK)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -shared -o $@ $(OBJS) $(LIBFT)

$(SYMLINK): $(NAME)
	ln -sf $(NAME) $(SYMLINK)

%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

tests/%.o: tests/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MAIN_EXEC): $(MAIN_SRC) $(TEST_OBJS) $(NAME) $(LIBFT)
	$(CC) $(CFLAGS) -L. -lft_malloc $(LIBFT) $(MAIN_SRC) $(TEST_OBJS) -lpthread -o $(MAIN_EXEC)

run: $(MAIN_EXEC)
	@echo "Running $(MAIN_EXEC)..."
	DYLD_LIBRARY_PATH=.:$$DYLD_LIBRARY_PATH ./$(MAIN_EXEC)

clean:
	rm -f $(OBJS) $(TEST_OBJS) $(MAIN_EXEC) 
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME) $(SYMLINK) $(LIBFT)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re run
