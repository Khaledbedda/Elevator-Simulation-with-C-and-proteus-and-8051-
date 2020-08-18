 #include <c8051f020.h> 
sbit led1 = P1^7;		/* set test pin0 of port1 */
sbit led_g = P1^6;
sbit led_b = P1^5;
sbit ir1 = P3^6 ;
sbit ir2 = P3^7 ;
int enter = 0 ;
int leave = 0 ;
int persons = 0 ;
unsigned int lookUpTable[5]={63,6,91,79,102};
int currFloor =0;
int i =0;
sbit motor1 = P3^0 ; 
sbit motor2 = P3^1 ; 
unsigned int floors[5]={0};
sbit floor0 = P1^4 ;
sbit floor1 = P1^3 ;
sbit floor2 = P1^2 ;
sbit floor3 = P1^1 ;
sbit floor4 = P1^0 ;

void delay(){

int i = 0;
int j = 0;
for (i=0;i<500;++i){
	for(j=0;j<100;++j){
	
	}
}
}
void door_delay(){
int i = 0;
int j = 0;
for (i=0;i<2000;++i){
	for(j=0;j<200;++j){
	  if ((ir1 == 0) && (ir2 ==1))
	{ if(leave == 0){enter=1;}
		if(leave==1){persons-- ; leave = 0; delay();}
	}
	  if ((ir1 == 1) && (ir2 ==0))
	{ if(enter == 0){leave=1;}
		if(enter==1){persons++ ; enter = 0; delay();}
	}
	}
}
}
void motor_delay(){
int i = 0;
int j = 0;
for (i=0;i<1000;++i){
	for(j=0;j<100;++j){
	
	}
}
}

void motor_delay1(){
int i = 0;
int j = 0;
for (i=0;i<1000;++i){
	for(j=0;j<90;++j){
	
	}
}
}
void ascend(){
motor1 = 1 ;
motor2 = 0;
motor_delay();
motor1 = 0 ;
	motor2=1;
	motor_delay1();
	motor2=0;
}

void descend(){
motor1 = 0 ; 
motor2 = 1 ;
motor_delay();
	motor2 = 0 ;
	motor1=1 ;
		motor_delay1();
	motor1=0;
}



void open_door() {
		led_g =1 ;
	led_b = 0 ;
	door_delay();	
	led_b=1 ; 
	led_g = 0 ; 
	
}



void checkrequest(){
  if(!floor0)   floors[0]=1;
	if(!floor1)   floors[1]=1;
	if(!floor2)   floors[2]=1;
	if(!floor3)   floors[3]=1;
	if(!floor4)   floors[4]=1;
}
void Timer_init()
{
	TMOD = 0x11;		/* Timer0 mode1 */
	TH0 = 0xDD;		/* 50ms timer value */
	TL0 = 0x00;        	      	/* Start timer0 */  
	TR0 = 1;	
  	      	/* Start timer0 */
}


void Timer0_ISR() interrupt 1	/* Timer0 interrupt service routine (ISR) */
{
	 checkrequest();

     
}


void Ext_int_Init()				
{
	EA  = 1;	/* Enable global interrupt */	/* Enable Ext. interrupt0 */
	EX1 =1 ;      	/* Select Ext. interrupt0 on falling edge */
	IT1 = 1 ;
}




void External1_ISR() interrupt 2
{
open_door();
}


int main(void)
{
	Timer_init();
	Ext_int_Init();
	P0= 0xFF;
	led1=0;
	led_g = 0;
	led_b = 1; 
	P3 = 0xC0;
	EA  = 1;         	/* Enable global interrupt */
	ET0 = 1;          /* Enable timer0 interrupt */
P2 =63;

  	while(1) {
		if (persons > 4 ){led1 = 1; continue; }
		if (persons< 5) {led1 = 0 ; }
		i=0;
for(i=0;i<5;i++){
if(floors[i] && i>currFloor){
	while(currFloor != i ){
		ascend();
		currFloor++;
		P2 = lookUpTable[currFloor];
		if(floors[currFloor]){ open_door(); floors[currFloor]=0;}
	}
}
}

i=4;

for(i=4;i>=0;i--){
if(floors[i] && i<currFloor){
	while(currFloor != i ){
		descend();
		currFloor--;
		P2 = lookUpTable[currFloor];
		if(floors[currFloor]) { open_door(); floors[currFloor]=0;}
	}
}
}


}
		}
