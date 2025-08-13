### WIFI 模块

#### TCP Client 示例

```shell
// 配置为 Station 模式
AT+CWMODE=1

// 连接 wifi 网络，帐号密码
AT+CWJAP_DEF="cotti coffee","Cotti123"

// 查看密码
AT+CIFSR

// 开启单连接
AT+CIPMUX=0

// 与服务器建立连接，IP + 端口
AT+CIPSTART="TCP","8.138.139.254",8080

// 发送 10 个字符到服务器
AT+CIPSEND=10

// 上面的指令响应后，串口发送具体内容
Ai-Thinker
```

#### 代码

```clike
#include <stdio.h>
#include <ncurses.h>

int main() {
    int ch;

    // 初始化ncurses库
    initscr();

    // 关闭回显，不在屏幕上显示输入的字符
    noecho();
    // 开启cbreak模式，无需等待回车即可获取输入
    cbreak();
    // 启用功能键（如方向键）的捕获
    keypad(stdscr, TRUE);
    
    printw("press q to quit...\n");
    refresh();
    
    while (1) {
        ch = getch(); // 获取输入
        
        switch (ch) {
            case KEY_UP:
                printw("key up\n");
                break;
            case KEY_DOWN:
                printw("key down\n");
                break;
            case KEY_LEFT:
                printw("key left\n");
                break;
            case KEY_RIGHT:
                printw("key right\n");
                break;
            case 'q':
                printw("退出程序...\n");
                endwin(); // 关闭ncurses模式
                return 0;
            default:
                printw("按下了未知键: %d\n", ch);
                break;
        }
        refresh(); // 刷新屏幕显示
    }
    
    endwin(); // 关闭ncurses模式
    return 0;
}
```
