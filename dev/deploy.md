##### 1. 部署到 开发/生产 环境

公司在 “猪齿鱼” 上有搭建好的自动化部署流水线，只需要通过 git tag 标记你要部署的某个 commit ，就可以完成自动化部署。

根据 tag 不同的格式，会触发不同的流水线任务，以 SFA 后端应用为例，格式说明如下

* 开发环境：T.FA{日期}{编号}-sfa-api-backend
* 生产环境：vR.FA{日期}{编号}-sfa-api-backend

下面是 SFA 后端应用具体的 tag。

![image](../images/tag.jpg)
