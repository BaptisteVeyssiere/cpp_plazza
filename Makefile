##
## Makefile for 42sh in /home/VEYSSI_B/rendu/Programmation_Shell/test/test_42tree
##
## Made by Baptiste veyssiere
## Login   <VEYSSI_B@epitech.net>
##
## Started on  Wed May 18 21:26:30 2016 Baptiste veyssiere
##

NAME	= plazza

RM	= rm -f

CXX	= g++

MKDIR	= mkdir -p

SRC	= src/main.cpp \
	src/Parser.cpp \
	src/Process.cpp \
	src/Mutex.cpp \
	src/Main_Process.cpp \
	src/Named_pipe.cpp \
	src/t_pool.cpp \
	src/CondVar.cpp \
	src/Thread.cpp \
	src/Finder.cpp \
	src/Decrypt.cpp

SRCUI	= src_ui/main.cpp \
	src_ui/Parser.cpp \
	src_ui/Process.cpp \
	src_ui/Mutex.cpp \
	src_ui/Main_Process.cpp \
	src_ui/Named_pipe.cpp \
	src_ui/t_pool.cpp \
	src_ui/CondVar.cpp \
	src_ui/ui.cpp \
	src_ui/Finder.cpp \
	src_ui/Decrypt.cpp \
	src_ui/Thread.cpp

SRCDIR	= src

SRCUIDIR	= src_ui

OBJDIR	= obj

OBJUIDIR	= obj_ui

OBJ	= $(SRC:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

OBJUI	= $(SRCUI:$(SRCUIDIR)/%.cpp=$(OBJUIDIR)/%.o)

LDFLAGS	= -pthread

LDFLAGSUI	= -pthread -lSDL -lSDL_ttf

CXXFLAGS	= -Iinclude -W -Wextra -Wall -Wpointer-arith -Wcast-qual -Wcast-align -Wconversion -Wdouble-promotion -Wold-style-cast -Wfloat-equal -Woverloaded-virtual -Wshadow -Weffc++ -Werror -Wfatal-errors

$(NAME): $(OBJ)
	@$(CXX) $(LDFLAGS) -o $(NAME) $(OBJ)
	@echo "Linking complete!"

ui: $(OBJUI)
	@$(CXX) $(LDFLAGSUI) -o $(NAME) $(OBJUI)
	@echo "Linking complete!"

$(OBJ): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@$(MKDIR) $(OBJDIR)
	@$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

$(OBJUI): $(OBJUIDIR)/%.o : $(SRCUIDIR)/%.cpp
	@$(MKDIR) $(OBJUIDIR)
	@$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

all: $(NAME) ui

clean:
	@$(RM) $(OBJ)
	@$(RM) $(OBJUI)
	@echo "Cleanup complete!"

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(LIBNAME)

re: fclean all

.PHONY: all clean fclean re ui
