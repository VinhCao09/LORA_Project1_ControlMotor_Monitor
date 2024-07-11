#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Adafruit_GFX.h>
#include "Adafruit_ILI9341.h"
#include <SPI.h>
#include <DHT.h>
#include "thu_vien_bitmap.h"
//-----------Phan khai bao bien cho mang hinh LCD---------------------------------
//------LCD TFT--------------------
#define TFT_CS    6      // TFT CS  pin is connected to arduino pin 8
#define TFT_RST   7     // TFT RST pin is connected to arduino pin 9
#define TFT_DC    8     // TFT DC  pin is connected to arduino pin 10
#define TFT_MOSI  9
#define TFT_SCLK  10
//----------------------------------------------
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
//------------Dinh nghia mau sac----------------
#define BLACK 0x0000    
#define BLUE 0x001F    
#define RED 0xF800      
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F  
#define YELLOW 0xFFE0
#define WHITE 0xFFFF 

// class data_dht11 {       
//   public:             
//     int temperature;        
//     int humidity; 
// }

// data_dht11 du_lieu;

SoftwareSerial loraTransfer(11, 12); //TX, RX

#define BUTTON 2
#define LED 13
#define DHTPIN 3 // chân kết nối của cảm biến DHT11
#define DHTTYPE DHT11 // loại cảm biến
DHT dht(DHTPIN, DHTTYPE);
unsigned long time;
int state_motor;

void button()
  {
    if(digitalRead(BUTTON)==LOW)
    {
      delay(20);
      if(digitalRead(BUTTON)==LOW)
      {
          state_motor++;
          if (state_motor==2) state_motor=0;    
          Serial.println(state_motor);

        while(digitalRead(BUTTON)==LOW);
      }
    }
  }
class motor{
  public:

    void control()
  {
      if(state_motor==1)
      {
        digitalWrite(LED, LOW); 
      }
        if(state_motor==0)
      {
      digitalWrite(LED,HIGH); 
      }
  }

};


class lora{
  public:
    float send_data(float temperature, float humidity, int state_motor){

        if(state_motor==1){
        loraTransfer.println("OFF");  
        Serial.println("OFF");  
        }
        if(state_motor==0){
        loraTransfer.println("ON");  
        Serial.println("ON");  
        }
        loraTransfer.println(temperature);   
        loraTransfer.println(humidity);  

    }
  void receive_data(float temperature, float humidity, int state_motor){
    if(loraTransfer.available() > 1){
      String input = loraTransfer.readString();
      // Serial.println(input);    
      if(input[0] == '0')
      {
        digitalWrite(LED, HIGH); state_motor=0;
        Serial.println("ON"); 
        //loraTransfer.println("ON");
      }
          if(input[0] == '1')
      {
        // loraTransfer.println("Độ ẩm:" + String(humidity));
          digitalWrite(LED, LOW); state_motor=1;
          Serial.println("OFF");   
          //loraTransfer.println("OFF");
      }
      //KHOI TAO
          if(input[0] == '2')
      {
          send_data(temperature,humidity,state_motor);
      }
    }
  }
};
class display{
  private:
    void printText(char *text, uint16_t color, int x, int y,int textSize ){
      tft.setCursor(x, y);
      tft.setTextColor(color);
      tft.setTextSize(textSize);
      tft.print(text);
  }
  public:
    void config()
    {
      tft.begin();                   //Thiet lap LCD TFT
      tft.fillScreen(BLACK); 
      printText("NHIET DO",RED,0,10,2);     delay(200);
      tft.drawBitmap(5,30,temp,30,62,RED);
      printText("DO AM",BLUE,0,100,2);     delay(200);
      tft.drawBitmap(5,120,hum,40,40,BLUE);
      printText("DONG CO",GREEN,0,170,2);     delay(200);
      tft.drawBitmap(5,190,motor_icon,30,30,GREEN);
      tft.drawBitmap(80,230,spkt,70,90,WHITE);
    }
    float xuat_Du_Lieu_TFT(float temperature, float humidity, int state_motor)
  {
    //-------NHIET DO TFT------------//
    tft.setCursor(60, 50);
    tft.setTextColor(YELLOW,BLACK);
    tft.setTextSize(3);
    tft.print(temperature);  
    tft.setTextSize(1);  tft.print('o');   tft.setTextSize(3); tft.print('C');
    //-------NHIET DO TFT------------//
    //-------DO AM TFT------------//
    tft.setCursor(60, 140);
    tft.setTextColor(BLUE,BLACK);
    tft.setTextSize(3);
    tft.print(humidity);  
    tft.setTextSize(3); tft.print('%');
    //-------DO AM TFT------------//
    //-------MOTOR STATE------------//
        if(state_motor==1)
      {
          tft.setCursor(60,195);
          tft.setTextColor(YELLOW,BLACK);
          tft.setTextSize(3);
          tft.print("OFF");  
      }
        if(state_motor==0)
      {
        tft.setCursor(60,195);
        tft.setTextColor(YELLOW,BLACK);
        tft.setTextSize(3);
        tft.print("ON ");  
      }
    //-------MOTOR STATE------------//
  }

};
lora lora;
display display;
motor motor;
void setup() {
  Serial.begin(9600);
  loraTransfer.begin(9600);
  display.config();
  dht.begin(); // Khởi tạo cảm biến DHT11
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW); 
  time = millis();
  state_motor=1;
  pinMode(BUTTON, INPUT_PULLUP); // sử dụng điện trở kéo lên cho chân số 2, ngắt 0
  attachInterrupt(0, button, LOW); // gọi hàm tatled liên tục khi còn nhấn nút
}
void loop() {
  float temperature = dht.readTemperature(); // Đọc nhiệt độ từ DHT11
  float humidity = dht.readHumidity(); // Đọc độ ẩm từ DHT11
  Serial.println(String(temperature) + "," + String(humidity)); 
  display.xuat_Du_Lieu_TFT(temperature,humidity, state_motor);
  if ( (unsigned long) (millis() - time) > 10000){
    lora.send_data(temperature,humidity,state_motor);
    // cập nhật lại biến time
    time = millis();
    }
  lora.receive_data(temperature,humidity,state_motor);
  motor.control();
  delay(1);
}

