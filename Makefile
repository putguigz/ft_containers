NAME= containerz

CC= clang++

CFLAGS= -Wall -Wextra -Werror -std=c++98

INCLUDES= containers_hpp

SRCS= $(shell find . -type f -name "*.cpp")

OBJS= $(addprefix $(OBJS_DIR)/, $(notdir $(SRCS:.cpp=.o)))

OBJS_DIR= objs

$(OBJS_DIR)/%.o: %.cpp
	$(CC) $(CFLAGS) -I$(INCLUDES) -c -o $@ $^

vpath %.cpp $(dir $(SRCS))


all: $(NAME)

echo: 
	@echo $(SRCS)
	@echo $(OBJS)

$(NAME): init $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) 

init:
	@mkdir -p $(OBJS_DIR)

clean:
	@rm -rf $(OBJS_DIR)
	@echo "deleting objects"

fclean: clean
	@rm -rf $(NAME)
	@echo "Full Clean"

re: fclean $(NAME)

.SUFFIXES: .cpp .o .hpp

.PHONY: all clean fclean re
