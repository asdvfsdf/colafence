# colafence

## USERAGE

1. 将您的工作代码放至 code 目录下
2. 在 sharelib 目录下执行 make，这会生成一个 .so 动态链接库
3. 在根目录下执行 make，这将会使得 .so 动态链接库与您在 .code 目录下的代码一同编译
5. 设置好 ANALYSIS 变量，其将是分析文件生成的目录，最好设置为绝对路径
6. 执行您的程序，会根据您的程序的 pid 在 ANALYSIS 下生成分析文件，文件名为您程序运行时的 pid
7. 目前的 Makefile 相对来说较为简单，您可以根据您代码的实际情况修改 Makefile