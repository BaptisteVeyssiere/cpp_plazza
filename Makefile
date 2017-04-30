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

CXX	= g++ -g

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

SRCCIPHER	= src_cipher/main.cpp \
	src_cipher/Parser.cpp \
	src_cipher/Process.cpp \
	src_cipher/Mutex.cpp \
	src_cipher/Main_Process.cpp \
	src_cipher/Named_pipe.cpp \
	src_cipher/t_pool.cpp \
	src_cipher/CondVar.cpp \
	src_cipher/Thread.cpp \
	src_cipher/Finder.cpp \
	src_cipher/Decrypt.cpp \
	src_cipher/ui.cpp

SRCDIR	= src

SRCUIDIR	= src_ui

SRCCIPHERDIR	= src_cipher

OBJDIR	= obj

OBJUIDIR	= obj_ui

OBJCIPHERDIR	= obj_cipher

OBJ	= $(SRC:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

OBJUI	= $(SRCUI:$(SRCUIDIR)/%.cpp=$(OBJUIDIR)/%.o)

OBJCIPHER	= $(SRCCIPHER:$(SRCCIPHERDIR)/%.cpp=$(OBJCIPHERDIR)/%.o)

LDFLAGS	= -pthread

LDFLAGSUI	= -pthread -lSDL -lSDL_ttf

CXXFLAGS	= -Iinclude -W -Wextra -Wall -Wpointer-arith -Wcast-qual -Wcast-align -Wconversion -Wdouble-promotion -Wold-style-cast -Wfloat-equal -Woverloaded-virtual -Wshadow -Weffc++ -Werror -Wfatal-errors

$(NAME): $(OBJ)
	@$(CXX) $(LDFLAGS) -o $(NAME) $(OBJ)
	@echo "Linking complete!"

ui: $(OBJUI)
	@$(CXX) $(LDFLAGSUI) -o $(NAME) $(OBJUI)
	@echo "Linking complete!"

cipher: $(OBJCIPHER)
	@$(CXX) $(LDFLAGSUI) -o $(NAME) $(OBJCIPHER)
	@echo "Linking complete!"

$(OBJ): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@$(MKDIR) $(OBJDIR)
	@$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

$(OBJUI): $(OBJUIDIR)/%.o : $(SRCUIDIR)/%.cpp
	@$(MKDIR) $(OBJUIDIR)
	@$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

$(OBJCIPHER): $(OBJCIPHERDIR)/%.o : $(SRCCIPHERDIR)/%.cpp
	@$(MKDIR) $(OBJCIPHERDIR)
	@$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

all: $(NAME)

clean:
	@$(RM) $(OBJ)
	@$(RM) $(OBJUI)
	@$(RM) $(OBJCIPHER)
	@echo "Cleanup complete!"

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(LIBNAME)

re: fclean all

.PHONY: all clean fclean re ui cipher
