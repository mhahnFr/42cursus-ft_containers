# The name of the executable.
NAME = container.exe

# The name of the ft executable
FT_NAME = ft_$(NAME)

# The name of the std executable.
STD_NAME = std_$(NAME)

# The C++ compiler to use.
CXX = c++

# The flags to be used by the compiler.
CXXFLAGS = -Wall -Wextra -Werror -pedantic -std=c++98 -Iinclude -g -fsanitize=address

# The flags to be used by the linker.
LDFLAGS = -fsanitize=address

# The source files.
SRCS = main.cpp

# The object files.
OBJS = $(patsubst %.cpp,%.o,$(SRCS))

# The dependency files.
DEPS = $(patsubst %.cpp,%.d,$(SRCS))


# Runs the tests.
run: all
	clear
	@printf "time \033[33;1m$(STD_NAME)\033[0m:\n"
	@time ./$(STD_NAME) > std
	@printf "\ntime \033[34;1m$(FT_NAME)\033[0m:\n"
	@time ./$(FT_NAME) > ft
	@printf "\ndiff \033[34;1mft\033[0m \033[33;1mstd\033[0m:\n"
	@diff ft std
	@printf "\n------\n"

# Makes everything ready.
all: clean
	$(MAKE) $(FT_NAME)
	$(MAKE) clean
	$(MAKE) $(STD_NAME)

# Creates the ft executable.
$(FT_NAME): CXXFLAGS += -DNS=ft
$(FT_NAME): $(OBJS)
	$(CXX) $(LDFLAGS) -o $(FT_NAME) $(OBJS)

# Creates the std executable.
$(STD_NAME): CXXFLAGS += -DNS=std
$(STD_NAME): $(OBJS)
	$(CXX) $(LDFLAGS) -o $(STD_NAME) $(OBJS)

# Compiles a source file individually.
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -MMD -MP -c -o $@ $<

# Cleans the repository.
clean:
	$(RM) $(OBJS) $(DEPS) ft std

# Removes all files created by this file.
fclean: clean
	$(RM) $(FT_NAME) $(STD_NAME)

# Removes everything and compiles everything.
re: fclean
	$(MAKE) all

# The rules that do not belong to a file.
.PHONY: re fclean clean all run

-include $(DEPS)
