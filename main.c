#include <reg52.h>

void ConfigUART(unsigned int baud);

void main() {
	
	EA = 1; // ȫ���ж�ʹ��
	ConfigUART(9600);
	
	while (1) {
//		// RI �����жϱ�־λ��������û����ʱһֱ���գ�
//		// ���ս�������� SBUF �У�
//		// �Ż��㣺��Ӧ����׼ѭ������ʱ�ȴ���
//		// ��Ӧ�����ж��н���״̬���������
//		while (!RI);
//		RI = 0;
//		
//		// ��ʽ�ұߵ� SBUF �����Խ���ģ��ģ�
//		// ��ʽ��ߵ� SBUF �����Է���ģ���
//		SBUF = SBUF + 1; // TxdBuf = RxdBuf + 1
//		
//		// TI �����жϱ�ʾλ��������û����ʱһֱ����
//		while (!TI);
//		TI = 0;
	}
}

void ConfigUART(unsigned int baud) {
	// SCON 0101 0000
	// SM1=1, REN=1������ͨ��ģʽ1
	SCON = 0x50;
	TMOD &= 0x0F; // Timer1
	TMOD |= 0x20; // Reload mode
	TH1 = 256 - (11059200/12/32)/baud;
	TL1 = TH1;
	ET1 = 0; // ʹ��T1��Ϊ�����ʷ�����������ֹT1������ʱ��
	ES = 1; // ʹ�ܴ����ж�
	TR1 = 1;
}

void InterruptUART() interrupt 4 {
	// ����ǽ����жϱ�־λ
	if (RI) {
		RI = 0;
		SBUF = SBUF + 1;
	}
	// ����Ƿ����жϱ�־λ
	if (TI) {
		TI = 0;
	}
}