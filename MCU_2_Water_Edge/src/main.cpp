#include <Arduino.h>
#include "Water_Level/Water_Level.h"
#include "ESPNOW_Reciever/Reciever.h"
#include "OLED/oled.h"

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0,SCL,SDA,U8X8_PIN_NONE);

struct Data : public SensorData
{
  float32 water_level_2;
} AllData;
// Struct to store all data

extern SensorData receivedData;
// Variable to store recieved data

/* Menu Variables ***********************************************************/

const unsigned char* menu_icons[3] = {
  menu_icon_waterdrop,
  menu_icon_battery,
  menu_icon_temp
};

const int n_items=3;
char items[n_items][20]= {
  {"Water level"},
  {"Battery level"},
  {"Temperature"} 
};

int previous; 
int selected = 0; 
int next; 
int current_screen = 0;

//temp measurements
int temp_progress = 0; //temp_progress bar
float temp  = 24 ;//depth_1iable to increase the temp_progress bar(in cm)
char temp_buffer[10];   // temp_buffer to hold the converted number

//water level measurements
int progress = 0; //progress bar
float depth_1  = 0;//variable to increase the progress bar(in cm)
char buffer[10];   // Buffer to hold the converted number

/*************************************************************************/

void setup()
{

    /*Intializations*/
  Sensor_init(HCSR04);
  OLED_init();

  Serial.begin(9600);

    /*Oled Config*/
  u8g2.setColorIndex(1);  //white color
  u8g2.setBitmapMode(1);
  u8g2.begin();

  ESPNOW_Receiver_Init();
}

void loop()
{
  // Get Sensor Data
  //AllData.water_level_2 = getDepth_Average_cm(HCSR04);

  /* Wait to Recieve ESP NOW Data *******************************************************************************/

  // Serial.println("Recieveing Data...");
  // while(isRecieved == false) {}
  // isRecieved = false;

  /************************************************************************************************************/

  // Store Sensor Data in structure
  AllData.water_level_1 = receivedData.water_level_1;
  AllData.temp = receivedData.temp;
  depth_1 = AllData.water_level_1;

  // Print Water Level
  Serial.printf("Water Level 1: %.2f\n", AllData.water_level_1);

  /* Button Control ************************************************************************/
  if (current_screen == 0)
  {
    //* Up Button
    if(digitalRead(OLED_BUTTON_UP_PIN )==LOW)
    {
      delay(200);
      selected=selected-1;
      if(selected < 0)
      {
        selected=n_items-1;
      }
    }
    
    //* Down Button
    if(digitalRead(OLED_BUTTON_DOWN_PIN)==LOW)
    {
      delay(200);
      selected=selected+1;
      if(selected == n_items)
      {
        selected=0;
      }
    }
    
    previous=selected-1;
    if(previous < 0)
    {
      previous=n_items-1;
    }
    next=selected+1;
    if(next >= n_items)
    {
      next=0;
    }
  }
    
  //* Enter Button
  if ((digitalRead(OLED_BUTTON_SELECT_PIN) == LOW))
  { 
    delay(200);
    if (current_screen == 0)
    {
      current_screen = 1;
    } 
    else if (current_screen == 1)
    {
      current_screen = 0;
    } 
  }
  /* End of Buttons ****************************************************************************************/


  /* OLED Section *******************************************************************************/
  u8g2.firstPage();       
    do
    { 
       if (current_screen == 0)
       {
        // Menu Item 1
         u8g2.setFont(u8g_font_7x14);
         u8g2.drawStr(26, 15, items[0]);
         u8g2.drawXBMP(4, 2, 16, 16, menu_icons[0]);
         
       // Menu Item 2
         u8g2.setFont(u8g_font_7x14);
         u8g2.drawStr(26, 37, items[1]);
         u8g2.drawXBMP(4, 24, 16, 16, menu_icons[1]);
         
       // Menu Item 3
         u8g2.setFont(u8g_font_7x14);
         u8g2.drawStr(26, 59, items[2]);
         u8g2.drawXBMP(4, 46, 16, 16, menu_icons[2]);
         
        if(selected == 1)
        {
          u8g2.drawXBMP(0,22, 128, 20, menu_sel_outline);
        }

        if(selected==2)
        {
          u8g2.drawXBMP(0,44, 128, 20, menu_sel_outline);
        } 

        if(selected==0)
        {
          u8g2.drawXBMP(0,0, 128, 20, menu_sel_outline);
        }

        u8g2.drawXBMP(120, 0, 8, 64, menu_scrollbar_bckg);
        
        // draw scrollbar handle
        u8g2.drawBox(125, 64/n_items * selected + 6, 3, 8);
       }

       else if(current_screen==1 && selected==2)
        {  
          u8g2.setFont(u8g2_font_helvB08_tr);//font
          dtostrf(temp, 6, 2, temp_buffer);  // Width = 6, Precision = 2 decimal places
       
          u8g2.setColorIndex(1); // white color
				  u8g2.drawXBMP(0, 0, 128, 64, temp_measurement);

				  u8g2.drawStr(25, 55, temp_buffer);

				  u8g2.setColorIndex(0);
					u8g2.drawBox(2, 15, 124, 8);
					u8g2.setColorIndex(1);
				  u8g2.drawBox(2, 16, temp_progress, 6);
        }
       else if(current_screen==1 and selected==0)
       {
        u8g2.setFont(u8g2_font_helvB08_tr);//font
       dtostrf(depth_1, 6, 2, buffer);  // Width = 6, Precision = 2 decimal places
        u8g2.setColorIndex(1); // white color
				 u8g2.drawXBMP(0, 0, 128, 64, waterlevel_measurement);

				 u8g2.drawStr(25, 55, buffer);

				  u8g2.setColorIndex(0);
					u8g2.drawBox(2, 15, 124, 8);
					 u8g2.setColorIndex(1);
					u8g2.drawBox(2, 16, progress, 6);
       }
      

    } while (u8g2.nextPage());
  
  /* End of OLED Control********************************************************************************************/

  /* Variables Control ***************************************************************************************/
  temp += 0.05; //? Change
  if(temp > 40)
  {
    temp = 24; //? Change
  }
  if ((temp_progress < 124) && (temp < 40)) {
   
      temp_progress= (temp * 124) / 40;
  } else {
      temp_progress = 0;
  }

  depth_1 +=0.05; //? Change
  if(depth_1 > 20)
  {
    depth_1 = 5.5; //? Change
  }
  if (progress < 124 && depth_1<20) {
   
      progress=(depth_1*124)/20;
  } else {
      progress = 0;
  }
  /* End of Variables Control ***************************************************************************************/

  // Send Data to web server

}
