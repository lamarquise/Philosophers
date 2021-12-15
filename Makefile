

CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra -pthread
# might need to add -pthread somewhere could do it in flags

NAME		=	philo

DIR_PHILO	=	./srcs/

SRCS_PHILO	=	philo_main.c \
				parsing.c \
				time.c \


# may move these to be in the SRCS folder, if the cors are gonna get all annoying about it...
DIR_MINILIB	=	./minilib/
SRCS_MINILIB	=	atoi_funcs.c \
					big_str_funcs.c \
					error_funcs.c \
					ft_split.c \
					ft_strjoin.c \
					is_funcs.c \
					list_funcs.c \
					nlist_funcs.c \
					nlstdel_n_one.c \
					ilist_funcs.c \
					put_funcs.c \
					str_funcs.c \
					tab_funcs.c \
					gnl.c \
					gnl_utils.c \


DIR_INC		=	./includes/
INCS		=	-I$(DIR_INC)


# if we had a library we would add its .h here
ALL_INCS	=	$(INCS) -I$(DIR_MINILIB)

DIR_OBJ		=	./objs/

OBJ_MINILIB	=	$(SRCS_MINILIB:.c=.o)
OBJ_PHILO	=	$(SRCS_PHILO:.c=.o) $(OBJ_MINILIB)

OBJS_PHILO	=	$(addprefix $(DIR_OBJ),$(OBJ_PHILO))


##### RULES ######

all: $(NAME)

$(NAME): $(OBJS_PHILO)
	$(CC) $(CFLAGS) $(ALL_INCS) $(OBJS_PHILO) -o $(NAME)
	printf "$(_GREEN)\r\33[2K\r$(NAME) created  😎\n$(_END)"


$(DIR_OBJ)%.o: $(DIR_PHILO)%.c
	mkdir -p $(DIR_OBJ)
	$(CC) $(CFLAGS) $(ALL_INCS) -c $< -o $@
	printf "$(_CYAN)\r\33[2K\rCompling $@$(_END)"

$(DIR_OBJ)%.o: $(DIR_MINILIB)%.c
	mkdir -p $(DIR_OBJ)
	$(CC) $(CFLAGS) $(ALL_INCS) -c $< -o $@
	printf "$(_CYAN)\r\33[2K\rCompling $@$(_END)"

clean:
	rem -rf $(DIR_OBJ)
	echo "$(_RED).o Files Deleted  😱$(_END)"

fclean: clean
	rm -rf $(NAME)
	echo "$(_RED)$(NAME) Deleted  😱$(_END)"

re: fclean all

tests:

testl:

testv:

.PHONY: all clean fclean re tests testl testv

.SILENT:

##################
##    COLORS    ##
##################

_GREY=$ \033[30m
_RED=$ \033[31m
_GREEN=$ \033[32m
_YELLOW=$ \033[33m
_BLUE=$ \033[34m
_PURPLE=$ \033[35m
_CYAN=$ \033[36m
_WHITE=$ \033[37m
_END=$ \033[0m


