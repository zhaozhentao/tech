### Java 进程问题排查三板斧

### 案例

7 月 1 日，突然收到一告警信息，内容如下。

<div style="text-align: center">
    <img src="./images/java/cpu.png">
</div>

### 传统处理办法

#### 1 找出占用 CPU 的线程

##### htop

借助 top 或 htop 等工具，找出具体占用 CPU 高的进程/线程。

如果服务器中有 htop ，可以通过打开 tree view 和显示线程名，看到如下内容。

<div style="text-align: center">
    <img src="./images/java/cpu_high.png">
</div>

> 启动 htop 后，大写 S，勾选 `Display options` -> `Tree View` 和 `Show custom thread names`

##### top

如果服务器中没有 htop ，也可以借助基本的 top ，先找出占用 CPU 高的进程号。

<div style="text-align: center">
    <img src="./images/java/cpu_high2.png">
</div>

然后通过 top -p {pid} -H ，可以找出该进程下的线程使用 CPU 情况。

<div style="text-align: center">
    <img src="./images/java/cpu_high_thread.png">
</div>

最终，通过 htop 或 top 都找到了线程 654769 正在产生高的 CPU 消耗。

#### 2 检查线程状态

经过第 1 步后，通常已经可以找出产生高 CPU 消耗的线程，然后使用 jdk 自带的工具 jstack 查看线程状态。

```bash
$ jstack 654733 | grep -A 10 9fdb1
```

> 上面的命令中 654733 为 java 进程号，9fdb1 为线程号 654769 的 16 进制显示

<div style="text-align: center">
    <img src="./images/java/jstack.png">
</div>

### Useful Scripts

#### show-busy-java-threads

```bash
$ ./show-busy-java-threads 3 10 -c 5 -a top.log
```

每 3 秒刷新一次，一共执行 10 次，获取 CPU 消耗 top 5 的线程状态，结果保存到 top.log 文件中。

<div style="text-align: center">
    <img src="./images/java/show.png">
</div>
