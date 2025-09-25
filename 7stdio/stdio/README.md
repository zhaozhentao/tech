#### 7.4 格式化输入 scanf 函数

scanf 格式化输入函数与 printf 格式化输出函数对应，scanf 函数按照指定的格式，将 **标准输入** 保存到其参数中。

##### 例子 1

下面的例子，在程序运行后，输入一个整数，scanf 会把对应的整数保存到 a 中（回顾一下使用指针修改）。

```clike
#include <stdio.h>

int main()
{
  int a;
  
  printf("请输入一个整数：");
  
  scanf("%d", &a);
  
  printf("你输入的整数是：%d\n", a);
  
  return 0;
}
```

##### 例子 2

scanf 碰到某些输入无法与指定格式匹配时，函数将会结束，并返回匹配中的变量数。

```clike
#include <stdio.h>

int main()
{
  int a;
  int b;
  int c;
  int count;

  count = scanf("%d %d %d\n", &a, &b, &c);

  printf("你输入的整数是：%d\n", a);
  printf("你输入的整数是：%d\n", b);
  printf("你输入的整数是：%d\n", c);

  printf("count %d\n", count);

  return 0;
}
```

运行上面的程序，输入 `10 10 u` ，其中 u 是一个字符，scanf 函数会返回 2（表示处理了两个变量），并把 10 和 10 保存到 a 和 b 中。

<img style="width: 400px" src="images/img.png"> 

##### 例子 3

从标准输入接收字符串，scanf 函数不会检查你接收字符串的数组长度，比如下面代码。

```clike
#include <stdio.h>

int main() 
{
  char str[10];
  
  printf("请输入一个字符串：");
  
  scanf("%s", str);
  
  printf("你输入的字符串是：%s\n", str);
  
  return 0;
}
```

运行时候，输入长度大于 10 的字符串，会导致报错，因为长度超出了 str 数组。

<img style="width: 400px" src="images/img_1.png"> 

为了处理上面的长度超出问题，也可以这样处理

```clike
#include <stdio.h>

int main()
{
  char str[10];

  printf("请输入一个字符串：");

  // 指定最大长度
  scanf("%10s", str);

  printf("你输入的字符串是：%s\n", str);

  return 0;
}
```

##### 例子 4

接收多个不同类型数据。

```clike
#include <stdio.h>

int main() 
{
  int year;
  char month[10];
  int day;
  
  printf("请输入日期，格式如 1 Dec 2025\n");
  
  scanf("%d %s %d", &day, month, &year);
  
  printf("你输入的日期是：%d %s %d\n", day, month, year);
  
  return 0;
}
```

运行程序，并按照下图输入，会看到打印的结果。

<img style="width: 400px" src="images/img_2.png"> 

这里需要说明的是：

* 输入数据之间的多个空格，会被忽略，请看上图示例。
* scanf 接收的所有参数，都是指针，因为要直接把值写入到对应的变量。

##### 其他说明

根据经验 scanf 函数在日常开发中，不常用，我们有个大致的了解即可，需要用到时再详细了解。


#### 7.5 文件访问

接下来我们将要学习通过 C 标准库访问文件，文件操作是软件开发中很重要的部分，Linux 也有 `一切都是文件` 的这种说法，
各种硬件外设（比如之前学习的单片机 IO 驱动的 LED），都被包装成了文件。

操作文件，离不开一个重要的结构 FILE，用来记录文件的读写位置等其他一些重要的信息。

接下来介绍的文件操作基本是按照下面的流程：
* 打开文件（fopen）
* 读取文件（getc）
* 关闭文件（fclose）

##### fopen

fopen 函数用于打开文件，返回一个 FILE 结构指针，如果打开文件失败，返回 NULL。函数的定义如下：

```clike
FILE *fopen(const char *filename, const char *mode);
```

参数说明：
* filename 文件名
* mode 文件打开模式

mode 参数可以有如下几种：
* r 只读
* w 只写
* a 追加
* r+ 读写
* w+ 读写
* a+ 读写

##### getc

getc 函数用于读取文件，返回一个字符，如果文件读取完毕，返回 EOF，与前面学习过的 getchar 函数类似。函数的定义如下：

```clike
int getc(FILE *stream);
```

##### fclose

fclose 函数用于关闭文件，函数的定义如下：

```clike
int fclose(FILE *stream);
 ```

因为 Linux 会限制每个进程打开的文件数量，所以在操作完文件后都需要关闭文件，释放资源。

##### 动手实现一个 cat 命令

```clike
#include <stdio.h>
#include <stdlib.h>

// 这里我们第一次使用 main 函数的参数 argc 表示参数个数，argv[] 表示参数数组
int main(int argc, char *argv[]) {
    // 检查命令行参数
    if (argc < 2) {
        printf("用法: %s <文件名>\n", argv[0]);
        return 1;
    }
    
    // 打开文件
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("错误: 无法打开文件 '%s'\n", argv[1]);
        return 1;
    }
    
    // 读取文件内容并输出到标准输出
    int ch;
    while ((ch = getc(file)) != EOF) {
        putchar(ch);
    }
    
    // 关闭文件
    fclose(file);
    
    return 0;
}
```

编译并运行下面的命令，可以看到 main.c 文件的内容被打印出来。

```shell
$ ./a.out main.c
```
