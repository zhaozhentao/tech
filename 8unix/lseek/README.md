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

#### 8.6 目录列表

在 Unix/Linux 系统中，目录是一个特殊的文件，目录中的条目被保存在目录文件中。目录文件本身是一个文件，目录文件保存的条目被保存在目录项中。

下面我们来编写一个程序，读取目录下的所有条目（文件/子目录），通过下面例子认识一下关于目录操作的系统调用，(类似于 ls 功能)。

```clike
#include <stdio.h>
#include <dirent.h>  // 目录操作相关函数
#include <string.h>  // 用于字符串处理

// 读取并打印目录下的所有条目（文件/子目录）
void read_directory(const char *dir_path) {
    // 打开目录，返回目录流指针
    DIR *dir = opendir(dir_path);
    if (dir == NULL) {
        perror("无法打开目录");  // 出错时打印错误信息
        return;
    }

    struct dirent *entry;  // 用于存储目录条目信息
    // 循环读取目录中的每个条目
    while ((entry = readdir(dir)) != NULL) {
        // 跳过 "."（当前目录）和 ".."（上级目录）
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // 打印条目名称
        printf("名称: %s\t", entry->d_name);

        // 根据条目的类型进行区分（可选）
        switch (entry->d_type) {
            case DT_DIR:   // 子目录
                printf("类型: 目录\n");
                break;
            case DT_REG:   // 普通文件
                printf("类型: 普通文件\n");
                break;
            case DT_LNK:   // 符号链接
                printf("类型: 符号链接\n");
                break;
            default:       // 其他类型（如设备文件等）
                printf("类型: 其他\n");
                break;
        }
    }

    // 关闭目录流
    closedir(dir);
}

int main() {
    const char *dir_path = ".";
    
    printf("读取目录: %s\n", dir_path);
    
    read_directory(dir_path);
    
    return 0;
}
```
