# The name of the executable.
NAME = container

# The C++ compiler to use.
CXX = c++

# The flags to be used by the compiler.
CXXFLAGS = -Wall -Wextra -Werror -pedantic -std=c++98 -g

# The flags to be used by the linker.
LDFLAGS = -Iinclude

# The source files.
SRCS = main.cpp

# The object files.
OBJS = $(patsubst %.cpp,%.o,$(SRCS))

# The dependency files.
DEPS = $(patsubst %.cpp,%.d,$(SRCS))


# Makes everything ready.
all: $(NAME)

# Creates the executable.
$(NAME): $(OBJ)
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

.PHONY: re fclean clean all

-include $(DEPS)
