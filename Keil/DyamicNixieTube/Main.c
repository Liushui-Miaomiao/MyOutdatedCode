#include <REG52.H>

#define SEGMENT_SELECTION_PORT P0
#define DIGIT_SELECTION_PORT   P2
#define LENGTH(table)          (sizeof(table) / sizeof(table[0]))

typedef unsigned char uchar;
typedef unsigned int  uint;

void loop   (                          );				// 声明循环事件子函数
void delay  (uint t                    );				// 声明延时子函数
void display(uint position, uint number);				// 声明显示子函数

uint       length;										// 数组长度
uchar code numberTable[] = {							// 0~7 的段选码
	0x3F, 0x06, 0x5B, 0x4F,
	0x66, 0x6D, 0x7D, 0x07
};

/* 主函数 */
void main(void) {
	length = LENGTH(numberTable);						// 求数组长度
	SEGMENT_SELECTION_PORT = 0xFF;						// 先关闭数码管
	
	while (1) {
		loop();
	}
}

/* 循环事件 */
void loop() {
	uint i;
	
	for (i = 0; i < length; i++) {
		display(i, i);									// 在第 i 个位置上显示 i
		
		delay(3);										// 延时
		DIGIT_SELECTION_PORT = ~0x00;					// 显示一次关闭一次位选端，去除重影的作用
	}
}

/* 延时函数 延时约 t ms */
void delay(uint t) {
	uint i, j;
	
	for (i = t; i > 0; i--) {
		for (j = 110; j > 0; j--);						// 12MHz 时钟频率
	}
}

/* 显示函数 */
void display(uint position, uint number) {
	DIGIT_SELECTION_PORT = ~(0x01 << position);			// 选择指定段显示
	SEGMENT_SELECTION_PORT = numberTable[number];		// 显示指定数字
}