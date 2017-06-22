/**
 *@文件：UCS/practice2/main.c
 *@作者：粟佳鑫
 *@版本：V1.0.0
 *@日期2017年6月20日
 *@简介：使用GPIO口的输出功能
 *       将MCLK=8MHz，SMCLK=1MHz，ACLK=32.768KHz
 *       使用TimerA定时器进行延时
 *       延时1s闪烁LED灯
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
void delay(unsigned int ms);
/**
 *添加全局变量
 */
unsigned int delayMsRemain=0;
int main( void )
{
  //加入初始化代码
  // 关闭看门狗定时器，防止溢出重启
  WDTCTL = WDTPW + WDTHOLD;
  //配置时钟
  BCSCTL1=0x00;
  BCSCTL2=SELM_2+DIVM_0+SELS+DIVS_3;
  //开启振荡器错误中断
  IE1|=OFIE;
  IE1&=~(OFIE);
  //开启总中断
  __bis_SR_register(GIE);
  while(state);
  //配置TimerA
  TACCR0=8000;
  TACTL=TASSEL1+TACLR+TAIE;
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
 *@简介：处理TIMERA中断
 *@参数：无
 *@返回值：无
 */
#pragma vector=TIMERA0_VECTOR
__interrupt
void TimerA0_ISR(void)
{
  if()
}

/**
 *@简介：精准延时一段时间
 *@参数 ms：毫秒数
 *@返回值：无
 */
void delay(unsigned int ms)
{
  delayMsRemain=ms;
  while(delayMsRemain);
}