
#include "lib/include.h"

extern void Configura_Reg_PWM1(uint16_t freq)
{
    SYSCTL->RCGCPWM |= (1<<1); /*Enable reloj de modulo PWM1 pag 354*/
    SYSCTL->RCGCGPIO |= (1<<5); /*Enable reloj de GPIO Puerto F pag 340 pin 5*/
    SYSCTL->RCC &= ~(1<<20);  /*Enable o Disable Divisor  Pag 254*/
   // GPIOF->AFSEL |= (1<<3)|(1<<2)|(1<<1); /*Control de registros ya sea por GPIO o Otros Pag 672*/
    GPIOF->AFSEL |= 0x0E;
    GPIOF->PCTL |= (GPIOF->PCTL&0xFFFF000F) | 0x00005550; /*Combinado con la tabla Pag 1351 y el registro PCTL le digo que es pwm Pag 689*/
    GPIOF->DEN |= (1<<3)|(1<<2)|(1<<1); /* para decirle si es digital o no Pag 682*/
    PWM1->_2_CTL = (0<<0);
    PWM1->_3_CTL = (0<<0); /*Bloqueo y desbloqueo*/
    PWM1->_3_GENB = 0x0000080C; /*Registro de las acciones del pwm Pag 1285*/
    PWM1->_3_GENA = 0x0000008C; /*Registro de las acciones del pwm Pag 1282*/
    PWM1->_2_GENB = 0x0000008C;//PWM5
    PWM1->_3_LOAD = 20000; /*cuentas=fclk/fpwm  para 1khz cuentas = (16,000,000/1000)*/
    PWM1->_2_LOAD = 20000;
    PWM1->_3_CMPB = 15000;
    PWM1->_3_CMPA = 15000;
    PWM1->_2_CMPA = 15000;
    PWM1->_3_CTL = (1<<0);// Se activa el generador 3
    PWM1->_2_CTL = (1<<0);// Se activa el generador 2
    PWM1->ENABLE = (1<<7) | (1<<6) | (1<<5); /*habilitar el bloque pa que pase Pag 1247*/
}
