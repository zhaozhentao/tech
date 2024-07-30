#### 1. 编写一个简单的计算器程序，支持基本运算

要求：接收一个简单的数学表达式（只需要支持两个操作数，加减乘除操作符），运行计算出结果。

例子：程序接收字符串 `3 * 5` ，需要输出结果 15。

提示：可以使用下面模板接收输入的字符串。

```java
import java.util.Scanner;

public class ExpressionCalculator {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        String expression = scanner.nextLine();

        scanner.close();
    }
}
```
