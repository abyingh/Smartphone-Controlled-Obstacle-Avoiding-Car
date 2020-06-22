int dis;			//define distance integer
char v;				//define character a for Read Data

void delay (unsigned int);	//delay
void distance ();		//distance

void distance()   {

  TRISB = 0b00010000;		//assign Echo pin as input
  T1CON = 0x10;			//initialize timer module
  while(1)
  {
    TMR1H = 0;			//sets the initial value of timer
    TMR1L = 0;			//sets the initial value of timer

    PORTB.F0 = 1;		//trigger HIGH
    delay(10);			//delay 10µs
    PORTB.F0 = 0;		//trigger LOW

    while(!PORTB.F4);		//wait for Echo
    T1CON.F0 = 1;		//start timer
    while(PORTB.F4);		//wait for Echo to go LOW
    T1CON.F0 = 0;		//stop timer

    dis = (TMR1L | (TMR1H<<8));	                //read timer value
    dis = dis/58.82;				//convert time to distance (cm)
    dis = dis + 1;				//distance calibration
}
}
void main()
{
  C1ON_bit = 0;
  C2ON_bit = 0; 			// disable comparators
   RC1IE_bit=1;			        //turn on interrupt on UART1 recieve
   RC1IF_bit=0;			        //clear interrupt flag
   PEIE_bit = 1;			//enable peripheral interrupts
   GIE_bit = 1;			        //enable global interrupts

   TRISD=0;				//make D (motor controller) ports outputs
   TRISC=0xC0;			        // make RX - TX pins input

   PWM1_Init(5000);		        // initialize PWM1 at 5kHz (reference frequency)
   PWM2_Init(5000);		        // initialize PWM2 at 5kHz (reference frequency)
   PWM1_Start();			//start PWM1
   PWM2_Start();			//start PWM2
   UART1_Init(9600);		        //initialize UART at 9.6kHz reference frequency
 while (1) {				//infinite loop

 distance();			         //measure distance
 if (v=='F' && d>30)	                 //if "F" is pressed and distance greater than 30cm
      {
          PORTD=0x05;		         //execute motors
          PWM1_Set_Duty(100);            //set current duty for PWM1
          PWM2_Set_Duty(100);            //set current duty for PWM2
         distance();		         //measure distance
if (d<30) {			         //if less than 30
PWM1_Set_Duty(0);		         //stop PWM1
PWM2_Set_Duty(0);		         //stop PWM2
  	  }
   	  }

if (v=='L' && d>30)	                  //if "F" is pressed and distance greater than 30cm
      {
          PORTD=0x01;		          //execute motors
          PWM1_Set_Duty(100);            //set current duty for PWM1
          PWM2_Set_Duty(100);            //set current duty for PWM2
         distance();		         //measure distance
if (d<30) {			         //if less than 30
PWM1_Set_Duty(0);		         //stop PWM1
PWM2_Set_Duty(0);		         //stop PWM2
  	  }
   	  }

if (v=='R' && d>30)	                 //if "F" is pressed and distance greater than 30cm
      {
          PORTD=0x04;		         //execute motors
          PWM1_Set_Duty(100);            //set current duty for PWM1
          PWM2_Set_Duty(100);            //set current duty for PWM2
         distance();		         //measure distance
if (d<30) {			         //if less than 30
PWM1_Set_Duty(0);	          	//stop PWM1
PWM2_Set_Duty(0);		        //stop PWM2
  	  }
   	  }

if (v=='B' && d>30)	                //if "F" is pressed and distance greater than 30cm
      {
          PORTD=0x0A;		        //execute motors
          PWM1_Set_Duty(100);          //set current duty for PWM1
          PWM2_Set_Duty(100);          //set current duty for PWM2
         distance();		         //measure distance
if (d<30) {			         //if less than 30
PWM1_Set_Duty(0);	          	//stop PWM1
PWM2_Set_Duty(0);	           	//stop PWM2
  	  }
   	  }




  if (v=='S' && d>30)	              //if "F" is pressed and distance greater than 30cm
      {
          PORTD=0x00;	              //execute motors
          PWM1_Set_Duty(100);         //set current duty for PWM1
          PWM2_Set_Duty(100);         //set current duty for PWM2
         distance();		      //measure distance

   	  }
         }
         }
         
 void interrupt()
{
    if (UART1_Data_Ready()) 	      //check for receive Interupt Flag pin (rx pin)
{
      v = UART1_Read();		      //read the received data
 }
 }

        //Delay
         void delay(unsigned int itime)      {
         unsigned char b;
         unsigned int a;
         for(a=0;a<itime;a++)
         for(b=0;b<165;b++) ;
         }
