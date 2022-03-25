## 简介

iSwordSDK 是一款提供系统内核调用穿透能力的开发套件。

可以帮忙安全软件轻松结束恶意软件进程、删除顽固病毒。或者在安全对抗中，提高自己对系统的控制能力。同时也可以绕过UAC，达到自动提权的效果。

> **如果您有下面这些问题的困扰，都可以考虑接入ISwordSDK**
>
> 想结束受保护的进程（比如病毒、其他杀毒软件）怎么办？
>
> 想删除正在运行进程的文件怎么办？
>
> 想删除被其他软件占用的文件怎么办？
>
> 想在被保护的文件目录写入软件怎么办？
>
> 终端安全产品部署管理员要求静默卸载竞品怎么办？
>
> 开机启动总是被其他安全软件拦截，设置失败怎么办？
>
> 需要管理员权限的软件总是弹烦人的UAC框怎么办？

###  ✨具备如下核心功能

- **强制结束进程**
- **强制删除文件**
- 文件打开、操作
- 进程打开、操作
- 注册表打开、操作
- 进程令牌打开
- 自动提权

###  📦适用于如下的产品

- 杀毒软件
- 系统优化
- Ark工具
- 其他需要高权限的产品

## 接入文档

使用太简单，根本不需要文档。

## 🔨 快速入门

示例一：强制结束进程

```c++
int main()
{
	SwordManager manager;

	HRESULT hr = manager.Start();

	CheckSignError(hr);

	cxAPITerminateProcess api(manager);
	api.ProcessId = 1234; // Set The ProcessId To Termiante!
	HRESULT hr = api.Call();

	return 0;
}
```

示例二：强制删除文件

```c++
int main()
{
	SwordManager manager;

	HRESULT hr = manager.Start();

	CheckSignError(hr);

	cxAPIDeleteFile api(manager);
	api.Path = L"PathToDelete";
	api.CloseAllHandles = TRUE;
	HRESULT hr = api.Call();

	return 0;
}
```

## 设计特点

iSwordSDK使用基于IDL的方式设计，使用方便、扩展简单。有效地解决了应用层到驱动层相互传递数据的安全性和开发效率。

只需要两个步骤，就可以实现一个新的API，完全不需要考虑参数的封装、传递、校验等重复工作。

1. 添加IDL参数

   ```idl
   struct DeleteFile
   {
   	Path : String;
   	CloseAllHandles : ULONG;
   }
   ```

2. 实现具体的函数（通过偏特化cxAPIProtocol来实现）

   ```c++
   template<>
   struct cxAPIProtocol<cxAPIDeleteFile>
   {
   	static NTSTATUS Call(const cxAPIDeleteFile& params, cxAPIResult& result)
   	{
   		PCUNICODE_STRING path = params.Path;
   		ULONG close_all_handles = params.CloseAllHandles;
   
   		return g_APIFile->ForceDeleteFile(path, close_all_handles);
   	}
   };
   ```

## 使用授权

> 免责说明：
>
> iSwordSDK（以下称本SDK）只授权给为正规的企业厂商使用。禁止用于危害企业、个人安全等任何非法的场景。
>
> 本SDK带有内核驱动程序，在使用本SDK前，请先在业务对应的环境系统中充分测试后再实际接入使用。
>
> 非法授权、非法使用而造成的经济损失、法律问题都于本SDK提供团队无关。
>
> 在您使用本SDK前，视为您已经知悉并且遵守此免责说明。

不同授权的功能差异：

| 功能说明                             | 免费授权     | 企业授权                     | 企业定制授权 |
| ------------------------------------ | ------------ | ---------------------------- | ------------ |
| 强制结束进程                         | ✔            | ✔                            | ✔            |
| 强制删除文件                         | ✔            | ✔                            | ✔            |
| 文件打开、操作                       |              | ✔                            | ✔            |
| 进程打开、操作                       |              | ✔                            | ✔            |
| 注册表打开、操作                     |              | ✔                            | ✔            |
| 进程令牌打开                         |              | ✔                            | ✔            |
| 自动提权                             |              | ✔                            | ✔            |
| 权限校验（支持按路径、私有签名验证） |              | ✔                            | ✔            |
| 源码                                 |              |                              | ✔            |
| 服务支持                             | 邮件、GitHub | 邮件、GitHub、微信、远程桌面 | ✔            |

[授权请通过邮箱（admin@iMonitorSDK.com）联系。](mailto://admin@iMonitorSDK.com)
