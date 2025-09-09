#### 结构

结构是一个或多个变量的集合，这些变量可以是不同的类型，为了方便而将这些变量组织在一个名字之下。比如，描述一个学生可以有多个维度：姓名，身高，体重，性别。

```clike
struct student {
        char* name;  // 姓名
        int height;  // 身高
        int weight;  // 体重
        int sex;     // 性别
};
```

结构，可以让程序变得容易理解，减少分开定义多个变量。

##### 1. 结构的基本知识

###### 1.1 结构的定义

还是以学生这种结构为例，下面的代码包含了几个部分

1. struct 关键字，表明这是一个结构体
2. student，为结构命名，有了结构的名字，就可以用该名字创建变量。
3. 结构体中的各个属性（也叫做成员变量）。

```clike
struct student {
        char* name;  // 姓名
        int height;  // 身高
        int weight;  // 体重
        int sex;     // 性别
};
```

###### 1.2 使用结构体创建变量

有了上面的结构定义，我们就可以用来创建具体的变量（就好像有了 int 类型后，就可以用 int 创建具体的整型变量）。

```clike
// 定义一个学生 lilei 和 tom
struct student lilei, tom;

// 就像使用 int 创建变量 x 和 y
int x, y;
```

声明结构体变量，同时初始化。

```clike
// 创建变量的时候同时初始化
struct student lilei = {"hi", 1, 2, 3};

// 类似创建 int 变量时初始化
int a = 1;
```

###### 1.3 引用成员变量

有了前面的结构体变量声明后，就可以使用结构体变量以及它的成员变量。

通过 `结构体变量.成员变量` 就可以引用结构体变量中的成员变量。

```clike
struct student lilei = {"hi", 1, 2, 3};

printf("name: %s, height: %d, weight", lilei.name, lilei.height, lilei.weight);
```

###### 1.4 对比

为什么要有结构体这种类型？假如没有结构体，我们需要描述两个学生 lilei 和 tom，他们各自的姓名、身高、体重、性别，就会出现类似下面的代码。

```clike
char* lileiName;
int lileiHeight;
int lileiWeight;
int lileiSex;

char* tomName;
int tomHeight;
int tomWeight;
int tomSex;
```

如果没有结构体，就会出现上面这种，大量重复的代码，非常影响编码，影响效率。

##### 2. 结构与函数

了解如何定义结构体和声明结构体变量后，就可以继续学习一下结构体是如何应用在函数中的，主要包括：作为函数参数、作为函数的返回值。

###### 2.1 结构体作为返回值

首先看看作为返回值时的例子，下面的例子中，函数的返回值类型为 `struct point`，表示函数将会返回一个结构体变量。

```clike
#include <stdio.h>

struct point {
        int x;
        int y;
};

// 返回的类型是 point
struct point makePoint(int x, int y) {
        struct point temp;
        temp.x = x;
        temp.y = y;
        return temp;
}

int main() {
        // 声明并初始化一个 point 类型的变量
        struct point p = makePoint(1, 2);

        printf("p.x = %d, p.y = %d\n", p.x, p.y);

        return 0;
}
```

###### 2.2 结构体作为参数

结构体作为参数时，语法如下（和基本类型变量的定义没有太大区别）。

```clike
#include <stdio.h>

struct point {
        int x;
        int y;
};

// 返回的类型是 point
struct point makePoint(struct point o) {
        struct point temp;
        temp.x = o.x;
        temp.y = o.y;
        return temp;
}

int main() {
        // 直接声明和初始化一个 point 结构体变量
        struct point p1 = {1, 2};

        struct point p;
        
        p = makePoint(p1);

        printf("p.x = %d, p.y = %d\n", p.x, p.y);

        return 0;
}
```

###### 2.3 结构体的传递

结构体作为参数或作为返回值传递时，采用的是值传递的方式，即创建出新的结构体变量，然后复制每个成员变量，如果结构体成员变量数量很大时，这样的传递效率会很低。

从下面代码可以看到，返回的 temp 结构体变量和 main 函数中的变量所在的内存地址不一样，他们是两个不同的变量。

> 理解这一点，对写出高性能程序很有帮助。

```clike
#include <stdio.h>

struct point {
        int x;
        int y;
};

// 返回的类型是 point

// struct point o
// o.x = p1.x
// o.y = p1.y
struct point makePoint(struct point o) {
        struct point temp;

        temp.x = o.x;
        temp.y = o.y;

        printf("makePoint 中的 temp 地址是 %p\n", &temp);

        return temp;
}

int main() {
        struct point p1 = {1, 2};

        // 声明并初始化一个 point 类型的变量
        struct point p;

        // 1. p1 作为运行 makePoint 函数参数
        // 2. 跳转到 makePoint 函数，然后需要先生成参数列表中的 o 变量
        // 3. 对 makePoint 函数中的 o 变量进行初始化 o.x = p1.x, o.y = p1.y
        p = makePoint(p1);

        printf("main 中的 p 地址是 %p\n", &p);

        return 0;
}
```

练习；尝试编写代码说明一下，作为参数传递时，也是采用了“复制的”方式。

###### 2.4 结构体指针

如果在函数调用时，传递的结构体很大，使用指针方式效率会更高。

```clike
#include <stdio.h>

struct point {
        int x;
        int y;
};

void printPoint(struct point * p) {
        // 与直接通过结构体变量访问成员变量不同，通过指针访问需要使用 -> 符号
        printf("x = %d, y = %d\n", p->x, p->y);
}

int main() {
        struct point p = {1, 2};

        printPoint(&p);

        return 0;
}
```

