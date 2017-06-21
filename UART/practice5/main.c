/**
 *@文件：UCS/practice3/main.c
 *@作者：粟佳鑫
 *@版本：V1.0.0
 *@日期2017年6月20日
 *@简介：使用GPIO口的输出功能
 *       将MCLK=8MHz，SMCLK=1MHz，ACLK=32.768KHz
 *       设置串口UART1波特率为9600,8位数据，无校验，无地址（空闲线）
 *       利用串口向单片机发字节数据，板载的LED灯显示该数据对应的二进制值
 *@编译环境：IAR for 430 7.10.3
 */
/**
 *添加头文件
 */
#include "msp430f149.h"
/**
 *添加宏定义
 */
int state=1;
/**
 *申明函数
 */

/**
 *添加全局变量
 */

int main( void )
{
  //加入初始化代码
  // 关闭看门狗定时器，防止溢出重启
  WDTCTL = WDTPW + WDTHOLD;
  //配置时钟，ACLK=XT1，SMCLK=XT2/8，MCLK=XT2
  BCSCTL1=0x00;
  BCSCTL2=SELM_2+DIVM_0+SELS+DIVS_3;
  //开启振荡器错误中断
  IE1|=OFIE;
  IE1&=~(OFIE);
  //开启总中断
  __bis_SR_register(GIE);
  while(state);
  //初始化串口I/O
  P3SEL|=BIT6+BIT7;
  P3DIR&=~BIT7;
  P3DIR|=BIT6;
  //初始化UART0
  ME2|=UTXE1+URXE1;//允许使用串口URAT0的输入输出功能
  U1CTL|=CHAR; //8位数据位
  U1TCTL|=SSEL1;//SMCLK=1MHZ
  U1BR0=104;
  U1BR1=0;
  U1MCTL=0;
  U1CTL&=~SWRST;
  //开启UART1的接受中断
  IE2|=URXIE1;
  //初始化D1-D8灯
  P6DIR=0xff;
  while(1)
  {
  //加入主程序代码

  }
}       

/**
 *@简介：处理NMU中断
 *@参数：无
 *@返回值：无
 */
#pragma vector=NMI_VECTOR
__interrupt
void NMI_ISR(void)
{
  do
  {
    //清除中断标记位
    IFG1&=~OFIFG;
  }
  //等待时钟启动，标记位不再置1
  while(IFG1&OFIFG);
  state=0;
}

/**
 *@简介：处理UART1RX中断
 *@参数：无
 *@返回值：无
 */
#pragma vector=UART1RX_VECTOR
__interrupt
void UART1RX_ISR(void)
{
  P6OUT=U1RXBUF;
}
