#### 6.3 结构数组

与基本类型的数组相同，结构体也可以有数组。

```clike
#include <stdio.h>

// 定义结构体包含的字段
struct student {
        char* name;
        int height;
};

int main() {
        // 声明并初始化一个学生结构的数组
        struct student students[] = {
                {"小明", 10},
                {"小黄", 11}
        };

        printf("第 0 个学生是: %s, 身高为 %d\n", students[0].name, students[0].height);

        printf("第 1 个学生是: %s, 身高为 %d\n", students[1].name, students[1].height);

        return 0;
}
```

> 知识点回顾，上面的例子中，数组在初始化时候，没有指定数组的长度。这是因为编译器可以根据后面给出的代码，“隐式”计算出数组的长度。C 语言中数组长度是固定，不可以修改的。

上面的例子也可以改写成下面这样，先声明不初始化（此时需要先指定数组长度，否则编译器不知道数组长度应该是多少）。

```clike
#include <stdio.h>

struct student {
        char* name;
        int height;
};

int main() {
        // 声明一个学生数组，此时已经分配好了内存
        struct student students[2];

        students[0].name = "小明";
        students[0].height = 10;
        students[1].name = "小黄";
        students[1].height = 11;

        printf("第 0 个学生是: %s, 身高为 %d\n", students[0].name, students[0].height);

        printf("第 1 个学生是: %s, 身高为 %d\n", students[1].name, students[1].height);

        return 0;
}
```

##### 小结

结构体数组定义的语法为。

```clike
struct 结构体名 数组名[数组长度];
```

引用数组中的元素语法和基本类型的数组一样。

```clike
数组名[元素编号];
```

#### 6.4 结构体指针

##### 6.4.1 结构体指针的声明

与基本类型的指针一样，结构体也有相应的指针，可以看到语法其实是一致的。

```clike
struct demo {
        int x;
        int y;
}; 

int main() {
        // 基本类型指针的声明
        int *p;

        // 结构体指针的声明
        struct demo *dp;

        return 0;
}
```

##### 6.4.2 结构体指针的使用

下面的例子，我们定义一个矩形(rectangle)结构体，其中 x 和 y 是矩形的长宽，m 保存矩形的面积，我们编写一个函数，接收一个矩形结构，计算其面积并保存到 m 中。

```clike
#include <stdio.h>

struct rectangle {
        int x;
        int y;
        int m;
}; 

void calc(struct rectangle* p) {
        // 面积 = 长 * 宽
        p->m = p->x * p->y;
}

int main() {
        // 声明一个矩形 x = 1, y = 2, m = 0
        struct rectangle r = {1, 2, 0};

        calc(&r);

        printf("m = %d\n", r.m);

        return 0;
}
```

上面的例子涉及几个语法点：
1. 结构体指针声明(在函数参数列表中) struct rectangle* p
2. 结构体的取地址 &r (包括基本类型变量，所有取址语法都相同)
3. 通过结构体指针访问成员变量，p->x (这里和通过结构体变量访问成员变量不一样)

> 练习：定义一个正方体的结构，成员变量需要包含：边长和周长，仿照上面的例子，编写一个函数计算出正方体的周长（可任意设置一个边长）。
