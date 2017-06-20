/**
 *@�ļ���UCS/practice3/main.c
 *@���ߣ��ڼ���
 *@�汾��V1.0.0
 *@����2017��6��20��
 *@��飺ʹ��GPIO�ڵ��������
 *       ��MCLK=8MHz��SMCLK=1MHz��ACLK=32.768KHz
 *       ����S1��D1��Ϩ�𣬷�����
 *       ����S2ʱ��D2��ȡ��
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
int state=1;
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
  //����ʱ�ӣ�ACLK=XT1��SMCLK=XT2/8��MCLK=XT2
  BCSCTL1=0x00;
  BCSCTL2=SELM_2+DIVM_0+SELS+DIVS_3;
  //�������������ж�
  IE1|=OFIE;
  IE1&=~(OFIE);
  //�������ж�
  __bis_SR_register(GIE);
  while(state);
  //����P6.0��P6.1Ϊ�������
  P6DIR|=BIT0+BIT1;
  //����P1.0��P1.1Ϊ���뷽��
  P1DIR&=~(BIT0+BIT1);
  //��P1.1�ڵ��жϹ���
  P1IE|=BIT1;
  //����P1.1��Ϊ��->�ʹ���
  P1IES|=BIT1;
  while(1)
  {
  //�������������
    if(P1IN&BIT0)
    {
      P6OUT&=~BIT0;
    }
    else
    {
      P6OUT|=BIT0;
    }
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
  state=0;
}

/**
 *@��飺����PORT1�ж�
 *@��������
 *@����ֵ����
 */
#pragma vector=PORT1_VECTOR
__interrupt
void PORT1_ISR(void)
{
  switch(P1IFG)
  {
  case 0x00:
    break;
  case 0x01:
    break;
  case 0x02:
    P6OUT^=BIT1;
    break;  
  default:
    break;
  }
  P1IFG=0x00;
}