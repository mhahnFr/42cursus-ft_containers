# The name of the executable.
NAME = container.exe

# The name of the ft executable
FT_NAME = ft_$(NAME)

# The name of the std executable.
STD_NAME = std_$(NAME)

# The C++ compiler to use.
CXX = c++

# A random value used as shared seed for the two executables.
RAND := $(shell echo $$RANDOM)

# The flags to be used by the compiler.
CXXFLAGS = -Wall -Wextra -Werror -pedantic -std=c++98 -Iinclude -DSEED=$(RAND) -Ofast

# The flags to be used by the linker.
LDFLAGS =

# The source files.
SRCS = main.cpp

# The ft object files.
FT_OBJS = $(patsubst %.cpp,%.ft.o,$(SRCS))

# The std object files.
STD_OBJS = $(patsubst %.cpp,%.std.o,$(SRCS))

# The dependency files.
DEPS = $(patsubst %.cpp,%.std.d,$(SRCS)) $(patsubst %.cpp,%.ft.d,$(SRCS))


# Runs the tests.
run: all
	clear
	@printf "time \033[33;1m$(STD_NAME)\033[0m:\n"
	@time ./$(STD_NAME) > std.log
	@printf "\ntime \033[34;1m$(FT_NAME)\033[0m:\n"
	@time ./$(FT_NAME) > ft.log
	@printf "\ndiff \033[34;1mft\033[0m \033[33;1mstd\033[0m:\n"
	@diff ft.log std.log
	@printf "\n------\n"

# Makes everything ready.
all: $(FT_NAME) $(STD_NAME)

# Creates the ft executable.
$(FT_NAME): $(FT_OBJS)
	$(CXX) $(LDFLAGS) -o $(FT_NAME) $(FT_OBJS)

# Creates the std executable.
$(STD_NAME): $(STD_OBJS)
	$(CXX) $(LDFLAGS) -o $(STD_NAME) $(STD_OBJS)

# Compiles a source file individually.
%.ft.o: %.cpp
	$(CXX) $(CXXFLAGS) -DNS=ft -MMD -MP -c -o $@ $<

%.std.o: %.cpp
	$(CXX) $(CXXFLAGS) -DNS=std -MMD -MP -c -o $@ $<

# Cleans the repository.
clean:
	$(RM) $(FT_OBJS) $(STD_OBJS) $(DEPS) ft.log std.log

# Removes all files created by this file.
fclean: clean
	$(RM) $(FT_NAME) $(STD_NAME)

# Removes everything and compiles everything.
re: fclean
	$(MAKE) all

# The rules that do not belong to a file.
.PHONY: re fclean clean all run

-include $(DEPS)
