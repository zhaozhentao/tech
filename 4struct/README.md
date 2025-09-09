#### 结构数组

与基本类型的数组相同，结构体也可以有数组。

```clike
#include <stdio.h>

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

> 上面的例子中，数组在初始化时候，没有指定数组的长度，但编译器可以根据后面给出的代码，“隐式”计算出数组的长度，C 语言中数组长度是固定，不可以修改的。

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
