#!/bin/bash

# 提示用户输入编译选项和 CFLAGS
CC              :=
FLAGS           :=
LIB_FLAG        :=

# 指定代码文件的源文件和输出文件
CODE_SOURCE     :=
CODE_OUTPUT     :=

# 指定动态链接库的源文件和输出文件
COLAFENCE_LIB="libcolafence.so"


# 检查动态链接库是否编译成功
if [ -f $COLAFENCE_LIB ]; then

    echo "Shared library compiled successfully."

    # 编译指定的代码文件并链接到动态链接库
    echo "Compiling code with shared library..."
    $CC $FLAGS -o $CODE_OUTPUT $CODE_SOURCE

    # 检查代码文件是否编译成功
    if [ $? -eq 0 ]; then
        echo "Code compiled and linked successfully with shared library."
    else
        echo "Error: Code compilation failed."
    fi
else
    echo "Error: Shared library not exists."
fi
