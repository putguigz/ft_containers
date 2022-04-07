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

OBJS_DIR= objs


all: $(NAME) $(NAME2)

$(OBJS_DIR)/main_42_ft.o: main_42.cpp
	@mkdir -p $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDES) -c -o $@ $< -D STD=0

$(OBJS_DIR)/main_42_std.o: main_42.cpp
	@mkdir -p $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDES) -c -o $@ $< -D STD=1

$(OBJS_DIR)/my_main_std.o: my_main.cpp
	@mkdir -p $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDES) -c -o $@ $< -D STD=1

$(OBJS_DIR)/my_main_ft.o: my_main.cpp
	@mkdir -p $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDES) -c -o $@ $< -D STD=0

$(NAME): $(OBJS_DIR)/main_42_std.o $(OBJS_DIR)/main_42_ft.o
	@echo "Cooking up executables 🍪..."
	$(CXX) $(CXXFLAGS) $(OBJS_DIR)/main_42_ft.o -o $(FT_NAME) 
	$(CXX) $(CXXFLAGS) $(OBJS_DIR)/main_42_std.o -o $(STD_NAME)

$(NAME2): $(OBJS_DIR)/my_main_std.o $(OBJS_DIR)/my_main_ft.o
	@echo "Cooking up executables 🍪..."
	$(CXX) $(CXXFLAGS) $(OBJS_DIR)/my_main_ft.o -o $(FT_NAME2)
	$(CXX) $(CXXFLAGS) $(OBJS_DIR)/my_main_std.o -o $(STD_NAME2)

clean:
	@rm -rf $(OBJS_DIR)
	@echo "deleting objects"

fclean: clean
	@rm -rf $(FT_NAME) $(FT_NAME2) $(STD_NAME) $(STD_NAME2) 
	@echo "Full Clean"

re: fclean all

.SUFFIXES: .cpp .o .hpp

.PHONY: all clean fclean re
