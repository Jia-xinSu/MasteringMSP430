/**
 *@文件：UCS/practice2/main.c
 *@作者：粟佳鑫
 *@版本：V1.0.0
 *@日期2017年6月20日
 *@简介：使用GPIO口的输出功能
 *       将MCLK=8MHz，SMCLK=1MHz，ACLK=32.768KHz
 *       似的P6.0口接的LED灯1s取反一次，闪烁
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
  
  BCSCTL1=0x00;
  BCSCTL2=SELM_2+DIVM_0+SELS+DIVS_3;
  //开启振荡器错误中断
  IE1|=OFIE;
  IE1&=~(OFIE);
  //开启总中断
  __bis_SR_register(GIE);
  while(state);
  P6DIR|=BIT0;
  while(1)
  {
  //加入主程序代码
    P6OUT^=BIT0;
    __delay_cycles(8000000);
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
