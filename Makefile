NAME= lem-in
GCC= gcc -Wall -Wextra -Werror
INCLUDES= -I includes -I libft/includes #-I minilibx
HEADER= includes/lem_in.h

LIBFT= libft/libft.a
LFT= -L libft -lft

#DLIBMLX= minilibx
#include $(DLIBMLX)/lmlx.mk

DOBJS= objs
DSRCS= srcs

SRCS_FILES= main #new#

SRCS = $(addprefix $(DSRCS)/, $(addsuffix .c, $(SRCS_FILES)))
OBJS = $(SRCS:$(DSRCS)/%.c=$(DOBJS)/%.o)

all: $(NAME)

$(DOBJS):
	@mkdir -p $(DOBJS)

$(LIBFT):
	@make -C libft

#$(LIBMLX):
#	@make -C $(DLIBMLX)

$(OBJS): $(DOBJS)/%.o: $(DSRCS)/%.c $(HEADER)
	@$(GCC) $(INCLUDES) -c $< -o $@

start:
	@echo "making lem-in..."

$(NAME): start $(LIBFT) $(DOBJS) $(OBJS) $(HEADER) #$(LIBMLX)
	@echo "objects done!"
	@$(GCC) -o $(NAME) $(OBJS) $(LFT) #$(LMLX)
	@echo "lem_in done!"

clean:
	@make clean -C libft
#	@make clean -C minilibx
	@rm -rf $(DOBJS)

fclean: clean
	@make fclean -C libft
	@rm -f $(NAME)

re: fclean all
