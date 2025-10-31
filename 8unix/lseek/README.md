#### 8.4 随机访问 lseek

前面介绍的 read 和 write 函数都是顺序读写，它们会从文件当前位置开始读写。lseek 函数可以改变文件位置，从而实现随机访问。

lseek 函数的声明如下：

```clike
long lseek(int fd, long offset, int origin);
```

回顾一下前面的学习文件读写操作，总是按照顺序的（一直 read 或 write），其实这里隐藏了一个概念：文件位置，以读操作为例，假如没有一次性读完整个文件，
当第二次调用 read 时，其实是从上次调用的 read 结尾的位置开始读的（否则就会一直读到相同的内容了），操作系统在背后存了一个 `文件位置` 
使得我们的读写操作可以有一定的顺序。

使用 lseek 函数，可以改变文件位置，从而实现随机访问。

下面是 lseek 的例子

```clike
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main() {
    int fd;
    char buf[16] = {0};

    fd = open("./test.txt", O_RDONLY);

    // 读取文件，读取完后文件位置会向后移动
    read(fd, buf, 16);

    printf("read:%s\n", buf);

    // 改变文件位置，移动到文件开头
    lseek(fd, 0, SEEK_SET);

    // 再次读取文件，读取到的内容与第一次的相同
    read(fd, buf, 16);

    printf("read:%s\n", buf);

    return 0;
}
```

> lseek 的重要性：如果把文件看作一个巨大的字符数组，使用 lseek 改变文件的位置，就可以快速访问这个数组中任意位置，而不是从头到尾的访问，因为磁盘读取的速度是很慢的。像数据库这种软件就需要使用到 lseek 来高效访问文件。
