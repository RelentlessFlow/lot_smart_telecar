#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"



void car_go(void) //ǰ��
 {
	 TIM_SetCompare3(TIM5,0);//��ǰ��
	 TIM_SetCompare4(TIM5,499);
	 TIM_SetCompare1(TIM5,0);//��ǰ��
	 TIM_SetCompare2(TIM5,499);
	 TIM_SetCompare3(TIM3,0);//�����
	 TIM_SetCompare4(TIM3,499);
	 TIM_SetCompare1(TIM3,0);//�Һ���
	 TIM_SetCompare2(TIM3,499);
}
 
 void car_background(void)//����
 {
	 TIM_SetCompare3(TIM5,499);//��ǰ��
	 TIM_SetCompare4(TIM5,0);
	 TIM_SetCompare1(TIM5,499);//��ǰ��
	 TIM_SetCompare2(TIM5,0);
	 TIM_SetCompare3(TIM3,499);//�����
	 TIM_SetCompare4(TIM3,0);
	 TIM_SetCompare1(TIM3,499);//�Һ���
	 TIM_SetCompare2(TIM3,0);
}
 void car_left_0(void)//��ת
 {
	 TIM_SetCompare3(TIM5,499);//��ǰ��
	 TIM_SetCompare4(TIM5,499);
	 TIM_SetCompare1(TIM5,0);//��ǰ��
	 TIM_SetCompare2(TIM5,499);
	 TIM_SetCompare3(TIM3,499);//�����
	 TIM_SetCompare4(TIM3,499);
	 TIM_SetCompare1(TIM3,0);//�Һ���
	 TIM_SetCompare2(TIM3,499);
}
 void car_right_0(void)//��ת
 {
	 TIM_SetCompare3(TIM5,0);//��ǰ��
	 TIM_SetCompare4(TIM5,499);
	 TIM_SetCompare1(TIM5,499);//��ǰ��
	 TIM_SetCompare2(TIM5,499);
	 TIM_SetCompare3(TIM3,0);//�����
	 TIM_SetCompare4(TIM3,499);
	 TIM_SetCompare1(TIM3,499);//�Һ���
	 TIM_SetCompare2(TIM3,499);
}
void car_stop(void)//ֹͣ
{
	  TIM_SetCompare3(TIM5,499);//��ǰ��
	 TIM_SetCompare4(TIM5,499);
	 TIM_SetCompare1(TIM5,499);//��ǰ��
	 TIM_SetCompare2(TIM5,499);
	 TIM_SetCompare3(TIM3,499);//�����
	 TIM_SetCompare4(TIM3,499);
	 TIM_SetCompare1(TIM3,499);//�Һ���
	 TIM_SetCompare2(TIM3,499);
}
	
void car_left(void)//ֹͣ
{
	 TIM_SetCompare2(TIM5,699);//��ǰ��  
	TIM_SetCompare1(TIM5,199);//��ǰ��	 
	TIM_SetCompare4(TIM5,199);//��ǰ��	
	TIM_SetCompare3(TIM5,699);//��ǰ��	
	TIM_SetCompare2(TIM3,699);//�����	
	TIM_SetCompare1(TIM3,199);//�����	
	TIM_SetCompare4(TIM3,199);//�Һ���	
	TIM_SetCompare3(TIM3,699);//�Һ���	
}

void car_right(void){
  TIM_SetCompare2(TIM5,199);//��ǰ��  
	TIM_SetCompare1(TIM5,699);//��ǰ��	 
	TIM_SetCompare4(TIM5,699);//��ǰ��	
	TIM_SetCompare3(TIM5,199);//��ǰ��	
	TIM_SetCompare2(TIM3,199);//�����	
	TIM_SetCompare1(TIM3,699);//�����	
	TIM_SetCompare4(TIM3,699);//�Һ���	
	TIM_SetCompare3(TIM3,199);//�Һ���	
}


 int main(void)
 {		
 //	u16 led0pwmval=0;
	//u8 dir=1;	
u8 left;
u8 right;
char on=0;
	int i=0;
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
 	LED_Init();			     //LED�˿ڳ�ʼ��
 	TIM3_PWM_Init(699,0);	 //����Ƶ��PWMƵ��=72000000/900=80Khz
	TIM5_PWM_Init(699,0);


	    
	  while(1){
		 right = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12);
		 left = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_0);
		  if(i==4){ //ͣ�Ĵ�
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
		else if(i==6){//ͣ���
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
			else if(i==7){//ͣ���
			car_stop();	
		}
		 if(!left&&!right){//���յ��ź� ��0
			 on=1;
			 car_go();

		
		}else if(right==0){//���յ��ź�
			car_right();
		}
		else if(left==0){//���յ��ź�
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