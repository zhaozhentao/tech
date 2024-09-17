### GoAccess 简介

GoAccess - 可视化 Web 日志分析工具。

GoAccess 是一款开源(MIT许可证)的且具有交互视图界面的实时 Web 日志分析工具，分析结果可以通过你的 Web 浏览器或者 *nix 系统下的终端程序访问。

GoAccess 常见使用场景如下

1. 检查是否有异常流量（异常的 ip 访问数量、扫描不存在的路径、提交可执行脚本、可疑的 User-Agent 和 OS）
2. 检查应用流量是否合理（接口访问次数是否正常）
3. 简单的独立访问用户统计

### GoAccess 的使用

如果你的 Nginx 日志按默认格式输出，那么不需要任何配置，直接运行下面命令就可以进行日志分析。如果分析的日志为实时日志，则会把分析结果刷新到终端中。

```shell
$ goaccess your_access.log
```

分析结果

![image](../images/goaccess/goaccess1.png)

恶意流量

![image](../images/goaccess/goaccess2.png)

非法 User-Agent

![image](../images/goaccess/goaccess3.png)

### GoAccess In Action

下面以小康的一次流量优化为例，说明一下如何借助 GoAccess 找到系统中可优化的地方。

以下为小康服务器 2024-06-18 的访问记录分析结果，分析结果输出到 html 文件中。

<iframe src="../files/all.html" height="800px"></iframe>

#### 统计结果分析

根据上面的分析结果可以看到，静态资源传输流量为 125.57 GiB，占总流量约 67% 。通过对静态资源传输数据量大小进行排序，可以看到 /htnew/static/js/chunk-vendors.js 文件消耗流量最高，单个文件消耗流量 5.03 GiB。

接下来，根据上面的文件路径重新到 Nginx 日志过滤一下，可以确定其完整的访问路径。得到完整的访问路径后在浏览器中访问，可以看到 http 响应头中出现的缓存控制字段如下图所示。

![image](../images/goaccess/img.png)

由于该字段的出现，导致用户每次访问小康相关的前端页面时，都需要完整加载所有的前端资源 ( js、css、image )，无法利用客户端本身的缓存，造成用户端流量的浪费，同时也增加了服务器的带宽压力。

接下来分析一下为什么响应头中会出现 `Cache-Control: no-store, no-cache, must-revalidate, proxy-revalidate, max-age=0`。

##### 单页应用的访问

<div style="text-align: center">
    <img src="./images/goaccess/nginx1.svg">
</div>

通常情况下，当浏览器访问一个网站时，会缓存以下类型的资源以加快后续访问的速度并减少网络流量：

1. HTML 页面，主页面内容，即页面的 HTML 文件，可能会被缓存
2. CSS 文件
3. JavaScript 文件
4. 图像文件，图片资源（如 .jpg, .png, .gif, .svg 等）会被缓存，尤其是网站中的 logo、背景图等不常变化的图片。


<div style="text-align: center">
    <img src="../images/goaccess/nginx2.svg">
</div>

一切正常...

##### 版本更新

当项目组有新版本的前端资源发布时，服务器中的静态资源文件发生变更，但文件名不变（此处用 '' 表示文件内容已经发生变化）。下面是一种前端项目版本更新时用户访问出现“白屏”的可能。

<div style="text-align: center">
    <img src="./images/goaccess/nginx3.svg">
</div>

> 此时，压力来到运维同事这边...

最终，为了应对这种情况，项目组在 Nginx 中加入了 `Cache-Control: no-store, no-cache, must-revalidate, proxy-revalidate, max-age=0` 的配置，强制用户每次访问都必须重新到服务器中加载相关资源文件。

#### 解决方案 

##### 1 文件名变更

为了解决上述问题，只需要在每次发布新版本时，简单地给所有资源文件增加一个“版本号”的变数，例如 app.js 变为 app1.js，那么用户在访问时，浏览器缓存肯定不会存在 app1.js 文件。

<div style="text-align: center">
    <img src="./images/goaccess/nginx4.svg">
</div>

经过上述改造后，Nginx 中的强制刷新缓存配置已经可以去掉了，并且发布新版本时也不会再出现“白屏”的问题。

##### 2 客户端缓存

浏览器的缓存机制几乎是在万维网刚刚诞生时就已经存在，在 HTTP 协议设计之初，便确定了服务端与客户端之间“无状态”（Stateless）的交互原则，即要求每次请求是独立的，
每次请求无法感知也不能依赖另一个请求的存在。但无状态并不只有好的一面，由于每次请求都是独立的，服务端不保存此前请求的状态和资源，
所以也不可避免地导致其携带有重复的数据，造成网络性能降低。HTTP 协议对此问题的解决方案便是客户端缓存，在 HTTP 从 1.0 到 1. 1，再到 2.0 版本
的每次演进中，逐步形成了现在被称为“状态缓存” 、 “强制缓存”（许多资 料中简称为“强缓存”）和“协商缓存”的 HTTP 缓存机制。

###### 强制缓存

HTTP 的强制缓存对一致性处理的策略就如它的名字一样，十分直接：假设在某个时点到来以前，譬如收到响应后的 10 分钟内，资源的内容和状态一定不会被改变，
因此客户端可以无须经过任何请求，在该时点前一直持有和使用该资源的本地缓存副本。

根据约定，强制缓存在浏览器的地址输入、页面链接跳转、新开窗口、前进和后退中均可生效，但在用户主动刷新页面时应当自动失效。HTTP 协议中设有以下两类 Header 实现强制缓存。

1.Expires

Expires 是 HTTP/1.0 协议中开始提供的 Header，后面跟随一个截至时间参数。当服务器返回某个资源时带有该 Header 的话，意味着服务器承诺截止时间之前资源不会发生变动，
浏览器可直接缓存该数据，不再重新发请求，示例

```http
HTTP/1.1 200 OK
Expires: Wed, 8 Apr 2020 07:28:00 GMT
```

Expires 是 HTTP 协议最初版本中提供的缓存机制，设计非常直观易懂，但考虑得并不够周全，它至少存在以下显而易见的问题：

* 受限于客户端的本地时间。譬如，在收到响应后，客户端修改了本地时间，将时间前后调整几分钟，就可能会造成缓存提前失效或超期持有。
 
* 无法处理涉及到用户身份的私有资源，譬如，某些资源被登录用户缓存在自己的浏览器上是合理的，但如果被代理服务器或者内容分发网络缓存起来，则可能被其他未认证的用户所获取。

2.Cache-Control

Cache-Control 是 HTTP/1.1 协议中定义的强制缓存 Header，它的语义比起 Expires 来说就丰富了很多，如果 Cache-Control 和 Expires 同时存在，
并且语义存在冲突（譬如 Expires 与 max-age / s-maxage 冲突）的话，规定必须以 Cache-Control 为准。Cache-Control 的使用示例如下：

```http
HTTP/1.1 200 OK
Cache-Control: max-age=600
```

Cache-Control 在客户端的请求 Header 或服务器的响应 Header 中都可以存在，它定义了一系列的参数，且允许自行扩展（即不在标准 RFC 协议中，
由浏览器自行支持的参数），其标准的参数主要包括有：

* max-age 和 s-maxage：max-age 后面跟随一个以秒为单位的数字，表明相对于请求时间（在 Date Header 中会注明请求时间）多少秒以内缓存是有效的，
资源不需要重新从服务器中获取。相对时间避免了 Expires 中采用的绝对时间可能受客户端时钟影响的问题。s-maxage 中的“s”是“Share”的缩写，
意味“共享缓存”的有效时间，即允许被 CDN、代理等持有的缓存有效时间，用于提示 CDN 这类服务器应在何时让缓存失效。
 
* public 和 private：指明是否涉及到用户身份的私有资源，如果是 public，则可以被代理、CDN 等缓存，如果是 private，则只能由用户的客户端进行私有缓存。
no-cache 和 no-store：no-cache 指明该资源不应该被缓存，哪怕是同一个会话中对同一个 URL 地址的请求，也必须从服务端获取，令强制缓存完全失效，
但此时下一节中的协商缓存机制依然是生效的；no-store 不强制会话中相同 URL 资源的重复获取，但禁止浏览器、CDN 等以任何形式保存该资源。

* no-transform：禁止资源被任何形式地修改。譬如，某些 CDN、透明代理支持自动 GZip 压缩图片或文本，以提升网络性能，而 no-transform 就禁止了这样的行为，
它要求 Content-Encoding、Content-Range、Content-Type 均不允许进行任何形式的修改。

* min-fresh 和 only-if-cached：这两个参数是仅用于客户端的请求 Header。min-fresh 后续跟随一个以秒为单位的数字，用于建议服务器能返回一个不少于该时间的缓存资
源（即包含 max-age 且不少于 min-fresh 的数字）。only-if-cached 表示客户端要求不必给它发送资源的具体内容，此时客户端就仅能使用事先缓存的资源来进行响应，
若缓存不能命中，就直接返回 503/Service Unavailable 错误。

* must-revalidate 和 proxy-revalidate：must-revalidate 表示在资源过期后，一定需要从服务器中进行获取，即超过了 max-age 的时间后，就等同于 no-cache 的行为，
proxy-revalidate 用于提示代理、CDN 等设备资源过期后的缓存行为，除对象不同外，语义与 must-revalidate 完全一致。

###### 协商缓存

同时，为了正常利用客户端缓存，参考“七牛 CDN”关于 Cache-Control 字段的配置如下图

![image](./images/goaccess/qiniu1.jpg)

在 Nginx 中加入了类似下面的配置。

```nginx.conf
location ~*\.(js|css|png|jpg)$ {
    add_header Cache-Control "public, max-age=31536000";
}
```
