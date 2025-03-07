### 第二章

#### 2.1 变量名

1. 变量名可以由字母、数字、下划线组成，但是不能以数字开头。
2. 变量名不能包含空格，比如 `my name` 是不合法的变量名。
3. 变量名区分大小写，比如 `name` 和 `Name` 是两个不同的变量。
4. 变量名不能使用关键字，比如 `if`、`for`、`while` 等。

#### 2.2 数据类型及长度

C 语言只提供了以下几种数据类型：

1. char 字符型，长度为 1 字节。
2. int 整型。
3. float 单精度浮点型。
4. double 双精度浮点型。

##### 课本练习 2-1

```clike
#include <stdio.h>
#include <limits.h>

int main() {
    printf("数据类型取值范围：\n\n");
    
    /* 有符号类型 */
    printf("有符号类型：\n");
    printf("signed char:\t%d 到 %d\n", SCHAR_MIN, SCHAR_MAX);
    printf("signed short:\t%d 到 %d\n", SHRT_MIN, SHRT_MAX);
    printf("signed int:\t%d 到 %d\n", INT_MIN, INT_MAX);
    printf("signed long:\t%ld 到 %ld\n\n", LONG_MIN, LONG_MAX);
    
    /* 无符号类型 */
    printf("无符号类型：\n");
    printf("unsigned char:\t0 到 %u\n", UCHAR_MAX);
    printf("unsigned short:\t0 到 %u\n", USHRT_MAX);
    printf("unsigned int:\t0 到 %u\n", UINT_MAX);
    printf("unsigned long:\t0 到 %lu\n", ULONG_MAX);
    
    return 0;
}
```

#### 2.3 常量

1. 数值型常量，如 1，2，3 等，还有浮点型常量如 1.1 或 1.1f (没有后缀的表示 double，有 f  后缀的表示 float)。
2. 字符常量，如 'x'，注意和双引号 "x" 区别开来， "x" 是字符串，字符常量实际上也是一个整数。
3. 字符串常量。
4. 枚举常量。

下面的程序可以看到字符常量的本质：

```clike
#include <stdio.h>

int main() {
    char c = 'x';
    printf("字符常量 'x' 的值为 %d\n", c);
    return 0;
}
```

> 也可以查看查看 ASCII 码表 https://www.runoob.com/w3cnote/ascii.html，看看 'x' 对应的整数值是多少。 

##### 练习

理解书中 strlen 计算字符串长度的原理，理解后尝试自己实现一遍。

枚举常量是另一种类型的常量。例如：

```clike
enum color {
    RED,
    GREEN,
    BLUE
};
```

没有显式说明的情况下，枚举常量的值从 0 开始，依次递增。下面是一个示例程序：

```clike
#include <stdio.h>

enum color {
    RED,
    GREEN,
    BLUE
};

enum weekday {
    SUNDAY,     // 0
    MONDAY,     // 1
    TUESDAY=5,  // 显式赋值为5
    WEDNESDAY   // 会自动递增为6
};

int main() {
    printf("颜色枚举值：\n");
    printf("RED = %d\n", RED);      // 0
    printf("GREEN = %d\n", GREEN);  // 1
    printf("BLUE = %d\n\n", BLUE);  // 2

    printf("星期枚举值：\n");
    printf("SUNDAY = %d\n", SUNDAY);     // 0
    printf("MONDAY = %d\n", MONDAY);     // 1
    printf("TUESDAY = %d\n", TUESDAY);   // 5
    printf("WEDNESDAY = %d\n", WEDNESDAY); // 6
    
    return 0;
}
```

#### 2.4 声明

所有变量都需要先声明，后使用。一般有下面两种声明方式：

```clike
// 第一种，相同类型的变量可以放在一行声明
int lower, upper;

// 或下面这种
int lower;
int uppper;
```

还可以在声明变量的时候初始化：

```clike
int lower = 0;
```

> 注意：在一个函数中，一个变量只能声明一次。

##### 练习

尝试一下，在函数中声明同一个变量多次，编译看看会发生什么事？

#### 2.5 算术运算符

C 语言中算术运算符包括：
1. `+` 加法运算符
2. `-` 减法运算符
3. `*` 乘法运算符
4. `/` 除法运算符
5. `%` 取模（求余）运算符

需要注意的是：

- 当两个整数相除时，结果会自动舍去小数部分，例如 `5/2` 的结果是 `2` 而不是 `2.5`
- 取模运算符 `%` 只能用于整数运算
- 运算符的优先级：`*`、`/`、`%` 高于 `+`、`-`

##### 练习

编写一个函数，参数是年份，判断这个年份是否是闰年，结合课本中 2.5 算术运算符相关代码。
