#include <reg52.h>

void ConfigUART(unsigned int baud);

void main() {
	
	ConfigUART(9600);
	
	while (1) {
		// RI 接收中断标志位，当接收没结束时一直接收，
		// 接收结果保存在 SUB中
		while (!RI);
		RI = 0;
		// 等式右边的 SBUF 是来自接收模块的，
		// 等式左边的 SBUF 是来自发送模块的
		SBUF = SBUF + 1; // TxdBuf = RxdBuf + 1
		
		// TI 发送中断标示位，当发送没结束时一直发送
		while (!TI);
		TI = 0;
	}
}

void ConfigUART(unsigned int baud) {
	// SCON 0101 0000
	// SM1=1, REN=1，串行通信模式1
	SCON = 0x50;
	TMOD &= 0x0F; // Timer1
	TMOD |= 0x20; // Reload mode
	TH1 = 256 - (11059200/12/32)/baud;
	TL1 = TH1;
	ET1 = 0; // 用T1座波特率发生器的时候，T1就不能用作定时器
	TR1 = 1;
}