# MasteringMSP430
## 概述
+ 本工程内的所有文件都是基于DM430-L学习板的
## 文件目录
+ EmptyProject -> 空工程
+ UCS/practice1 -> 配置UCS模块 MCLK=8MHz，SMCLK=1MHz，ACLK=32.768KHz，并在P5.4输出MCLK，P5.5输出SMCLK，P5.6输出ACLK信号
+ GPIO/practice2 -> 以1s为延时闪烁LED灯
+ GPIO/practice3 -> 按下S1按键D1灯灭，松手D1灯亮，每次按下S2按键，D2灯取反（分别用扫描IO口与外部中断实现）
