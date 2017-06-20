/**
 *@文件：UCS/practice3/main.c
 *@作者：粟佳鑫
 *@版本：V1.0.0
 *@日期2017年6月20日
 *@简介：使用GPIO口的输出功能
 *       将MCLK=8MHz，SMCLK=1MHz，ACLK=32.768KHz
 *       按下S1，D1灯熄灭，否则亮
 *       按下S2时，D2灯取反
 *       
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
  //设置P6.0，P6.1为输出方向
  P6DIR|=BIT0+BIT1;
  //设置P1.0，P1.1为输入方向
  P1DIR&=~(BIT0+BIT1);
  //打开P1.1口的中断功能
  P1IE|=BIT1;
  //设置P1.1口为高->低触发
  P1IES|=BIT1;
  while(1)
  {
  //加入主程序代码
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