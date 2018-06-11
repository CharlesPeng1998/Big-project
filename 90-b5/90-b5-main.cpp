/*1751367 计2 彭健聪*/
#include "90-b5.h"

int main()
{
	//读取LED的设置
	LED_SETUP led_setup;
	led_setup.read_cfg();

	//读取LED显示的内容
	LED_CONTENT led_content;
	led_content.read_cfg();
	led_content.display_content(led_setup);

	return 0;
}