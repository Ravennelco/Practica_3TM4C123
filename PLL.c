#include "lib/include.h"
extern void Configurar_PLL(uint16_t reloj)
{
  // 0) Use RCC2
  SYSCTL->RCC2 |=  0x80000000;  // USERCC2
  // 1) bypass PLL while initializing
  SYSCTL->RCC2 |=  0x00000800;  // BYPASS2, PLL bypass
  // 2) select the crystal value and oscillator source
  SYSCTL->RCC = (SYSCTL->RCC &~0x000007C0)   // clear XTAL field, bits 10-6
                 + 0x00000540;   // 10101, configure for 16 MHz crystal
  SYSCTL->RCC2 &= ~0x00000070;  // configure for main oscillator source
  // 3) activate PLL by clearing PWRDN
  SYSCTL->RCC2 &= ~0x00002000;
  // 4) set the desired system divider
  SYSCTL->RCC2 |= 0x40000000;   // use 400 MHz PLL
  //RCC2[28:21]=SYSDIV2 400MHz/(x+1) = 50MHz
  SYSCTL->RCC2 = (SYSCTL->RCC2&~ 0x1FC00000)  // clear system clock divider
                  + (reloj<<22);      // configure for 80 MHz clock
  // 5) wait for the PLL to lock by polling PLLLRIS
  while((SYSCTL->RIS&0x00000040)==0){};  // wait for PLLRIS bit
  // 6) enable use of PLL by clearing BYPASS
  SYSCTL->RCC2 &= ~0x00000800;
}