CC = g++
CPPFLAGS = -std=c++11 -Wall -g -Iinclude
SRCS = src/main.cpp src/blockEntity.cpp src/movableEntity.cpp src/hollow.cpp
SRCS_TST = tests/main_test.cpp src/blockEntity.cpp src/movableEntity.cpp src/hollow.cpp
OBJS = $(SRCS:.cpp=.o)
OBJS_TST = $(SRCS_TST:.cpp=.o)
DEPS = $(OBJS:.o=.d)
DEPS_TST = $(OBJS_TST:.o=.d)

ifneq ($(OS), Windows_NT)
RM = rm -f
ifeq ($(shell uname), Linux)
# Enable AddressSanitizer and UndefinedBehaviorSanitizer on Linux
CPPFLAGS += -fsanitize=address,undefined
endif
else
RM = del
endif

game: $(OBJS)
	$(CC) -o $@ $^ $(CPPFLAGS)

game_test: $(OBJS_TST)
	$(CC) -o $@ $^ $(CPPFLAGS)

# To include the .d dependency files
-include $(DEPS)
-include $(DEPS_TST)

src/%.o: src/%.cpp
	$(CC) -MMD -MP -c -o $@ $< $(CPPFLAGS)

tests/%.o: tests/%.cpp
	$(CC) -MMD -MP -c -o $@ $< $(CPPFLAGS)

clean:
	$(RM) src\*.o src\*.d tests\*.o tests\*.d game.exe game_test.exe