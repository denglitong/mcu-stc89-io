#include <reg52.h>

void ConfigUART(unsigned int baud);

void main() {
	
	EA = 1; // 全局中断使能
	ConfigUART(9600);
	
	while (1) {
//		// RI 接收中断标志位，当接收没结束时一直接收，
//		// 接收结果保存在 SBUF 中；
//		// 优化点：不应该在准循环中延时等待，
//		// 而应该在中断中进行状态检测与重置
//		while (!RI);
//		RI = 0;
//		
//		// 等式右边的 SBUF 是来自接收模块的，
//		// 等式左边的 SBUF 是来自发送模块的
//		SBUF = SBUF + 1; // TxdBuf = RxdBuf + 1
//		
//		// TI 发送中断标示位，当发送没结束时一直发送
//		while (!TI);
//		TI = 0;
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
	ET1 = 0; // 使能T1作为波特率发生器，而禁止T1用作定时器
	ES = 1; // 使能串口中断
	TR1 = 1;
}

void InterruptUART() interrupt 4 {
	// 如果是接收中断标志位
	if (RI) {
		RI = 0;
		SBUF = SBUF + 1;
	}
	// 如果是发送中断标志位
	if (TI) {
		TI = 0;
	}
}