/**
 *@�ļ���UCS/practice2/main.c
 *@���ߣ��ڼ���
 *@�汾��V1.0.0
 *@����2017��6��20��
 *@��飺ʹ��GPIO�ڵ��������
 *       ��MCLK=8MHz��SMCLK=1MHz��ACLK=32.768KHz
 *       ʹ��TimerA��ʱ��������ʱ
 *       ��ʱ1s��˸LED��
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
void delay(unsigned int ms);
/**
 *���ȫ�ֱ���
 */
unsigned int delayMsRemain=0;
int main( void )
{
  //�����ʼ������
  // �رտ��Ź���ʱ������ֹ�������
  WDTCTL = WDTPW + WDTHOLD;
  //����ʱ��
  BCSCTL1=0x00;
  BCSCTL2=SELM_2+DIVM_0+SELS+DIVS_3;
  //�������������ж�
  IE1|=OFIE;
  IE1&=~(OFIE);
  //�������ж�
  __bis_SR_register(GIE);
  while(state);
  //����TimerA
  TACCR0=8000;
  TACTL=TASSEL1+TACLR+TAIE;
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
  state=0;
}

/**
 *@��飺����TIMERA�ж�
 *@��������
 *@����ֵ����
 */
#pragma vector=TIMERA0_VECTOR
__interrupt
void TimerA0_ISR(void)
{
  if()
}

/**
 *@��飺��׼��ʱһ��ʱ��
 *@���� ms��������
 *@����ֵ����
 */
void delay(unsigned int ms)
{
  delayMsRemain=ms;
  while(delayMsRemain);
}