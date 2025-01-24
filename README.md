## 开始使用C语言

### 1.1 简介

C语言是一种通用的、过程式的计算机编程语言，支持系统编程和底层硬件操作。它由丹尼斯·里奇（Dennis Ritchie）于20世纪70年代初在贝尔实验室开发，最初是为了编写Unix操作系统。

> 推荐阅读: 《Unix 传奇》了解更多 Unix 操作系统和 C 语言起源。

### 1.2 第一个程序

我们将从一个简单的例子开始学习C语言。这个程序会在屏幕上打印一行文本：“Hello, World”。这是所有编程语言中最经典的入门示例之一。

```clike
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

### 练习

尝试删除掉代码中的一部分，看看编译器会报什么错? 尝试通过搜索，看看报错的含义。

### 2.1 变量与算术表达式

C 语言中，所有变量都需要先声明后使用。**声明** 用于说明变量的类型，由类型名和变量名组成，下面的例子表示声明一个类型为 int，名字为 rmb 的变量。

```clike
int rmb;
```

> 后面会讲解更多不同的类型。

下面是一个包含变量声明和算术运算的简单小程序。

```clike
#include <stdio.h>

/*
 * 下面程序打印人民币和美元的转换表，假如 1 美元等于 7 人民币
 */
int main() {
    // 声明两个变量 rmb 代表人民币，dollar 表示美元
    int rmb, dollar;
    int upper;
    
    dollar = 1;
    upper = 10;
    
    /*
     * 当 dollar 小于等于 upper 时，执行 while {} 中的代码
     * 我们要输出的是 1 美元等于人民币，2 美元等于人民币，...，10 美元等于多少人民币。
     * 因为 upper 是 10，所以最多输出到 10 美元。
     */
    while (dollar <= upper) {
        // 计算 dollar 美元对应的人民币
        rmb = dollar * 7;
        
        // 下面的两个 %d 会被替换为两个整数，第一个会被替换为 dollar 的值，第二个会被替换为 rmb 的值
        printf("%d 美元可以兑换 %d 人民币\n", dollar, rmb);
        
        // dollar 的值加 1，准备下一个循环
        dollar = dollar + 1;
    }
    
    // 表示程序正常结束
    return 0;
}
```

上面的程序中
* `int rmb, dollar;` 声明了两个变量，类型为 int
* `dollar = 1;` 是一个赋值语句，将 1 赋值给 dollar 变量
* `rmb = dollar * 7;` 是一个算术表达式，按照 1 美元等于 7 人民币，计算 dollar 美元等于多少 rmb 人民币

程序中的 `/**/` 和 `//` 是注释，应该要养成良好的习惯，在程序中添加适当的注释，这样当别人或你自己阅读代码时，就会很快知道代码的意图。

> 上面的 %d 会被替换成整数，如果需要被替换成其他类型，比如小数呢？从书中找找答案。

反复练习输入上面代码，提升输入代码的速度和熟练度，注意在代码中加入合适的空格，优秀的软件工程师会时刻关注代码的工整。下面是一个反例，不注意空格的使用，代码挤在一起，也不注意代码的对齐。

```clike
#include <stdio.h>

int main(){
    int rmb,dollar;
    int upper;
    
    dollar=1;
    upper=10;
    
    while(dollar<=upper){
        rmb=dollar*7;
        
        printf("%d美元可以兑换%d人民币\n",dollar,rmb);
        
    dollar=dollar+1;
    }
    
    return 0;
}
```
