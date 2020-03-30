#include<reg52.h>
     
    sfr lcd_data_port=0xB0; /* P1 port as data port */
    sbit rs=P2^0; /* Register select pin */
    sbit rw=P2^1; /* Read/Write pin */
    sbit en=P2^2; /* Enable pin */
		sbit ir=P1^0;
		unsigned char c;
		int num[10];
     
     
void delay(unsigned int count)  /* Function to provide delay Approx 1ms */
{
	int i,j;
	for(i=0;i<count;i++)
	for(j=0;j<112;j++);
}
     
void LCD_Command (unsigned char cmd)  /* LCD16x2 command funtion */
{
	lcd_data_port= cmd;
	rs=0; /* command reg. */
	rw=0; /* Write operation */
	en=1;
	delay(1);
	en=0;
	delay(5);
}
     
void LCD_Char (unsigned char char_data)  /* LCD data write function */
{
	lcd_data_port=char_data;
	rs=1; /* Data reg.*/
	rw=0; /* Write operation*/
	en=1;  
	delay(1);
	en=0;
	delay(5);
}

void LCD_integer (unsigned int num) /* Send string to LCD function */
{
	int number[10];
	int k = 0;
	
	for(;num>=0;)  /* Send each char of string till the NULL */
	{
		number[k]=(num%10);
			k++;
			num = num/10;
	}
	k--;
	for(;k>=0;k--)
	{
		c	= number[k]+48;
		lcd_data_port=c;
		rs=1; /* Data reg.*/
		rw=0; /* Write operation*/
		en=1;  
		delay(1);
		en=0;
		delay(5);
	}
}
void lcd_data(unsigned int i)     //Function to send data on LCD
{   int p;
int k=0;
while(i>0)
{
  num[k]=i%10;
  i=i/10;
  k++;
}
k--;
for (p=k;p>=0;p--)
{
  c=num[p]+48;
  lcd_data_port = c;
  rw = 0;
  rs = 1;
  en = 1;
  delay(1);
  en = 0;
}
return;
}
     
void LCD_String (unsigned char *str) /* Send string to LCD function */
{
	int i;
	for(i=0;str[i]!=0;i++)  /* Send each char of string till the NULL */
	{
		LCD_Char (str[i]);  /* Call LCD data write */
	}
}
     
void LCD_String_xy (char row, char pos, char *str)  /* Send string to LCD function */
{
	if (row == 0)
		LCD_Command((pos & 0x0F)|0x80);
	else if (row == 1)
		LCD_Command((pos & 0x0F)|0xC0);
		LCD_String(str); /* Call LCD string function */
}
     
void LCD_Init (void) /* LCD Initialize function */
{
	delay(20); /* LCD Power ON Initialization time >15ms */
	LCD_Command (0x38); /* Initialization of 16X2 LCD in 8bit mode */
	LCD_Command (0x0C); /* Display ON Cursor OFF */
	LCD_Command (0x06); /* Auto Increment cursor */
	LCD_Command (0x01); /* clear display */
	LCD_Command (0x80); /* cursor at home position */
}
void welcome()
{
  LCD_Init(); /* initialization of LCD*/
	LCD_Command(0x0C);
	delay(20);

	LCD_String("  Tachometer");  /* write string on 1st line of LCD*/
	delay(2000);

	LCD_Command(0xc0);
	LCD_String("   Project");  /*write string on 2nd line*/
  delay(1000);

	LCD_Command(0x01);
	LCD_Command(0x0c);
	LCD_String("By-");
	LCD_Command(0xc0);
	LCD_String("  Tashmin Mishra");
	delay(1000);

	LCD_Command(0x01);
	LCD_Command(0x0c);
	LCD_String("By-");
	LCD_Command(0xc0);
	LCD_String("  Feecon Behera");
	delay(1000);

	LCD_Command(0x01);
	LCD_Command(0x0c);
	LCD_String("By-");
	LCD_Command(0xc0);
	LCD_String("Kishan kumar Singh");
	delay(1000);

	LCD_Command(0x01);
	LCD_Command(0x0c);
	LCD_String("By-");
	LCD_Command(0xc0);
	LCD_String("  Subham Kumar");
}
int delay1()
{
//unsigned int long k;
int i,j;
unsigned int count=0;
for(i=0;i<1000;i++)
{
for(j=0;j<1000;j++)
{
if(!ir)
{
count++;
while(!ir);
}
}
}

return count;
}


void Tach()
{
	unsigned int rpm = 0;
	unsigned int count = 0;
	int i;
	for(i = 0;i<=300;i++)
	{
		if(ir==1)count++;
	}
	count = count/2;
	rpm = (count*12)/3;
  
	LCD_Command(0x01);
	LCD_Command(0x0c);
	LCD_String("RPM");
	LCD_Command(0xc0);
	LCD_integer(rpm);
}
     
void main()
{
  welcome();
	while(1)
	{
		//Tach();
		int time=delay1();
    //lcd.clear();
//lcd.print("Please Wait.....");
    int RPM=(time*12)/3;
		LCD_Command(0x01);
	LCD_Command(0x0c);
	LCD_String("RPM");
	LCD_Command(0xc0);
	lcd_data(RPM);
		

	}
}
