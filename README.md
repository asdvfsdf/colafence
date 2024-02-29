# colafence

## 对目前工作的认识

1. 在当前机器下(Linux cola-virtual-machine 6.5.0-21-generic #21~22.04.1-Ubuntu SMP PREEMPT_DYNAMIC Fri Feb  9 13:32:52 UTC 2 x86_64 x86_64 x86_64 GNU/Linux)制作一个内存分配器(感觉要写理清 linux 的内存分配，心里大致有个数)

2. 实现在用户申请空间时一个周期使用一次我制作的内存分配器,这通过动态共享库来包装 malloc 来实现

3. 分析（不做那么长的计划 2.29）

## 进度

## 参考资料

## 目前可以想到的问题

1. 我们要观测的是用户态应用，kfence 的原理就是在内存分配阶段周期性的使用自己的内存分配器分配特殊的块，我该如何让用户态的 malloc 使用我的内存分配器呢？

在Linux，如果你将一个动态库文件的路径设置在环境变量LD_PRELOAD中，这个库文件会优先被加载。利用这个特性可以保证我们一会在shell中运行程序时使用我们实现的malloc(),free(),calloc()和realloc()。

这个问题解决了（https://stackoverflow.com/questions/17803456/an-alternative-for-the-deprecated-malloc-hook-functionality-of-glibc）

2. 后面可能还要考虑多线程
