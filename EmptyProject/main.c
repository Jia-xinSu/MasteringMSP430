/**
 *@文件：EmptyProject/main.c
 *@作者：粟佳鑫
 *@版本：V1.0.0
 *@日期2017年6月20日
 *@简介：空的主程序模板
 *@编译环境：IAR for 430 7.10.3
 */
/**
 *添加头文件
 */
#include "msp430f149.h"
/**
 *添加宏定义
 */

/**
 *申明函数
 */

/**
 *添加全局变量
 */

int main( void )
{
  //加入初始化代码
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  while(1)
  {
    //加入主程序代码
  }
}
