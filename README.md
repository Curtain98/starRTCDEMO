# starRTC-DEMO
生成C++DLL 并调用IP/ID通话 添加试试回调信息以供C#进行处理  已封装 回调信息只需要导入BackMsgEntity.h即可.  
感谢用户 work1989 提供的思路 以及Windows端开发者的协助  
原网址https://github.com/work1989/starrtcForCSharpe?tdsourcetag=s_pcqq_aiomsg.  
Windowns-DEMO地址https://github.com/starrtc/starrtc-windows-demo.   
本DEMO为上述DEMO进行修改. 使用教程图片已经放入文件中.  
****
注意事项  
#1.首先将c++源代码CVoipP2PDlg.h 改成了对应的TPVOIP_P2P.h,基本99%的代码不需要更改,大家可以直接参考  
#2.利用dllexport 关键字开放几个函数给c#调用  
#3.注释相关无用代码 入口处starrtcdemo.cpp文件里面注释以下代码,并将retrun FALSE改为return TRUE  (不修改则使用接口 将载入C++窗体 同时卡死程序)
//CStarRTCMenuDialog dlg;  
//m_pMainWnd = &dlg;  
//INT_PTR nResponse = dlg.DoModal();  
//if (nResponse == IDOK)  
//{  
//	// TODO: 在此放置处理何时用  
//	//  “确定”来关闭对话框的代码  
//}  
//else if (nResponse == IDCANCEL)  
//{  
//	// TODO: 在此放置处理何时用  
//	//  “取消”来关闭对话框的代码  
//}  
//else if (nResponse == -1)  
//{  
//	TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");  
//	TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");  
//}  
#4.配置属性 将项目默认值->配置类型 改为动态库(dll)  
#5.c/c++ 里面的优化改为 已禁用 (/Od) 否则c#无法初始化类
****
![Aaron Swartz](https://github.com/Curtain98/starRTCDEMO/blob/master/Csharpe/set.png)  
![Aaron Swartz](https://github.com/Curtain98/starRTCDEMO/blob/master/Csharpe/set2.png)  
![Aaron Swartz](https://github.com/Curtain98/starRTCDEMO/blob/master/Csharpe/code.png)  
![Aaron Swartz](https://github.com/Curtain98/starRTCDEMO/blob/master/Csharpe/su.png)
