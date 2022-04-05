NAME= 42

FT_NAME = $(addprefix ft_, $(NAME))
STD_NAME= $(addprefix std_, $(NAME))

NAME2= my

FT_NAME2 = $(addprefix ft_, $(NAME2))
STD_NAME2= $(addprefix std_, $(NAME2))

CXX= clang++

CXXFLAGS= -Wall -Wextra -Werror -std=c++98

INCLUDES= containers_hpp

SRCS= main_42.cpp

SRCS2= my_main.cpp

OBJS= $(addprefix $(OBJS_DIR)/, $(SRCS:.cpp=.o))

OBJS2= $(addprefix $(OBJS_DIR)/, $(SRCS2:.cpp=.o))

OBJS_DIR= objs

$(OBJS_DIR)/%.o: %.cpp
	@mkdir -p $(OBJS_DIR)
	@$(CXX) $(CXXFLAGS) -I$(INCLUDES) -c -o $@ $<

all: $(NAME) $(NAME2)

$(NAME): $(OBJS)
	@echo "Cooking up executables 🍪..."
	@$(CXX) $(CXXFLAGS) $(OBJS) -o $(FT_NAME)
	@$(CXX) $(CXXFLAGS) $(OBJS) -o $(STD_NAME) -D STD=1

$(NAME2): $(OBJS2)
	@echo "Cooking up executables 🍪..."
	@$(CXX) $(CXXFLAGS) $(OBJS2) -o $(FT_NAME2)
	@$(CXX) $(CXXFLAGS) $(OBJS2) -o $(STD_NAME2) -D STD=1

clean:
	@rm -rf $(OBJS_DIR)
	@echo "deleting objects"

fclean: clean
	@rm -rf $(FT_NAME) $(FT_NAME2) $(STD_NAME) $(STD_NAME2) 
	@echo "Full Clean"

re: fclean all

.SUFFIXES: .cpp .o .hpp

.PHONY: all clean fclean re
