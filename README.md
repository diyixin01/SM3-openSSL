# SM3-openSSL
SM3 from openssl


# openssl简介
openssl是一个安全套接字层密码库，囊括主要的密码算法、常用密钥、证书封装管理功能及实现ssl协议。OpenSSL整个软件包大概可以分成三个主要的功能部分：SSL协议库libssl、应用程序命令工具以及密码算法库libcrypto。

# 运行简介

在build/中，有ELF可执行文件a.out，linux下可直接执行，速度在200w+/s

# 实现简介

openssl中，有关SM3的实现是套用了Hash函数的模板，即MD结构的函数，使用宏函数来减少函数调用。

其中有关SM3的个性函数都在sm3local.h中给了声明，尤其是SM3中，对于CF函数的各种小操作，都定义成了宏函数。

openssl并没有使用simd指令去尝试并行SM3，而是选择减少中间变量，充分利用函数流水的方式，将展开利用到了极致。

我们知道SM3算法中，需要对64字节的一个block进行消息拓展，但是宏观来看，其实就是对原来消息的线性变化，同时ABCDEFGH等寄存器，也是不断的经历线性变换。比如每轮变化中D=C（只是示例，随便写的）,其实不用真的进行赋值操作，只需要在下一轮压缩时，改变两个寄存器的顺序即可，也就是手搓位置变换，宏函数代替移位变换，免除了很多局部变量和指令，大大提高了效率


