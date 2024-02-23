CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = object/object_create.c object/object_utils.c print/print.c scene/scene.c scene/scene_init.c\
util/utils_1.c util/utils_2.c util/utils_3.c  util/utils_4.c gnl/gnl.c gnl/gnl_utils.c\
trace/hit_cylinder.c trace/hit_util.c trace/hit.c main.c trace/normal.c trace/phong_lightening.c trace/ray.c \
check/check_util_1.c check/check_util_2.c check/check.c check/parse_util_1.c check/parse_util_2.c check/parse.c check/ft_split.c

OBJS = $(SRCS:.c=.o)
NAME = minirt

all: $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c -g $< -o $@

$(NAME) : $(OBJS)
	$(CC) -Lmlx -lmlx -framework OpenGL -framework Appkit -o $@ $(OBJS) -g

clean :
	rm -f *.o */*.o

fclean : clean
	rm -f $(NAME)

re: fclean all

.PHONY : re all fclean clean