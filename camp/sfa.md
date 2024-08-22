### SFA 同步企业微信帐号流程

#### 1. 同步主数据，获取所有内部员工名单

目前 SFA 数据库中已有表 hmview（数据来源：主数据推送至 SOA ，由 SOA 直接写入到 SFA 数据库），该表记录海天内部员工信息。现需要在表中增加手机号字段，用于
SFA 同步人员信息至企业微信时，通过手机号判断是否内部人员。

#### 2. 人员信息同步企业微信逻辑与实现

SFA 新增或修改人员信息后，同步至企业微信判断流程如下：

1. 同步人员信息前，通过手机号在 hmview 表中检索，如果在表中存在，则认为该记录为内部人员记录，停止同步。
2. 通过企业微信接口 [获取单个部门详情](https://developer.work.weixin.qq.com/document/path/95351) https://qyapi.weixin.qq.com/cgi-bin/department/get 检查部门 id 合法性，包括：是否为空、是否存在、是否在<font color="red">外企德科（用人单位）</font> 、<font color="red">佩琪（用人单位）</font>、<font color="red">猎聘（用人单位）</font>、<font color="red">嘉驰（用人单位）</font>、<font color="red">58魔方（用人单位）</font>或其子架构中（逐级往上查找，直到根节点，检查有没有经过这些组织架构），若不合法，停止同步。
3. 通过企业微信接口 [更新成员](https://developer.work.weixin.qq.com/document/path/90197) https://qyapi.weixin.qq.com/cgi-bin/user/update 或 [创建成员](https://developer.work.weixin.qq.com/document/path/90195) https://qyapi.weixin.qq.com/cgi-bin/user/create， 同步（创建或修改）用户信息到企业微信。

调用更新/创建成员接口传递的参数包括:

| 字段名                                 | 是否必填 | 字段说明                                                                                                                                     |
|-------------------------------------|------|------------------------------------------------------------------------------------------------------------------------------------------|
| userid                              | 必填   | 企业微信用户 id ，SFA 用户的手机号                                                                                                                    |
| name                                | 必填   | 用户姓名                                                                                                                                     |
| mobile                              | 必填   | 用户手机号                                                                                                                                    |
| department                          | 必填   | 用户所在部门 id ，该值在调用企业微信[创建部门](https://developer.work.weixin.qq.com/document/path/90205)接口时返回保存至 SFA 数据库中。<br/><br/>重要：该字段的判断在上面部门 id 的检查有说明 |
| position                            | 非必填  | SFA 中的岗位信息                                                                                                                               |
| enable                              | 非必填  | 禁用状态，禁用后用户不能登录 (创建时不传)                                                                                                                   |
| external_profile.external_corp_name | 必填   | 对外显示的公司信息，固定值：海天外部合作伙伴                                                                                                                   |

> 更新 / 创建用户需要使用 <font color="red">通讯录</font> secret，查询部门使用 <font color="red">用户查询</font> secret
