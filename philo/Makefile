NAME = philo

SRCS = src/philo.c\
		src/parsing_utils.c\
		src/utils.c\
		src/philo_utils.c\
		src/init_utils.c\
		src/routine_utils.c\
		src/free_utils.c\
		src/philo_utils_2.c

OBJS = $(SRCS:.c=.o)
INCDIR = includes
INC = -I $(INCDIR)

CC = cc
INCDIR = includes
INC = -I $(INCDIR)

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -g $(INC)
RM = rm -f

# Couleurs

# Couleurs
RED = \033[1;31m
ORANGE = \033[38;5;208m
YELLOW = \033[1;33m
RESET = \033[0m

all: $(NAME) ascii

$(NAME): $(OBJS)
	@echo "$(YELLOW)Compilation de $(NAME)...$(RESET)"
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(YELLOW)Compilation terminée !$(RESET)"

ascii:
	@echo "$(RED) (        )  (    (        )   (        )   (        )       (    (     "
	@echo "$(RED) )\ )  ( /(  )\ ) )\ )  ( /(   )\ )  ( /(   )\ )  ( /(       )\ ) )\ )  "
	@echo "$(ORANGE)(()/(  )\())(()/((()/(  )\()) (()/(  )\()) (()/(  )\()) (   (()/((()/(  "
	@echo "$(ORANGE) /(_))((\_  /(_))/(_))((\_   /(_))((\_   /(_))((\_  )\   /(_))/(_)) "
	@echo "$(YELLOW)(_))   _((_)(_)) (_))    ((_) (_))    ((_) (_))   _((_)((_) (_)) (_))   "
	@echo "$(YELLOW)| _ \ | || ||_ _|| |    / _ \ / __|  / _ \ | _ \ | || || __|| _ \/ __|  "
	@echo "$(YELLOW)|  _/ | __ | | | | |__ | (_) |\__ \ | (_) ||  _/ | __ || _| |   /\__ \  "
	@echo "$(YELLOW)|_|   |_||_||___||____| \___/ |___/  \___/ |_|   |_||_||___||_|_\|___/  "
	@echo "$(RESET)"

clean:
	@echo "$(RED)Suppression des fichiers objets...$(RESET)"
	$(RM) $(OBJS)

fclean: clean
	@echo "$(RED)Suppression de $(NAME)...$(RESET)"
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
