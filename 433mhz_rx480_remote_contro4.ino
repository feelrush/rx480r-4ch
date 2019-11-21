//#include <Arduino.h>
// 433mhz rx480 remote control blank with short and long push for 4 buttons
#define BAUDRATE 9600

//#define REMOTE_BUTTON_PIN1      16
//#define REMOTE_BUTTON_PIN2      14
//#define REMOTE_BUTTON_PIN3      6
//#define REMOTE_BUTTON_PIN4      5

//#define REMOTE_BUTTON_PIN1      18
//#define REMOTE_BUTTON_PIN2      19
//#define REMOTE_BUTTON_PIN3      20
//#define REMOTE_BUTTON_PIN4      21


#define REMOTE_BUTTON_PIN1      A0
#define REMOTE_BUTTON_PIN2      A1
#define REMOTE_BUTTON_PIN3      A2
#define REMOTE_BUTTON_PIN4      A3

#define REMOTE_BUTTON_PIN_K      4

#define MAX_SHORT_PUSH_UP_TIME_DS      4 // 4 deciseconds
  
  byte push_counter = 0;
  byte push_up_ind = 0;
  boolean push_up_check = 0; 
  //boolean button_status_1,button_status_2,button_status_3,button_status_4;
  //byte button_status_1,button_status_2,button_status_3,button_status_4;
  unsigned long remote_push_timer = 0;
  byte push_key_id = 0;
  
void setup() {
    Serial.begin(BAUDRATE);
    pinMode(REMOTE_BUTTON_PIN1, INPUT); 
    pinMode(REMOTE_BUTTON_PIN2, INPUT);
    pinMode(REMOTE_BUTTON_PIN3, INPUT);
    pinMode(REMOTE_BUTTON_PIN4, INPUT);
    pinMode(REMOTE_BUTTON_PIN_K, INPUT); 
}

void loop() {

    if (millis() - remote_push_timer > 100){ //ds counter        
         push_key_id = digitalRead(REMOTE_BUTTON_PIN_K);
         if (push_key_id > 0 && push_up_check == 0) {
               //button_status_1 = digitalRead(REMOTE_BUTTON_PIN1);
               if ( digitalRead(REMOTE_BUTTON_PIN1) > 0) { push_up_ind = 1;}
               else { 
                  //button_status_2 = digitalRead(REMOTE_BUTTON_PIN2);
                  if ( digitalRead(REMOTE_BUTTON_PIN2) > 0) { push_up_ind = 2;}
                  else { 
                      //button_status_3 = digitalRead(REMOTE_BUTTON_PIN3);
                      if ( digitalRead(REMOTE_BUTTON_PIN3) > 0) { push_up_ind = 3;}
                      else { 
                          //button_status_4 = digitalRead(REMOTE_BUTTON_PIN4);
                          if ( digitalRead(REMOTE_BUTTON_PIN4) > 0) { push_up_ind = 4;}
                      }
                  }
               }
            push_up_check = 1;
            push_counter++;
       }
       else if (push_key_id > 0 && push_up_check > 0) {
        push_counter++;
       }
       else if (push_key_id == 0 && push_up_ind > 0 && push_counter > 0) {
            //push_counter++;
             if (push_counter > MAX_SHORT_PUSH_UP_TIME_DS && push_key_id == 0 && push_up_check == 1) {
                switch (push_up_ind) {
                  case 1: Serial.println("a2"); break;
                  case 2: Serial.println("b2"); break;
                  case 3: Serial.println("c2"); break;
                  case 4: Serial.println("d2"); break;
                }
             }
             else if (push_counter > 0 && push_key_id == 0 && push_up_check == 1) {
                switch (push_up_ind) {
                  //case 1: Serial.println("a1"); break;
                  case 1: Serial.println("a1"); break;
                  case 2: Serial.println("b1"); break;
                  case 3: Serial.println("c1"); break;
                  case 4: Serial.println("d1"); break;
                }
         }
         //Serial.println(push_counter );
         push_up_ind = 0; push_counter = 0; push_up_check = 0;
      }   
         //char s[80]; snprintf(s, 80, "%d %d %d %d %d", key_id, button_status_1, button_status_2, button_status_3, button_status_4); Serial.println(s);
        remote_push_timer = millis();  
    }
}
