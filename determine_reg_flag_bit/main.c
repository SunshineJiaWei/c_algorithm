/* 题目描述： 
假设你在一个基于 ARM Cortex-M 系列的单片机项目上开发。
系统有一个 32 位的全局状态寄存器 uint32_t status_reg，每一位代表一个外设或模块的异常状态（1 表示异常，0 表示正常）。 
请写一个 C 语言函数 uint8_t count_set_bits(uint32_t n)，返回该寄存器中异常位的总数量。
*/

#include <stdio.h>
#include <stdint.h>

// 暴力破解
// uint8_t count_set_bits(uint32_t status_reg)
// {
//     uint8_t count = 0;
//     for (uint8_t i = 0; i < 32; i++)
//     {
//         if (status_reg & (1 << i))
//         {
//             count ++;
//         }
//     }
//     return count;
// }

// 减法错位算法
// 因为寄存器标志位都是稀疏的，这个算法极大提高了执行效率，有几位1则执行几次，无1则不执行
uint8_t count_set_bits(uint32_t status_reg)
{
    uint8_t count = 0;
    while (status_reg)
    {
        count ++;
        status_reg &= (status_reg - 1); // 这一步每次能消除最右边那一位1
    }
    return count;
}

void main(void)
{
    uint32_t status_reg = 0x00000003;
    uint8_t count = count_set_bits(status_reg);
    printf("count = %d", count);
}