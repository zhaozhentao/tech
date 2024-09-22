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

> 启动 htop 后，大写 S，勾选 `Display options` 然后勾选 `Tree View` 和 `Show custom thread names` 可以看到进程下产生的线程状态。

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

前面基于 top 和 jstack 的排查过程基本够用，但步骤略繁琐，更简单的是借助其他现成的工具比如 github 上的一个开源项目 [useful-scripts](https://github.com/oldratlee/useful-scripts) 中的一个脚本 show-busy-java-threads ，
该脚本可以通过一行命令的操作就完成前面通过 top 和 jstack 的几步操作。

下面是一个简单的示例，通过一条命令找出之前的繁忙线程。

```bash
$ ./show-busy-java-threads 3 10 -c 5 -a top.log
```

每 3 秒刷新一次，一共执行 10 次，获取 CPU 消耗 top 5 的线程状态，结果保存到 top.log 文件中。

<div style="text-align: center">
    <img src="./images/java/show.png">
</div>

命令执行完后，检查输出的 top.log 文件，可以看到繁忙线程的信息。

<div style="text-align: center">
    <img src="./images/java/show2.png">
</div>

### Arthas 阿尔萨斯

Arthas 是一款线上监控诊断产品，通过全局视角实时查看应用 load、内存、gc、线程的状态信息，并能在不修改应用代码的情况下，对业务问题进行诊断，
包括查看方法调用的出入参、异常，监测方法执行耗时，类加载信息等，大大提升线上问题排查效率。

#### 安装与启动

```bash
$ curl -O https://arthas.aliyun.com/arthas-boot.jar

$ java -jar arthas-boot.jar
```

arthas-boot 运行起来后，选择需要诊断的 Java 进程 attach，成功后就可以看到如下图所示。

<div style="text-align: center">
    <img src="./images/java/arthas.png">
</div>

#### 使用 Arthas 查看繁忙线程

和前面一样，接下来看看如何利用 Arthas 查找 Java 进程中的繁忙线程。

在 Arthas 控制台中，输入不带参数的命令 thread ，可以看到 JVM 中的线程，默认按 CPU 耗时降序排列。

```bash
$ thread
```

<div style="text-align: center">
    <img src="./images/java/arthas_thread.png">
</div>

找到最繁忙的线程 id 后，输入下面命令可以看到具体线程状态。

```bash
$ thread id
```

<div style="text-align: center">
    <img src="./images/java/arthas_thread2.png">
</div>

#### 停止

Arthas 通过增强类来实现 Java 进程的诊断，在诊断完毕后，需要调用下面命令，重置掉所有增强类。

```bash
$ stop
```
