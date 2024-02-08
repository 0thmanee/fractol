CC = cc
CFLAGS = -Wall -Wextra -Werror -O3
MLX = -lmlx -framework OpenGL -framework AppKit
RM = rm -f

NAME = fractol
CFILES = mandatory/fractol.c mandatory/fractol_operations.c mandatory/fractol_render.c mandatory/fractol_tools.c
OFILES = $(CFILES:.c=.o)
INCLUDES = mandatory/fractol.h

NAME_BONUS = fractol_bonus
CFILES_BONUS = bonus/fractol_bonus.c bonus/fractol_operations_bonus.c bonus/fractol_render_bonus.c bonus/fractol_tools_bonus.c
OFILES_BONUS = $(CFILES_BONUS:.c=.o)
INCLUDES_BONUS = bonus/fractol_bonus.h

all: $(NAME)
	@printf "\033[32m[ ✔ ] %s\n\033[0m" "Program Created"


$(NAME): $(OFILES)
	@$(CC) $(MLX) $(CFLAGS) $^ -o $@

mandatory/%.o: mandatory/%.c $(INCLUDES)
	@$(CC) $(CFLAGS) -c $< -o $@

bonus: $(NAME_BONUS)
	@printf "\033[32m[ ✔ ] %s\n\033[0m" "Bonus Program Created"

$(NAME_BONUS): $(OFILES_BONUS)
	@$(CC) $(MLX) $(CFLAGS) $^ -o $@

bonus/%.o: bonus/%.c $(INCLUDES_BONUS)
	@$(CC) $(CFLAGS) -c $< -o $@


clean:
	@$(RM) $(OFILES) $(OFILES_BONUS)

fclean: clean
	@$(RM) $(NAME) $(NAME_BONUS)
	@printf "\033[32m[ ✔ ] %s\n\033[0m" "Cleaning Done"

re: fclean all

.PHONY: all clean fclean re bonus