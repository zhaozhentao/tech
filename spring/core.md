##### IOC 控制反转

在传统的 Java 程序开发中，我们需要通过 `new` 关键字来创建对象，对象的使用者需要关心构造这个对象所需要的参数，如果程序中有多个地方需要用到这个
类所创建的对象，就有可能需要多次出现相似的对象创建代码。

IOC 为我们实现了对象的管理，简单来说就是我们把设计好的对象交给 Spring 容器，需要使用到这个对象的时候就直接从容器中获取，而不需要手动的 new 出对象。

举个例子，我们平时使用得最多的被 @RestController 注解的类 XXXController 。

```java
@RestController 
public class XXXController {

    @GetMapping("/")
    public Object index() {
        ...
    }
}
```

index 方法并没有被 `static` 修饰，所以这是一个需要有 XXXController 的实例才能被调用的方法，而这个实例正是 Spring 的 IOC 为我们创建的。

##### Dependency Injection 依赖注入

依赖注入（Dependency Injection，DI）和控制反转（Inversion of Control，IoC）是两个相关但又不完全相同的概念，它们通常一起使用来提高软件应用程序的可维护性、灵活性和可测试性。

继续沿用上面的例子，假如我们的 XXXController 中有包含了下面的代码。

```java
@RestController
public class XXXController {

    @Resource
    XXXService xxxService;
    
    @GetMapping("/")
    public Object index() {
        ...
    }
}
```

这说明创建 XXXController 需要 XXXService 实例作为 "原料" ，正是 Spring 的依赖注入机制为我们创建 XXXController 时候 "注入" XXXService 实例。

##### 引申

上面提及的 XXXController 是在整个 Spring 容器中是单例还是多例 ？单例和多例有什么影响吗。
