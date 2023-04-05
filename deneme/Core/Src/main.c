
#include <stm32f407xx.h>
#define rccahb1enable *((int *)0x40023830U)
typedef struct
{
  uint32_t MODER;    /*!< GPIO port mode register,               Address offset: 0x00      */
   uint32_t OTYPER;   /*!< GPIO port output type register,        Address offset: 0x04      */
   uint32_t OSPEEDR;  /*!< GPIO port output speed register,       Address offset: 0x08      */
  uint32_t PUPDR;    /*!< GPIO port pull-up/pull-down register,  Address offset: 0x0C      */
  uint32_t IDR;      /*!< GPIO port input data register,         Address offset: 0x10      */
   uint32_t ODR;      /*!< GPIO port output data register,        Address offset: 0x14      */
  uint32_t BSRR;     /*!< GPIO port bit set/reset register,      Address offset: 0x18      */
   uint32_t LCKR;     /*!< GPIO port configuration lock register, Address offset: 0x1C      */
   uint32_t AFR[2];   /*!< GPIO alternate function registers,     Address offset: 0x20-0x24 */
} MyGpioDEf;

//#define  gpiodmoderegister  *((int *)0x40020c00U)
//#define   gpiododr *((int *)0x40020c14)


int main()
{
	MyGpioDEf *mygpio=((int *)0x40020C00U);

//set rccahb1en to 1000
rccahb1enable=  0x00000008;
//set mode register to output for pin 14 on gpiod
//gpiodmoderegister= pd14mask;
//gpiodmoderegister=0x04000000;
//set pd14 and 13 to 1 for modreg. which is output
//gpiodmoderegister=0x14000000;
mygpio->MODER=0x14000000;
//// set the output of the above pin to 1=
//turn on the led
//gpiododr=GPIO_ODR_OD13_Msk  ;
mygpio->ODR=GPIO_ODR_OD13_Msk ;
//gpiododr=gpiododr| GPIO_ODR_OD14_Msk;
mygpio->ODR=mygpio->ODR|GPIO_ODR_OD14_Msk;
//turn offg the led

mygpio->ODR=mygpio->ODR|GPIO_ODR_OD14_Msk;
//gpiododr&=( ~pd13mask);
mygpio->ODR=mygpio->ODR&(~GPIO_ODR_OD14_Msk);

}
