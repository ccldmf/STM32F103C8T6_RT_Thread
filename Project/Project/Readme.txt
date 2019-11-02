NOTE:
	1.创建工程时，需要选择对应的MCU，如果没有对应的，则需要安装对应的软件包：Project->Manage->Reload Software Packs
	2.设置工程的输出文件：Project->Option for target "xxxxx"->Output 选中“Create HEX File"
	3.针对STM32F03C8T6，需要在Project->Option for target "xxxxx"->C/C++中的Preprocessor Symbols中设置如下宏:USE_STDPERIPH_DRIVER  STM32F10X_MD
	  可参看该链接了解具体宏定义的含义：https://blog.csdn.net/u010893262/article/details/62419606
	  在该页的下面，有Include Paths,这里是添加工程需要build的文件夹的路径，包括.c和.h文件所在路径，这里根据工程的需要添加。
	4.设置调试模式：需要在Project->Option for target "xxxxx"->Debug修改。由于使用的是ST-Link Debugger，所以配置为对应的即可。点击“Setting"，然后在弹出的页面中
	  修改Port下拉框，选择为SW，然后右侧会显示当前支持SW的设备，如果没有，则需要检查ST-Link的驱动是否安装好。然后再点击”Flash Download“,在新页面中选中”Reset and Run"。
	  在Programming Algorithm中，添加MCU对应的Flash，STM32F103C8T6使用的是STM32F10x Med-denisity Flash 128K。
	