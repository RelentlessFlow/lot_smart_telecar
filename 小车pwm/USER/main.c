#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"



void car_go(void) //前进
 {
	 TIM_SetCompare3(TIM5,0);//左前轮
	 TIM_SetCompare4(TIM5,499);
	 TIM_SetCompare1(TIM5,0);//右前轮
	 TIM_SetCompare2(TIM5,499);
	 TIM_SetCompare3(TIM3,0);//左后轮
	 TIM_SetCompare4(TIM3,499);
	 TIM_SetCompare1(TIM3,0);//右后轮
	 TIM_SetCompare2(TIM3,499);
}
 
 void car_background(void)//后退
 {
	 TIM_SetCompare3(TIM5,499);//左前轮
	 TIM_SetCompare4(TIM5,0);
	 TIM_SetCompare1(TIM5,499);//右前轮
	 TIM_SetCompare2(TIM5,0);
	 TIM_SetCompare3(TIM3,499);//左后轮
	 TIM_SetCompare4(TIM3,0);
	 TIM_SetCompare1(TIM3,499);//右后轮
	 TIM_SetCompare2(TIM3,0);
}
 void car_left_0(void)//左转
 {
	 TIM_SetCompare3(TIM5,499);//左前轮
	 TIM_SetCompare4(TIM5,499);
	 TIM_SetCompare1(TIM5,0);//右前轮
	 TIM_SetCompare2(TIM5,499);
	 TIM_SetCompare3(TIM3,499);//左后轮
	 TIM_SetCompare4(TIM3,499);
	 TIM_SetCompare1(TIM3,0);//右后轮
	 TIM_SetCompare2(TIM3,499);
}
 void car_right_0(void)//右转
 {
	 TIM_SetCompare3(TIM5,0);//左前轮
	 TIM_SetCompare4(TIM5,499);
	 TIM_SetCompare1(TIM5,499);//右前轮
	 TIM_SetCompare2(TIM5,499);
	 TIM_SetCompare3(TIM3,0);//左后轮
	 TIM_SetCompare4(TIM3,499);
	 TIM_SetCompare1(TIM3,499);//右后轮
	 TIM_SetCompare2(TIM3,499);
}
void car_stop(void)//停止
{
	  TIM_SetCompare3(TIM5,499);//左前轮
	 TIM_SetCompare4(TIM5,499);
	 TIM_SetCompare1(TIM5,499);//右前轮
	 TIM_SetCompare2(TIM5,499);
	 TIM_SetCompare3(TIM3,499);//左后轮
	 TIM_SetCompare4(TIM3,499);
	 TIM_SetCompare1(TIM3,499);//右后轮
	 TIM_SetCompare2(TIM3,499);
}
	
void car_left(void)//停止
{
	 TIM_SetCompare2(TIM5,699);//左前轮  
	TIM_SetCompare1(TIM5,199);//左前轮	 
	TIM_SetCompare4(TIM5,199);//右前轮	
	TIM_SetCompare3(TIM5,699);//右前轮	
	TIM_SetCompare2(TIM3,699);//左后轮	
	TIM_SetCompare1(TIM3,199);//左后轮	
	TIM_SetCompare4(TIM3,199);//右后轮	
	TIM_SetCompare3(TIM3,699);//右后轮	
}

void car_right(void){
  TIM_SetCompare2(TIM5,199);//左前轮  
	TIM_SetCompare1(TIM5,699);//左前轮	 
	TIM_SetCompare4(TIM5,699);//右前轮	
	TIM_SetCompare3(TIM5,199);//右前轮	
	TIM_SetCompare2(TIM3,199);//左后轮	
	TIM_SetCompare1(TIM3,699);//左后轮	
	TIM_SetCompare4(TIM3,699);//右后轮	
	TIM_SetCompare3(TIM3,199);//右后轮	
}


 int main(void)
 {		
 //	u16 led0pwmval=0;
	//u8 dir=1;	
u8 left;
u8 right;
char on=0;
	int i=0;
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	 //串口初始化为115200
 	LED_Init();			     //LED端口初始化
 	TIM3_PWM_Init(699,0);	 //不分频。PWM频率=72000000/900=80Khz
	TIM5_PWM_Init(699,0);


	    
	  while(1){
		 right = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12);
		 left = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_0);
		  if(i==4){ //停四次
			car_go();
			//delay_ms(500);
			delay_ms(2700);
			car_left();
			//delay_ms(1800);
			delay_ms(600);
			car_stop();
			delay_ms(4000);
			  i++;
		
		}
		else if(i==6){//停五次
			car_go();
			delay_ms(75);
			car_stop();	
			delay_ms(10000);
			car_stop();	
			delay_ms(10000);
			car_stop();	
			delay_ms(10000);
			car_stop();	
			delay_ms(10000);
			car_stop();	
			delay_ms(10000);
			car_stop();	
			delay_ms(10000);
			car_stop();	
		}
			else if(i==7){//停五次
			car_stop();	
		}
		 if(!left&&!right){//都收到信号 反0
			 on=1;
			 car_go();

		
		}else if(right==0){//右收到信号
			car_right();
		}
		else if(left==0){//左收到信号
			car_left();
		}
		else if(left&&right&&on){ 
			i++;
			car_stop();
			delay_ms(5000);
			car_go();
			delay_ms(3000);
			 car_go();
		}
		else{
		car_stop();
		}
		
		delay_ms(10);

		
	 }
 }