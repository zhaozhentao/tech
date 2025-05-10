### 独立按键

前面的课程中主要使用了 IO 口的输出功能，本节课程将使用 IO 口的输入功能来实现独立按键的功能。

#### 独立按键的原理

从原理图中可以看出，独立按键一端接的是 P3.x IO 口，另一端接的是 GND，当按键按下时，P3.x IO 口的电平会被拉低，当按键松开时，P3.x IO 口恢复高电平。
所以只需要`读取` P3.x IO 口的电平状态，就可以知道按钮是否被按下。

本节的重点就是 `读取` IO 口的电平状态。

![独立按键原理图](./button.png)

```clike
#include "reg52.h"

typedef unsigned int u16;
typedef unsigned char u8;

sbit KEY1 = P3^1;
sbit KEY2 = P3^0;
sbit KEY3 = P3^2;
sbit KEY4 = P3^3;

sbit LED1 = P2^0;

#define KEY1_PRESS 1
#define KEY2_PRESS 2
#define KEY3_PRESS 3
#define KEY4_PRESS 4
#define KEY_UNPRESS 0

void delay_10us(u16 tenus) {
  while (tenus--);
}

u8 key_scan(u8 mode) {
  static u8 key = 1;

  if (mode) key = 1; // 连续扫描按键

  // 任意按键按下
  // 这里的 KEY1 == 0 实际上就是先"读取"了 P3.1 IO 口的电平状态，然后再与 0 进行比较
  if (key == 1 && (KEY1 == 0 || KEY2 == 0 || KEY3 == 0 || KEY4 == 0)) {
    delay_10us(1000)
    key=0;

    if (KEY1 == 0)
      return KEY1_PRESS;
    
    if (KEY2 == 0)
      return KEY2_PRESS;

    if (KEY3 == 0)
      return KEY3_PRESS;

    if (KEY4 == 0)
      return KEY4_PRESS;
  } else if (KEY1 == 1 && KEY2 == 1 && KEY3 == 1 && KEY4 == 1) {
    key = 1;
  }
  return KEY_UNPRESS;
}

void main() {
  u8 key;

  while (1) {
    // 获取按下的按键
    key = key_scan(0);

    if (key == KEY1_PRESS) {
      LED1 = !LED1;
    }
  }
}
```

### 练习

通过四个按键，分别控制四个 LED 灯的亮灭。
