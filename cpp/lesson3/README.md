### 输入与输出(第五节)

#### 函数简介

在学习输入输出之前，有必要先简单学习一下关于函数的一些概念，包括函数的定义、参数、返回值，以及函数的调用。

可以把函数想象成一个数据的加工工厂，接收一个或多个参数，计算出一个结果。比如可以设计一个函数，计算不同数量的兔和狗，会有多少只脚(一只狗4只脚，一只兔子2只脚)。

```clike
// 返回值类型是 int， 函数名为 calc，接收两个参数，一个参数代表狗的数量，一个参数代表兔子的数量
int calc(int dog, int rabbit) {
    // 在函数中计算我们要想获得的内容
    int result = dog * 4 + rabbit * 2;
    
    // return 表示返回的结果
    return result; 
}

int main() 
{
    int legs1 = 0;
    int legs2 = 0;
    
    // 调用函数计算 2 只狗，3 只兔子时，有多少只脚
    legs1 = calc(2, 3);
    
    // 调用函数计算 3 只狗，5 只兔子时，有多少只脚
    legs2 = calc(3, 5);
    
    return 0;
}
```

##### 练习

编写一个函数，实现人民币与美元之间的转换，假设 1 美元等于6.5 人民币，那么输入参数 1，返回 6.5。

#### 输入输出简介

目前学习的命令行程序一般是通过键盘来获取输入的数据，然后通过屏幕来输出程序想要给用户展示的结果。

比如下面一个咖啡点单程序，通过键盘输入所需要的咖啡，然后输出选择结果。

```clike
#include <iostream>

using namespace std;

int main() {
    int choice;
    
    cout << "欢迎来到咖啡店！" << endl;
    cout << "请选择您想要的咖啡：" << endl;
    cout << "1. 美式咖啡 (Americano) - ¥15" << endl;
    cout << "2. 拿铁咖啡 (Latte) - ¥20" << endl;
    cout << "3. 卡布奇诺 (Cappuccino) - ¥18" << endl;
    cout << "4. 摩卡咖啡 (Mocha) - ¥22" << endl;
    cout << "5. 浓缩咖啡 (Espresso) - ¥12" << endl;
    cout << "请输入您的选择 (1-5): ";
    
    cin >> choice;
    
    switch(choice) {
        case 1:
            cout << "您选择了美式咖啡，价格为¥15。" << endl;
            break;
        case 2:
            cout << "您选择了拿铁咖啡，价格为¥20。" << endl;
            break;
        case 3:
            cout << "您选择了卡布奇诺，价格为¥18。" << endl;
            break;
        case 4:
            cout << "您选择了摩卡咖啡，价格为¥22。" << endl;
            break;
        case 5:
            cout << "您选择了浓缩咖啡，价格为¥12。" << endl;
            break;
        default:
            cout << "无效选择，请重新运行程序并输入1-5之间的数字。" << endl;
            return 1;
    }
    
    cout << "谢谢惠顾，您的咖啡正在制作中..." << endl;
    
    return 0;
}

```

#### 字符输入函数 getchar

getchar() 函数用于从键盘输入一个字符，并返回该字符。getchar 函数会等待用户输入，直到用户按下回车键。

* getchar 只能接受一个字符，输入数字也按字符处理。
* 输入多于一个字符，只接收第一个字符。
* getchar 以回车键结束输入。

下面是 getchar 函数的使用例子。

```clike
#include <iostream>
#include <cstdio>

using namespace std;

int main() {
    // 定义一个字符变量
    char ch;
    
    cout << "请输入一个字符: ";
    
    // 使用 getchar 读取单个字符
    ch = getchar();
    
    cout << "您输入的字符是: " << ch << endl;
    
    return 0;
}
```

> 需要说明的是，如果要使用 getchar 函数，需要包含 cstdio 头文件(暂时先忽略头文件这个概念)。

#### 字符输出函数 putchar

putchar 可以向屏幕中输出一个字符。可以看下面的例子。

```clike
#include <cstdio>
#include <iostream>

using namespace std;

int main() {
    char ch = 'A';
    
    // 这里会显示出一个字符 A
    putchar(ch);
    
    // 根据 ASCII 表，A 的 ASCII 码是 65，这里也会显示出字符 A
    putchar(65);
    
    return 0;
}
```

#### cout 

在 C++ 中，可以使用 cout 向屏幕打印，类似上面的 putchar。要使用 cout ，至少需要按照下面代码

```clike
// 包含 iostream 头文件，引入 cout
#include <iostream>

// cout 在 std 命名空间中，如果不使用下面这句，则需要使用 std::cout
using namespace std;

int main() 
{
    /*
     * cout 使用语法为: cout << 输出内容 << endl; 其中 endl 表示换行
     * 可以一行中包含多个输出内容：cout << 输出内容1 << 输出内容2 << endl;
     */
    cout << "Hello World!" << endl;

    return 0;
}
```

##### 练习

使用 cout 输出下面的内容。

```txt
*
**
***
****
*****
```
