# RT-Thread-Studio

## RT-Thread-Studio下载
浏览器中输入https://www.rt-thread.org/page/download.html，然后选择下载RT-Thread Studio，下载完成安装即可。

## 如何创建工程
以STM32F103C8T6板为例

- 打开RT-Thread Studio，点击“文件”->“新建”->“RT-Thread项目”

- 填写如下信息：

![创建RT-Thread项目](Image/RT-Thread-Studio-CreatePrj.png)

其中工程名，工程位置，使用的芯片，调试器等根据实际情况选择。

## 如何配置RT-Thread的UART
- 设置开发板使能UART port
在board.h文件中，可以根据每个开发板自身资源使用情况设置UART
- 配置console使用的串口
在rtconfig.h文件中，修改#define RT_CONSOLE_DEVICE_NAME "uart1"，可以根据开发板实际的串口使用情况修改。

## 参考