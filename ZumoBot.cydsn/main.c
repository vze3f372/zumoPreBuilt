/**
* @mainpage ZumoBot Project
* @brief    You can make your own ZumoBot with various sensors.
* @details  <br><br>
    <p>
    <B>General</B><br>
    You will use Pololu Zumo Shields for your robot project with CY8CKIT-059(PSoC 5LP) from Cypress semiconductor.This 
    library has basic methods of various sensors and communications so that you can make what you want with them. <br> 
    <br><br>
    </p>
    
    <p>
    <B>Sensors</B><br>
    &nbsp;Included: <br>
        &nbsp;&nbsp;&nbsp;&nbsp;LSM303D: Accelerometer & Magnetometer<br>
        &nbsp;&nbsp;&nbsp;&nbsp;L3GD20H: Gyroscope<br>
        &nbsp;&nbsp;&nbsp;&nbsp;Reflectance sensor<br>
        &nbsp;&nbsp;&nbsp;&nbsp;Motors
    &nbsp;Wii nunchuck<br>
    &nbsp;TSOP-2236: IR Receiver<br>
    &nbsp;HC-SR04: Ultrasonic sensor<br>
    &nbsp;APDS-9301: Ambient light sensor<br>
    &nbsp;IR LED <br><br><br>
    </p>
    
    <p>
    <B>Communication</B><br>
    I2C, UART, Serial<br>
    </p>
*/

#include <project.h>
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "Motor.h"
#include "Ultra.h"
#include "Nunchuk.h"
#include "Reflectance.h"
#include "Gyro.h"
#include "Accel_magnet.h"
#include "LSM303D.h"
#include "IR.h"
#include "Beep.h"
#include "mqtt_sender.h"
#include <time.h>
#include <sys/time.h>
#include "serial1.h"
#include <unistd.h>
#include<stdlib.h>

#define ON 1
#define OFF 0

#define PRESSED 0
#define RELEASED 1

#define WAITING 1

#define BLACK 1 
#define WHITE 0
#define STOP 2

void drive_to_first_line(struct sensors_ *dig);
void progStart(uint32_t delay);
void progEnd(void);

/**
 * @file    main.c
 * @brief   
 * @details  ** Enable global interrupt since Zumo library uses interrupts. **<br>&nbsp;&nbsp;&nbsp;CyGlobalIntEnable;<br>
*/
//week 4 Assignment 1
#if 1
    

    
void zmain(void) {
    const char *prompt = "Joe/Elapsed";
    unsigned int count = 0;
    struct sensors_ dig;
    TickType_t start_T = 0;
    TickType_t stop_T = 0;
    
    IR_Start();
    reflectance_start();
    reflectance_set_threshold(15000, 15000, 11000, 11000, 15000, 15000);
    motor_start(); // start motors
    motor_forward(0,0);
    progStart(1000);
    drive_to_first_line(&dig);
    start_T = xTaskGetTickCount();
    motor_forward(255,0);
    while(count < STOP){
    
        reflectance_digital(&dig); 
        if(dig.L3 == BLACK && dig.R3 == BLACK){
            
            count++;
            stop_T = xTaskGetTickCount();           
            while((dig.L3 == BLACK && dig.R3 == BLACK ) && count < STOP){
                reflectance_digital(&dig);
            }
            
        }
    }
    print_mqtt(prompt, "%dms", stop_T-start_T);
    motor_forward(0,0);
    progEnd();
    
}
#endif
// Week 3 Assignment 1
#if 0

void zmain(void) {
    
    motor_start(); // start motors
    motor_forward(0,0);
    //code to start the robot
    progStart(1000);
    
    motor_forward(100,3200); // motors run for 
    motor_forward(0,0);
    
    progEnd();
    
}
#endif
//Week3 Assignment 2
#if 0 

void zmain(void){
    
    Ultra_Start();
    srand(5678);
    progStart(1000);
    
    while(true) {
        
        int d = Ultra_GetDistance();
        int rNum = rand() %11 + 10; // num between 10 - 20
        printf("distance: %5d Random: %d", d, rNum);
        if(d < 10){
            printf("TOO CLOSE!!!\n");
        }
        else{
            printf("KEEP GOING\n");
        }
        vTaskDelay(100);
    }
    
    progEnd();

}


#endif
// Hello World!
#if 0

void zmain(void)
{
    printf("\nHello, Folks!\n");

    while(true)
    {
        vTaskDelay(100); // sleep (in an infinite loop)
    }
 }   
#endif
//Tick Timer Example
#if 0 


void zmain(void) 
{
	TickType_t Ttime = xTaskGetTickCount();
	TickType_t PreviousTtime = 0;

	while(true) 
	{
		while(SW1_Read()) vTaskDelay(1); // loop until user presses button
		Ttime = xTaskGetTickCount(); // take button press time
		/*Print out the time between button presses in seconds. int cast used to suppress warning messages*/
		printf("The amount of time between button presses is: %d.%d seconds\n", (int)(Ttime-PreviousTtime)/1000%60, (int)(Ttime-PreviousTtime)%1000);
		while(!SW1_Read())vTaskDelay(1); // loop while user is pressing the button
		PreviousTtime = Ttime; // remember previous press time
	}
	
}

#endif
// button
#if 0

void zmain(void)
{
    while(true) {
        printf("Press button within 5 seconds!\n");
	    TickType_t Ttime = xTaskGetTickCount(); // take start time
        bool timeout = false;
        while(SW1_Read() == 1) {
            if(xTaskGetTickCount() - Ttime > 5000U) { // too long time since start
                timeout = true;
                break;
            }
            vTaskDelay(10);
        }
        if(timeout) {
            printf("You didn't press the button\n");
        }
        else {
            printf("Good work\n");
            while(SW1_Read() == 0) vTaskDelay(10); // wait until button is released
        }
    }
}
#endif
// button
#if 0

void zmain(void)
{
    printf("\nBoot\n");

    //BatteryLed_Write(1); // Switch led on 
    BatteryLed_Write(0); // Switch led off 
    
    //uint8 button;
    //button = SW1_Read(); // read SW1 on pSoC board
    // SW1_Read() returns zero when button is pressed
    // SW1_Read() returns one when button is not pressed
    
    bool led = false;
    
    while(true)
    {
        // toggle led state when button is pressed
        if(SW1_Read() == 0) {
            led = !led;
            BatteryLed_Write(led);
            if(led) printf("Led is ON\n");
            else printf("Led is OFF\n");
            Beep(1000, 150);
            while(SW1_Read() == 0) vTaskDelay(10); // wait while button is being pressed
        }        
    }
 }   
#endif
//ultrasonic sensor//
#if 0
void zmain(void)
{
    Ultra_Start();                          // Ultra Sonic Start function
    
    while(true) {
        int d = Ultra_GetDistance();
        // Print the detected distance (centimeters)
        printf("distance = %d\r\n", d);
        vTaskDelay(200);
    }
}   
#endif
//IR receiverm - how to wait for IR remote commands
#if 0

void zmain(void)
{
    IR_Start();
    
    printf("\n\nIR test\n");
    
    IR_flush(); // clear IR receive buffer
    printf("Buffer cleared\n");
    
    bool led = false;
    // Toggle led when IR signal is received
    while(true)
    {
        IR_wait();  // wait for IR command
        led = !led;
        BatteryLed_Write(led);
        if(led) printf("Led is ON\n");
        else printf("Led is OFF\n");
    }    
 }   
#endif
//reflectance
#if 0
//reflectance
void zmain(void)
{
   
    struct sensors_ dig;

    reflectance_start();
    reflectance_set_threshold(15000, 15000, 11000, 11000, 15000, 15000); // set center sensor threshold to 11000 and others to 9000
    

    while(true)
    {
        // read digital values that are based on threshold. 0 = white, 1 = black
        // when blackness value is over threshold the sensors reads 1, otherwise 0
        reflectance_digital(&dig); 
        //print out 0 or 1 according to results of reflectance period
        printf("%5d %5d %5d %5d %5d %5d \r\n", dig.L3, dig.L2, dig.L1, dig.R1, dig.R2, dig.R3);        
        
        vTaskDelay(200);
    }
}   
#endif
//motor
#if 0

void zmain(void)
{
    motor_start();              // enable motor controller
    motor_forward(0,0);         // set speed to zero to stop motors

    vTaskDelay(3000);
    
    motor_forward(100,2000);     // moving forward
    motor_turn(200,50,2000);     // turn
    motor_turn(50,200,2000);     // turn
    motor_backward(100,2000);    // moving backward
     
    motor_forward(0,0);         // stop motors

    motor_stop();               // disable motor controller
    
    while(true)
    {
        vTaskDelay(100);
    }
}
#endif
// MQTT test
#if 0

// MQTT test
void zmain(void)
{
    //int ctr = 0;
    //int prev = 0;
    int elapsed = 0;
    int button = 0;
    const char *topic = "Joe/Assignment1";

    //printf("\nBoot\n");
    print_mqtt(topic, "Boot");

    while(true)
    {
        
        
        //printf("Ctr: %d, Button: %d\n", ctr, SW1_Read());
        button = SW1_Read();
        if(button == PRESSED){
           // ctr++;
            elapsed = xTaskGetTickCount();
            print_mqtt(topic, "Time: %dms, Button: %d", elapsed, SW1_Read());
            while(button != RELEASED){
                button = SW1_Read();
            }
            vTaskDelay(10);
        }
       // prev = ctr;
        
        
        
    }
 }  

#endif

// Custom functions below

void progStart(uint32_t delay){
    
    while(SW1_Read() == 1);
    BatteryLed_Write(ON);
    vTaskDelay(delay);
    BatteryLed_Write(OFF);

}
 
void progEnd(void){
    bool led = 0;
    while(true){
        vTaskDelay(100);
        BatteryLed_Write(led ^= 1);
    }

}
#if 1 
void drive_to_first_line(struct sensors_ *dig){
    motor_forward(50,0);
    while(dig->L3 != BLACK && dig->R3 != BLACK){
            reflectance_digital(dig);
    }                  
    while(dig->L3 == BLACK && dig->R3 == BLACK){
            reflectance_digital(dig);
    }
    motor_forward(0,0);
    IR_wait();
    
}
#endif
/* [] END OF FILE */
