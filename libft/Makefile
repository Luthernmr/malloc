# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lnemor <lnemor.student@42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/06 12:45:11 by lnemor            #+#    #+#              #
#    Updated: 2021/11/06 12:45:11 by lnemor           ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a

SRCS	=	ft_strlcpy.c \
			ft_strlen.c	\
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_strlcat.c \
			ft_tolower.c \
			ft_toupper.c \
			ft_strlcpy.c \
			ft_strchr.c \
			ft_strrchr.c \
			ft_strncmp.c \
			ft_memset.c \
			ft_bzero.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memchr.c \
			ft_strnstr.c \
			ft_memcmp.c \
			ft_atoi.c \
			ft_strdup.c \
			ft_calloc.c \
			ft_substr.c \
			ft_isspace.c \
			ft_strjoin.c \
			ft_strtrim.c \
			ft_split.c \
			ft_itoa.c \
			ft_strmapi.c \
			ft_striteri.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \

SRCBONUS = 	ft_lstnew.c \
			ft_lstadd_front.c	\
			ft_lstsize.c \
			ft_lstlast.c \
			ft_lstadd_back.c \
			ft_lstdelone.c \
			ft_lstclear.c	\
			ft_lstiter.c \
			ft_lstmap.c 

OBJSBONUS 	=	$(SRCBONUS:.c=.o)

OBJS	=	$(SRCS:.c=.o)

CC		=	gcc 

CFLAGS	= 	-Wall -Werror -Wextra

LIB 	= 	ar -rcs

RM		= 	rm -f

CLEAN	=	CLEAN

%.o:%.c libft.h
		$(CC) $(CFLAGS) -c $< -o $@

all		: $(NAME)

$(NAME)	:	$(OBJS)
		$(LIB) $(NAME) $(OBJS)

bonus	: $(OBJSBONUS)
		$(LIB) $(NAME) $(OBJSBONUS)

clean 	:
		$(RM) $(OBJS) $(OBJSBONUS)

fclean	: clean
		$(RM) $(NAME)

re :	fclean all

.PHONY: fclean clean all re bonus