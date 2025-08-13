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
