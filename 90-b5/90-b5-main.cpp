/*1751367 ��2 ����*/
#include "90-b5.h"

int main()
{
	//��ȡLED������
	LED_SETUP led_setup;
	led_setup.read_cfg();

	//��ȡLED��ʾ������
	LED_CONTENT led_content;
	led_content.read_cfg();
	led_content.display_content(led_setup);

	return 0;
}