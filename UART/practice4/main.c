/**
 *@文件：UCS/practice3/main.c
 *@作者：粟佳鑫
 *@版本：V1.0.0
 *@日期2017年6月20日
 *@简介：使用GPIO口的输出功能
 *       将MCLK=8MHz，SMCLK=1MHz，ACLK=32.768KHz
 *       设置串口UART1波特率为9600,8位数据，无校验，无地址（空闲线）
 *       点按钮S1发送‘a’
 *       点按钮S2发送‘b’
 *       点按钮S3发送‘c’
 *       点按钮S4发送‘d’     
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
  //设置S1-S4按键输入模式，上升沿中断
  P1DIR&=~(BIT0+BIT1+BIT2+BIT3);
  P1IES|=(BIT0+BIT1+BIT2+BIT3);
  P1IE|=(BIT0+BIT1+BIT2+BIT3);
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
 *@简介：处理PORT1中断
 *@参数：无
 *@返回值：无
 */
#pragma vector=PORT1_VECTOR
__interrupt
void PORT1_ISR(void)
{
  while(!(IFG2&UTXIFG1));
  switch(P1IFG)
  {
  case 0x00:
    break;
  case 0x01:
    TXBUF1='a';
    break;
  case 0x02:
    TXBUF1='b';
    break;  
  case 0x04:
    TXBUF1='c';
    break;
  case 0x08:
    TXBUF1='d';
    break;
  default:
    break;
  }
  P1IFG=0x00;
}