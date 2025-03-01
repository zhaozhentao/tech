### 1.7 函数

在 C 语言中，函数是程序中可重复使用的代码块，一个函数主要包括函数的名称、参数和返回值类型。函数可以接受参数，并在函数内部进行计算，然后返回一个值。

前面的例子中，我们使用的 printf、getchar、putchar 都称为库函数，接下来我们自己手动编写一些简单计算的函数，下面是一个加法函数的例子。

```clike
#include <stdio.h>

int add(int a, int b) {
    return a + b;
}

int main() {
    int one = 10, tow = 20;
    int result = 0;
    
    // 调用 add 函数，获取计算结果
    result = add(one, tow);
    
    // 输出结果
    printf("one + tow = %d\n", result);
    
    // 也可以减少一个变量，简化成: printf("one + tow = %d\n", add(one, tow));
    
    return 0;
}
```

函数定义的一般形式为:

```clike
返回值类型 函数名(0 个或多个参数) {

}
```

练习：

1. 编写一个函数，要求有两个整型参数，返回较大的值，需要用到条件判断。
2. 根据前面的美元兑换人民币的例子，编写一个函数，通过参数控制返回多少行数据：比如参数为 2 时，返回 1, 2 美元兑换的人民币，参数为 3 时，返回 1, 2, 3 美元兑换的人民币，以此类推。

函数不一定有返回值，也可以没有参数，比如下面的例子。

```clike
void sayHello() {
    printf("hello\n");
}
```

### 1.8 参数

C 语言中，所有参数都是通过 "值" 传递给函数的，这意味着，如果函数修改了参数的值，那么修改后的值不会影响调用函数的变量。

```clike
#include <stdio.h>

void change(int a) {
    // 这里的 a 变量与 main 函数中的 a 变量，不是同一个变量，这里的 a 是变量是一个新的变量，命名刚好也为 a，而且值等于 main 函数中的 a 变量
    a = 1;
}

int main() {
    int a = 0;
    
    change(a);
  
    printf("a = %d\n", a);
    
    return 0;
}
```

> 如果想要在 change 函数中国改变 a 的值，那么需要使用指针。

### 1.9 字符数组

前面提到了，在 C 语言中，如果函数修改了参数的值，那么修改后的值不会影响调用函数的变量，但如果参数是一个数组，情况就不同了，传递给函数的值是数组起始元素的地址（也可以称为指针）。

被调用的函数中，可以通过数组下标修改数组元素的值。

```clike
#include <stdio.h>

// 这里没有做数组长度的检查
void changeArr(char arr[]) {
    arr[0] = 'w';
    arr[1] = 'o';
    arr[2] = 'r';
    arr[3] = 'l';
    arr[4] = 'd';
    arr[5] = '\0';
}

int main() {
    char arr[6] = "hello";
    
    printf("调用函数前 arr: %s\n", arr);
    
    changeArr(arr);
    
    // 从输出可以看到，arr 中的内容被改变了
    printf("调用函数后 arr: %s\n", arr);

    return 0;
}
```

练习:
1. 尝试编写一个 reverse 函数（reverse 是反转的意思），将字符数组中的内容反转。

### 1.10 外部变量与作用域

在 C 语言中，变量的作用域是定义变量所在的函数内，如果变量在函数外定义，那么这个变量就是全局变量。函数中的每个局部变量只有在函数被调用时存在，在函数执行完毕退出时消失。

除了局部变量之外，还可以定义位于所有函数外部的变量，所有函数都可以访问这个变量。

```clike
#include <stdio.h>

void change() {
    a = 1;
}

int a = 0;

int main() {
    printf("a = %d\n", a);
    
    change();
    
    printf("a = %d\n", a);
}
```

#### extern 关键字

上面的例子，假如 change 函数定义在 int a = 0; 之前，那么就需要使用 extern 关键字。

```clike
#include <stdio.h>

void change() {
    // 声明这是一个外部变量，其定义不在本函数中
    extern int a;
    a = 1;
}

int a = 0;

int main() {
    printf("a = %d\n", a);
    
    change();
    
    printf("a = %d\n", a);
}
```
