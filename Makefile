NAME= containerz

CXX= clang++

CXXFLAGS= -Wall -Wextra -Werror -std=c++98 -pedantic

DFLAGS= -D STD=0

INCLUDES= containers_hpp

SRCS= main_42.cpp

OBJS= $(addprefix $(OBJS_DIR)/, $(SRCS:.cpp=.o))

OBJS_DIR= objs

$(OBJS_DIR)/%.o: %.cpp
	@mkdir -p $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) $(DFLAGS) -I$(INCLUDES) -c -o $@ $<

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME) 

clean:
	@rm -rf $(OBJS_DIR)
	@echo "deleting objects"

fclean: clean
	@rm -rf $(NAME)
	@echo "Full Clean"

re: fclean $(NAME)

.SUFFIXES: .cpp .o .hpp

.PHONY: all clean fclean re
