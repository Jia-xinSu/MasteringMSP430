/**
 *@�ļ���UCS/practice1/main.c
 *@���ߣ��ڼ���
 *@�汾��V1.0.0
 *@����2017��6��20��
 *@��飺����MSP430f149��ʱ��ģ��
 *       ��MCLK=8MHz��SMCLK=1MHz��ACLK=32.768KHz
 *       ��P5�ڽ���Ӧʱ���ź����
 *       
 *@���뻷����IAR for 430 7.10.3
 */
/**
 *���ͷ�ļ�
 */
#include "msp430f149.h"
/**
 *��Ӻ궨��
 */

/**
 *��������
 */

/**
 *���ȫ�ֱ���
 */

int main( void )
{
  //�����ʼ������
  // �رտ��Ź���ʱ������ֹ�������
  WDTCTL = WDTPW + WDTHOLD;
  
  BCSCTL1=0x00;
  BCSCTL2=SELM_2+DIVM_0+SELS+DIVS_3;
  //�������������ж�
  IE1|=OFIE;
  IE1&=~(OFIE);
  //�������ж�
  __bis_SR_register(GIE);
  //����P5.4��P5.5��P5.6Ϊ���⹦�ܿ�
  P5SEL|=BIT4+BIT5+BIT6;
  //����P5.4��P5.5��P5.6Ϊ���ģʽ
  while(1)
  {
    //�������������
  }
}       

/**
 *@��飺����NMU�ж�
 *@��������
 *@����ֵ����
 */
#pragma vector=NMI_VECTOR
__interrupt
void NMI_ISR(void)
{
  do
  {
    //����жϱ��λ
    IFG1&=~OFIFG;
  }
  //�ȴ�ʱ�����������λ������1
  while(IFG1&OFIFG);
}
