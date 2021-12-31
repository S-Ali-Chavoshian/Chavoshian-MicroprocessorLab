#include<avr/io.h>
#include <util/delay.h>

#define sensor0 (PINA & (1 << 0))
#define sensor1 (PINA & (1 << 1))
#define sensor2 (PINA & (1 << 2))
#define sensor3 (PINA & (1 << 3))
#define sensor4 (PINA & (1 << 4))
#define sensor5 (PINA & (1 << 5))
#define sensor6 (PINA & (1 << 6))

#define LCD_DATA PORTC          // port C is selected as LCD data port
#define ctrl PORTB              //  port B is selected as LCD command port
#define en PB7                  // enable signal is connected to port B pin 7
#define rw PB6                  // read/write signal is connected to port B pin 6
#define rs PB5                  // register select signal is connected to port B pin 5
 
void LCD_cmd(char cmd);
void init_LCD(void);
void LCD_write(char data);
void LCD_write_string(char* data);

int main(void) {

    // make PA0 to PA6 as input for 7 sensors
    DDRA=0x80;
    // make PB as output for LCD
    DDRB=0xFF;
    // make PC as output for LCD 
    DDRC=0xFF;
    // make PD as output for motors 
    DDRD=0xFF;

    init_LCD();
    _delay_ms(1);
    LCD_cmd(0x0C);          // display on, cursor off

    while(1) {
        // Go forward -> turn on both wheels
        if ((sensor0 || sensor1) && (sensor5 || sensor6)) {
            PORTD=0b00110101;
            LCD_cmd(0x01);
            LCD_write_string("Going Forward");
        }
        // Turn left -> only turn on the left wheel
        else if (sensor0 || sensor1) {
            PORTD=0b00010001;
            LCD_cmd(0x01);
            LCD_write_string("Going Left");
        }
        // Turn right -> only turn on the right wheel
        else if (sensor5 || sensor6) {
            PORTD=0b00100100;
            LCD_cmd(0x01);
            LCD_write_string("Going Right");
        }
        // Go forward -> turn on both wheels
        else if (sensor3 && sensor2 && sensor4) {
            PORTD=0b00110101;
            LCD_cmd(0x01);
            LCD_write_string("Going Forward");
        }
        // Go forward -> turn on both wheels
        else if (sensor3 && !sensor2 && !sensor4) {
            PORTD=0b00110101;
            LCD_cmd(0x01);
            LCD_write_string("Going Forward");
        }
        // Turn left -> only turn on the left wheel
        else if (sensor2) {
            PORTD=0b00010001;
            LCD_cmd(0x01);
            LCD_write_string("Going Left");
        }
        // Turn right -> only turn on the right wheel
        else if (sensor4) {
            PORTD=0b00100100;
            LCD_cmd(0x01);            
            LCD_write_string("Going Right");
        }
        // Go backward -> turn on both wheels on reverse
        else {
            PORTD=0b00111010;
            LCD_cmd(0x01);
            LCD_write_string("Going Backward");
        }
    }
 }

void init_LCD(void) {
    LCD_cmd(0x38);           // initialization in 8bit mode of 16X2 LCD
    _delay_ms(1);
    LCD_cmd(0x01);          // make clear LCD
    _delay_ms(1);
    LCD_cmd(0x02);          // return home
    _delay_ms(1);
    LCD_cmd(0x06);          // make increment in cursor
    _delay_ms(1);
    LCD_cmd(0x80);          // “8” go to first line and “0” is for 0th position
    _delay_ms(1);
    return;
}

//**************sending command on LCD***************//

void LCD_cmd(char cmd){
    LCD_DATA = cmd;      // data lines are set to send command
    ctrl  &= ~(1<<rs);  // RS sets 0
    ctrl  &= ~(1<<rw);  // RW sets 0
    ctrl  |= (1<<en);   // make enable from high to low
    _delay_ms(1);
    ctrl  &= ~(1<<en);
    return;
}

//*****************write data on LCD*****************//
void LCD_write(char data){
    LCD_DATA= data;       // data lines are set to send command
    ctrl  |= (1<<rs);    // RS sets 1
    ctrl  &= ~(1<<rw);   // RW sets 0
    ctrl  |= (1<<en);    // make enable from high to low
    _delay_ms(1);
    ctrl &= ~(1<<en);
    return ;
}

void LCD_write_string(char* data) {
    for(int i = 0; data[i] != 0; i++){
        LCD_write(data[i]);
    }
    return;
}
