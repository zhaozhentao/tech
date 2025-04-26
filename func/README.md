### 蜂鸣器实验与 C 语言数组

开发板上使用的蜂鸣器是无源蜂鸣器，属于压电式蜂鸣器类型。这里说的有源和无源，并不是指电源的意思，
而是指蜂鸣器内部是否含有振荡电路，有源蜂鸣器内部自带振荡电路， 只需提供电源即可发声， 
而无源蜂鸣器则需提供一定频率的脉冲信号才能发声， 频率大小通常在 1.5-5KHz 之间。

对于无源蜂鸣器，如果改变频率就可以调节蜂鸣器音调，产生各种不同音色、音调的声音。如果改变输出电平的高低电平占空比，
则可以改变蜂鸣器的声音大小。

```clike
#include "reg52.h"

typedef unsigned int u16; // 对系统默认数据类型进行重定义
typedef unsigned char u8;

sbit BEEP = P2^5; // 将 P2.5 管脚定义为 BEEP

void delay_10us(u16 tenus) {
  while (tenus--);
}

void main() {
  u16 i = 2000;

  while(1) {
    //循环 2000 次
    while (i--) {
      BEEP = !BEEP; //产生一定频率的脉冲信号
      delay_10us(100);
    }

    i = 0;    //清零
    BEEP = 0; //关闭蜂鸣器
  }
}

```

```clike
#include "reg52.h"

// 定义蜂鸣器连接的引脚
sbit buzzer = P2^5; // 将 P2.5 管脚定义为 BEEP

// 延时 10us 的函数
void delay_10us(int n) {
    int i;

    for (i = 0; i < n; i++);
}

// 音符对应的频率（Hz）
float note_frequencies[] = {261.63, 293.66, 329.63, 349.23, 392.00, 440.00, 493.88};

// 播放指定音符一段时间的函数
void play_note(int note, int duration_ms) {
    int i = 0;
    float frequency;
    int period_10us;
    int half_period_10us;
    int cycles;

    if (note < 1 || note > 7) {
        return;
    }

    frequency = note_frequencies[note - 1];
    // 计算方波周期（单位：10us）
    period_10us = (int)(1e6 / (frequency * 10));
    half_period_10us = period_10us / 2;
    // 计算总循环次数
    cycles = (int)(duration_ms * 1e3 / (period_10us * 10));

    for (; i < cycles; i++) {
        buzzer = 1;
        delay_10us(half_period_10us);
        buzzer = 0;
        delay_10us(half_period_10us);
    }
}

void main() {
    int note = 1;
    // 依次播放音符 1 - 7，每个音符持续 500 毫秒
    for (; note <= 7; note++) {
        play_note(note, 500);
    }
    while (1);
}
```