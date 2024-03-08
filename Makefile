# 提示用户输入编译选项和 CFLAGS
CC := gcc
FLAGS :=
LIB_FLAG := -Lsharedlib -lcolafence

# 指定代码文件的源文件和输出文件
CODE_SOURCE := $(wildcard ./code/*.c)
CODE_OUTPUT := ./output/testfile

# 指定动态链接库的源文件和输出文件
COLAFENCE_LIB := libcolafence.so

all: $(CODE_OUTPUT)

$(CODE_OUTPUT): $(CODE_SOURCE)
	$(CC) $(CODE_SOURCE) $(FLAGS) $(LIB_FLAG) -o $(CODE_OUTPUT)

.PHONY: clean

clean:
	rm -f $(CODE_OUTPUT)
	make clean -C sharedlib

test:
	make -C sharedlib
	make lib -C sharedlib
	make
	echo ""
	./output/testfile