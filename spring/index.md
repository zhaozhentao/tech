##### Spring 与 Spring Boot

首先 Spring Boot 并不是 Spring、SpringMVC 替代，而是使他们用起来更加简单。

Spring 和 Spring MVC 最大的弊病在于存在大量的配置，并且这些配置在不同的项目中具有很高的相似性。从而导致重复配置，繁琐而且杂乱。

比如，为了实现一个 url 路径到 Controller 的映射，我们可能会使用到下面的代码（通过 Java 配置）。

```java
@EnableWebMvc
@Configuration
public class WebConfig {

    /// ...
}
```

```java
@EnableWebMvc
@Configuration
public class WebConfig implements WebMvcConfigurer {

   @Override
   public void addViewControllers(ViewControllerRegistry registry) {
      registry.addViewController("/").setViewName("index");
   }

   @Bean
   public ViewResolver viewResolver() {
      InternalResourceViewResolver bean = new InternalResourceViewResolver();

      bean.setViewClass(JstlView.class);
      bean.setPrefix("/WEB-INF/view/");
      bean.setSuffix(".jsp");

      return bean;
   }
}
```

```java
@EnableWebMvc
@Configuration
@ComponentScan(basePackages = { "com.baeldung.web.controller" })
public class WebConfig implements WebMvcConfigurer {
    // ...
}
```

或者是通过 xml 进行配置。

```xml
<context:component-scan base-package="com.baeldung.web.controller" />
<mvc:annotation-driven />    

<bean id="viewResolver" 
      class="org.springframework.web.servlet.view.InternalResourceViewResolver">
        <property name="prefix" value="/WEB-INF/view/" />
        <property name="suffix" value=".jsp" />
    </bean>

    <mvc:view-controller path="/" view-name="index" />

</beans>
```

不论是通过 Java 还是 xml 配置都很繁琐，且恶心，开发人员不得不编写很多业务无关的代码。如果换成 Spring Boot 则只需要。

```java
@RestController
public class Controller {
    
    @GetMapping("/")
    public void index() {
        // 业务代码
    }
}
```
