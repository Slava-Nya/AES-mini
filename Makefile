NAME	= aes.a

CC		= gcc
NA		= nasm
NFLAGS	= -f elf64
EXEC	= aes_test

SRCS	= encrypt.s \
		  decrypt.s


OBJS	= $(SRCS:%.s=%.o)

all: $(NAME)

%.o:%.s
	$(NA) $(NFLAGS) $<

$(NAME): $(OBJS)
	ar rcs $(NAME) $^
	ranlib $(NAME)

bonus: $(BOBJS)
	ar rcs $(NAME) $^
	ranlib $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME) $(EXEC)

re: fclean all

test: re
	@$(RM) $(EXEC)
	$(CC) main.c $(NAME) -o $(EXEC)
	./$(EXEC)
	@$(RM) linux_read_output linux_write_output ft_read_output ft_write_output

.PHONY: all clean fclean re test