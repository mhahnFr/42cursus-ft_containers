# The name of the executable.
NAME = container.exe

# The C++ compiler to use.
CXX = c++

# The flags to be used by the compiler.
CXXFLAGS = -Wall -Wextra -Werror -pedantic -std=c++98 -Iinclude -g -fsanitize=address

# The flags to be used by the linker.
LDFLAGS = -fsanitize=address

# The source files.
SRCS = main4.cpp

# The object files.
OBJS = $(patsubst %.cpp,%.o,$(SRCS))

# The dependency files.
DEPS = $(patsubst %.cpp,%.d,$(SRCS))


# Makes everything ready.
all: $(NAME)

# Creates the executable.
$(NAME): $(OBJS)
	$(CXX) $(LDFLAGS) -o $(NAME) $(OBJS)

# Compiles a source file individually.
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -MMD -MP -c -o $@ $<

# Cleans the repository.
clean:
	$(RM) $(OBJS) $(DEPS)

# Removes all files created by this file.
fclean: clean
	$(RM) $(NAME)

# Removes everything and compiles everything.
re: fclean
	$(MAKE) all

# The rules that do not belong to a file.
.PHONY: re fclean clean all

-include $(DEPS)
