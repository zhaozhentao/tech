#### 8.1 文件描述符

在 Unix/Linux 操作系统中，所有的外围设备（包括键盘和显示器）都被看作是文件系统中的文件，所有的输入/输出都要通过读文件或写文件来完成。

```clike
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv) {
    int fd;

    fd = open("/sys/class/leds/orangepi:green:status/brightness", O_WRONLY);

    write(fd, "1", 1);

    close(fd);

    return 0;
}
```

> 开发板演示通过文件点灯

通常情况下，读写文件之前都需要先打开文件，如果操作正常，操作系统会返回一个小的非负整数，该整数称为文件描述符，后续的读写操作都要通过该文件描述符来完成。

> 标准库使用的是 FILE，Unix/Linux 提供的系统调用使用文件描述符，注意这个区别。

```clike
#include <stdio.h>

int main() {
    FILE *fp;

    fp = fopen("/sys/class/leds/orangepi:green:status/brightness", "w");

    putc('1', fp);

    fclose(fp);

    return 0;
}
```

shell 运行一个程序时，会打开三个文件描述符：标准输入（0）、标准输出（1）和标准错误输出（2）。

> 可以在 /proc/进程id/fd 中看到上面提到的这三个文件描述符。

#### 8.2 低级 IO read 和 write

与上一章学习的标准库函数相似，Unix/Linux 提供的系统调用 read 和 write (对应标准库函数 fread 和 fwrite) 是低级的 IO 函数，它们直接操作文件描述符，而不是 FILE 指针。

* read 接收的参数包括: 文件描述符、缓冲区、缓冲区大小，返回读取的字节数。

* write 接收的参数包括: 文件描述符、缓冲区、写入的大小，返回写入的字节数。

下面使用 read 和 write 函数实现另一个 cat 程序，该程序从标准输入读取数据，然后将数据回显到标准输出。

```clike
#include <unistd.h>

int main() {
    long n;
    char buf[1024];

    // 从文件描述符 0 中读取数据，即标准输入
    while ((n = read(0, buf, sizeof buf)) != 0) {
        // 把数据写入文件描述符 1 中，即标准输出
        write(1, buf, n);
    }

    return 0;
}
```

运行程序，以 main.c 文件作为标准输入，程序从标准输入中读取内容并打印。

```bash
$ ./a.out < main.c
```

> 注意上面的程序，因为标准输入和标准输出本来就已经打开，所以程序中没有打开文件的动作。

#### 8.3 open、creat、close 和 unlink

##### open

与标准库函数类似，Unix/Linux 提供 open 函数用于打开文件（对应标准库 fopen）。函数的定义如下。

```clike
// 注意这里和书本的不一致
int open(const char *pathname, int flags);
```

* pathname 是要打开的文件路径。

* flags 是打开文件的方式，例如只读、只写、读写等。常用的标志有：
    * O_RDONLY：只读打开文件。
    * O_WRONLY：只写打开文件。
    * O_RDWR：读写打开文件。
    * O_CREAT：如果文件不存在，则创建文件。
    * O_EXCL：与 O_CREAT 一起使用，如果文件已存在，则返回错误。
    * O_TRUNC：如果文件已存在，清空文件内容。

> 可以通过命令行 man 2 open ，查看 open 函数的说明，看不懂英文可以用 AI 翻译。

##### creat 

creat 函数用于创建一个新文件，函数的定义如下。

```clike
int creat(const char *pathname, mode_t mode);
```

* pathname 是要创建的文件路径。

* mode 是文件的权限模式，例如 0644 表示文件所有者有读写权限，其他用户只有读权限。

##### close

close 函数相对简单，对应标准库函数 fclose。函数的定义如下。

```clike
int close(int fd);
```

下面我们使用前面学到的系统调用来实现一个 cp 命令。

```clike
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
    int f1, f2;
    long n;
    char buf[1024];

    if (argc != 3) {
        printf("请输入两个文件路径\n");
        exit(1);
    }

    // 打开原文件
    f1 = open(argv[1], O_RDONLY);

    if (f1 < 0) {
        printf("打开文件 %s 失败\n", argv[1]);
        exit(1);
    }

    // 创建新文件
    f2 = creat(argv[2], 0666);

    if (f2 < 0) {
        printf("创建文件 %s 失败\n", argv[2]);
        exit(1);
    }

    while ((n = read(f1, buf, sizeof buf)) > 0) {
        // 把原文件的内容复制到新文件中
        write(f2, buf, n);
    }

    close(f1);
    close(f2);

    return 0;
}
```
