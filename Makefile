NAME = libft_malloc_$(HOSTTYPE).so
SYMLINK = libft_malloc.so
CC = gcc
CFLAGS =  -fPIC -Iincludes
SRCS = src/malloc.c src/free.c src/realloc.c
OBJS = $(SRCS:src/%.c=%.o)
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

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

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MAIN_EXEC): $(MAIN_SRC) $(NAME) $(LIBFT)
	$(CC) $(CFLAGS) -L. -lft_malloc $(LIBFT) $(MAIN_SRC) -o $(MAIN_EXEC)

run: $(MAIN_EXEC)
	@echo "Running $(MAIN_EXEC)..."
	DYLD_LIBRARY_PATH=.:$$DYLD_LIBRARY_PATH ./$(MAIN_EXEC)

clean:
	rm -f $(OBJS) $(MAIN_EXEC) 
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME) $(SYMLINK) $(LIBFT)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re run
