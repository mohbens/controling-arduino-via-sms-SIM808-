

//******you need something? feel free to contact me ...!!!
//*************mohbenselama@gmail.com*******

#include <DFRobot_sim808.h>
#define MESSAGE_LENGTH 160


char message[MESSAGE_LENGTH];
int messageIndex = 0;
char phone[16];
char datetime[24];
DFRobot_SIM808 sim808(&Serial);



void setup() {
  //mySerial.begin(9600);
  Serial.begin(9600);

  //********************************** Initialize sim808 module ************************
  while(!sim808.init()) {
      Serial.print("Sim808 init error\r\n");
      delay(1000);
  }
  delay(3000);  
  Serial.println("Init Success, please send SMS message to me!");
}



void loop() {
  //*********************************** Detecting unread SMS ************************
   messageIndex = sim808.isSMSunread();
    Serial.print("messageIndex: ");
    Serial.println(messageIndex);

   //***************************** At least, there is one UNREAD SMS ******************
   if (messageIndex > 0) {
      sim808.readSMS(messageIndex, message, MESSAGE_LENGTH, phone, datetime);

      //***********In order not to full SIM Memory, is better to delete it**********
      
      sim808.deleteSMS(messageIndex);
      Serial.print("From number: ");
      Serial.println(phone);  
      Serial.print("Datetime: ");
      Serial.println(datetime);        
      Serial.print("Recieved Message: ");
      Serial.println(message);    
      Serial.println(" AT+CMGD=1,4 ");

  //************these step is to compare the received message and do the action *********
  //*********you just have to change {Serial.println("commands ");} with what you want***
  //**********in this case A1 and A2 are the messages that the gsmshield receive 
  
       if (strcmp(message,"A1") == 0) {
         Serial.println("******************************************** ");
         Serial.println("command1 ");
         Serial.println("******************************************** ");
         }
        if (strcmp(message,"A2") == 0) {
         Serial.println("******************************************** ");
         Serial.println("command2 ");
         Serial.println("******************************************** ");    
         }

         
  //********in order to empty the sim card memory in case you sent messages while it was off******
      Serial.println(" AT+CMGD=1,4 ");
      Serial.println(" all messages has been deleted  ");
   }
}
