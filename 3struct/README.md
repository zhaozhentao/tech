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
