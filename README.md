## 开始使用C语言

### 1.1 简介

C语言是一种通用的、过程式的计算机编程语言，支持系统编程和底层硬件操作。它由丹尼斯·里奇（Dennis Ritchie）于20世纪70年代初在贝尔实验室开发，最初是为了编写Unix操作系统。

> 推荐阅读: 《Unix 传奇》了解更多 Unix 操作系统和 C 语言起源。

### 1.2 第一个程序

我们将从一个简单的例子开始学习C语言。这个程序会在屏幕上打印一行文本：“Hello, World”。这是所有编程语言中最经典的入门示例之一。

```CLang
#include <stdio.h>

int main() { 
    printf("Hello, World\n"); 
    return 0;
}
```

### 1.3 编译与运行

要运行这段代码，你需要：
- 使用文本编辑器将代码保存为`.c`文件（例如`hello.c`）
- 使用C编译器（如gcc）编译该文件：`gcc hello.c -o hello`
- 运行生成的可执行文件：`./hello`

这将输出：

```shell
Hello, World
```
