/**
 *@�ļ���EmptyProject/main.c
 *@���ߣ��ڼ���
 *@�汾��V1.0.0
 *@����2017��6��20��
 *@��飺�յ�������ģ��
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
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  while(1)
  {
    //�������������
  }
}
