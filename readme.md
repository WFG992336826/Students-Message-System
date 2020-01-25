### 环境：Visual Studio 2019 + MFC+Access2016

1. 登录界面页面跳转完成
2. 图片背景成功 可定时关闭
3. 数据库连接完成
4. 登录界面和主界面读取数据库完成
5. 插入数据库学生信息完成
6. 读取数据库并将信息写入窗口中的表格中
7. 修改信息功能完成
8. 删除学生信息完成
9. 精确查询信息完成
10. 使用SQL语言实现对名字的模糊查询
11. 显示数据库首项和尾项功能
12. 可以再第二次生成的窗口中添加背景图片（仿照自动生成的窗口类来写新窗口的类）

### 编程中遇到的问题

1. 测试VS连接Access及我遇到的一些问题及解决方案

   https://app.yinxiang.com/fx/62a17202-d48d-4e85-82b7-26c9b8507413

2. LPCTSTR string 转换；

   解决方法：**项目-属性-属性配置-常规-字符集，修改为：多字节显示**

3. MFC窗口退出时，弹出提示框

   解决方法：新建消息映射

   BEGIN_MESSAGE_MAP(CLibrarySystemDlg, CDialogEx)

    **ON_MESSAGE(WM_CLOSE, OnClose)**

   END_MESSAGE_MAP()

   定义相关联函数 OnClose();

   **afx_msg LRESULT OnClose(WPARAM wPara, LPARAM lPara)**

4. Edit控件，按回车键会退出程序

   参考博客：<https://www.cnblogs.com/dupengcheng/p/5618286.html>