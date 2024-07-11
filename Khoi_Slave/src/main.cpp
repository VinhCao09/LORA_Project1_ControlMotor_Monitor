#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define screen_width 128
#define screen_height 64
Adafruit_SSD1306 display(screen_width, screen_height);
SoftwareSerial loraReceive(6, 7); //TX, RX


#define BUTTON 12            
int State=0;
String read_data="";
// void ON_OFF();
class oled{
  public:
  void hienthi()
  {
        display.clearDisplay();
        display.setTextSize(1);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(0,0);
        display.print("LORA SYSTEM");
        display.setTextSize(2);
        display.setCursor(0,10);
        display.print(read_data);
        display.setCursor(0,25);
      // display.print(read_data);
        display.setCursor(60,25);
        display.setTextSize(1);
        display.print("o");
        display.setTextSize(2);
        display.print("C");
        display.setTextSize(2);
        display.setCursor(65,45);
        display.print("%");
        display.display();   
  }
};
class nutnhan{
  public:
  void gui_data_notice(){
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(5,30);
  }
  void kiem_Tra()
{
  if(digitalRead(BUTTON)==LOW)
  {
    delay(20);
    if(digitalRead(BUTTON)==LOW)
    {
        State++;
        if (State==2) State=0;    
        loraReceive.println(State);    
        Serial.println(State);
        gui_data_notice();
        display.print("Dang gui du lieu...");   
        display.display();  
        delay(500);

      while(digitalRead(BUTTON)==LOW);
    }
  }
}
};
nutnhan nutnhan;
oled oled;

void setup() {
  Serial.begin(9600);
  loraReceive.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Address 0x3C for 128x32
  pinMode(BUTTON, INPUT_PULLUP);  
  //GUI SO 2 DE NHAN GIA TRI CAM BIEN KHI VUA KHOI DONG
  loraReceive.println("2");    
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.print("LORA SYSTEM");

}

void loop() {
//   //GUI:
//   if(Serial.available() > 0){
//     String input = Serial.readString();
//     loraReceive.println(input);    
//   }
//  //NHAN:
//   if(lorasReceive.available() > 1){
//     String input = loraReceive.readString();
//     Serial.println(input);    
//   }
  nutnhan.kiem_Tra();
  if(loraReceive.available() > 1){
    // HIEN_THI_NHAN_GUI_DU_LIEU();
    // display.print("Dang nhan du lieu...");   
    // display.display();
     read_data = loraReceive.readString();
 }
    Serial.println(read_data); 
   oled.hienthi();
   

  //delay(20);
}


