NAME= visu-hex
GCC= gcc -Wall -Wextra -Werror
INCLUDES= -I includes -I ../libft/includes -I minilibx -I ../includes
HEADER= includes/visu_hex.h

LIBFT= ../libft/libft.a
LFT= -L ../libft -lft

DLIBMLX= minilibx
include $(DLIBMLX)/lmlx.mk

DOBJS= objs
DSRCS= srcs

SRCS_FILES= main #new#

SRCS = $(addprefix $(DSRCS)/, $(addsuffix .c, $(SRCS_FILES)))
OBJS = $(SRCS:$(DSRCS)/%.c=$(DOBJS)/%.o)

all: $(NAME)

$(DOBJS):
	@mkdir -p $(DOBJS)

dolibft:
	@make -C ../libft

$(LIBMLX):
	@make -C $(DLIBMLX)

$(OBJS): $(DOBJS)/%.o: $(DSRCS)/%.c $(HEADER)
	@$(GCC) $(INCLUDES) -c $< -o $@

start:
	@echo "making visu-hex..."

$(NAME): start $(LIBMLX) dolibft $(DOBJS) $(OBJS) $(HEADER)
	@echo "objects done!"
	@$(GCC) -o $(NAME) $(OBJS) $(LFT) $(LMLX)
	@echo "visu-hex done!"

clean:
	@make clean -C minilibx
	@rm -rf $(DOBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all
