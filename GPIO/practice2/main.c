/**
 *@�ļ���UCS/practice2/main.c
 *@���ߣ��ڼ���
 *@�汾��V1.0.0
 *@����2017��6��20��
 *@��飺ʹ��GPIO�ڵ��������
 *       ��MCLK=8MHz��SMCLK=1MHz��ACLK=32.768KHz
 *       �Ƶ�P6.0�ڽӵ�LED��1sȡ��һ�Σ���˸
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
  
  BCSCTL1=0x00;
  BCSCTL2=SELM_2+DIVM_0+SELS+DIVS_3;
  //�������������ж�
  IE1|=OFIE;
  IE1&=~(OFIE);
  //�������ж�
  __bis_SR_register(GIE);
  while(state);
  P6DIR|=BIT0;
  while(1)
  {
  //�������������
    P6OUT^=BIT0;
    __delay_cycles(8000000);
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
