SRCS =	./srcs/main.c \
		./srcs/do_stuff.c \
		./srcs/talk.c \
		./srcs/setup.c \
		./srcs/time.c \
		./srcs/basic_utils.c \
		./srcs/ft_itoa.c

RENAME		= mv a.out philo
OBJ			= $(SRCS:.c=.o)
NAME		= philo
FS			= a.out.dSYM philo.dSYM
CC			= gcc
RM			= rm -f
RM_DIR		= rm -rf
CFLAGS		= -g3 -fsanitize=address -Wall -Wextra -Werror -DLinux
# -g3 -fsanitize=thread
DEP			= -lpthread
$(NAME):		$(OBJ)
#add CFLAGS
				@$(CC) $(CFLAGS) $(SRCS) $(DEP)
				@$(RENAME)
all:			$(NAME)
clean:
				@$(RM) $(OBJ)
fclean:			clean
				@$(RM) $(NAME)
				@$(RM_DIR) $(FS)
re:				fclean all	
.PHONY:			all clean fclean re

