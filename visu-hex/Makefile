# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mnunnari <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/06/17 16:59:08 by mnunnari          #+#    #+#              #
#    Updated: 2017/06/24 21:44:10 by mnunnari         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= visu-hex
GCC= gcc -Wall -Wextra -Werror
INCLUDES= -I includes -I ../libft/includes -I ../minilibx/includes -I ../includes
HEADER= includes/visu_hex.h

LIBFT= ../libft/libft.a
LFT= -L ../libft -lft

DLIBMLX= ../minilibx
include $(DLIBMLX)/lmlx.mk

DOBJS= objs
DSRCS= srcs

LI_SRCS_FILES= li_error print_hex free utils parse_rooms parse_ants  #new#
LI_SRCS = $(addprefix ../$(DSRCS)/, $(addsuffix .c, $(LI_SRCS_FILES)))
LI_OBJS = $(LI_SRCS:../$(DSRCS)/%.c=$(DOBJS)/%.o)

SRCS_FILES= main draw_links parse_turns draw_rooms parse_links #new#
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

$(LI_OBJS): $(DOBJS)/%.o: ../$(DSRCS)/%.c $(HEADER)
	@$(GCC) $(INCLUDES) -c $< -o $@

start:
	@echo "making visu-hex..."

$(NAME): start $(LIBMLX) dolibft $(DOBJS) $(OBJS) $(LI_OBJS) $(HEADER)
	@echo "objects done!"
	@$(GCC) -o $(NAME) $(LI_OBJS) $(OBJS) $(LFT) $(LMLX)
	@echo "visu-hex done!"

clean:
	@make clean -C $(DLIBMLX)
	@rm -rf $(DOBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all
