String data; //variable para comandos miscelaneos
String temp;  
double current_pos = 0;
double desired_pos = 0;
unsigned int moving = 0;
double current_speed = 100.00;

void setup()
{                     
  Serial.begin(9600); //Open connection to port
  while(!Serial) { 
    
  } 
}                     

void loop(){                    //Inicio del void loop.
  int index;
  String text;  
  
  if (moving){
    if (current_pos < desired_pos){
      current_pos += 20;
    }
    else if (current_pos > desired_pos){
      current_pos -= 20;
    }
    delay(50);
  //Serial.println(current_pos);
  }

  if (current_pos == desired_pos){ moving = 0; }  
  
  if (Serial.available()){
    data = Serial.readStringUntil('\r');
    Serial.read();    // Discard any remaining characters after \r
    delay(100);
    
    if (data.indexOf("GOTO") != -1){
      temp = data.substring(0, index-2);
      desired_pos = temp.toDouble();
      delay(1000);
      current_pos = desired_pos;
    } 
    
    else if (data.indexOf("MODEL") != -1){
      Serial.print(" SP-2-500i  ok\r\n");    
    }

    else if (data.indexOf("?NM/MIN")!=-1){
      //Serial.println(current_speed);
      Serial.print(" " + String(current_speed) + " nm/min ok\r\n");  
    }       

    else if (data.indexOf("NM/MIN") != -1){
      temp = data.substring(0, index-2);
      current_speed = temp.toDouble();
      //Serial.println(current_speed);
    }
    
    else if (data.indexOf(">NM")!=-1){
      temp = data.substring(0, index-2);
      desired_pos = temp.toDouble();     
      moving = 1; 
    }
    
    else if (data.indexOf("?NM")!=-1){
      Serial.print(" " + String(current_pos) + " nm ok\r\n");  
    }
    
    else if (data.indexOf("MONO-?DONE") != -1){
      if (current_pos == desired_pos){
        Serial.print(" 1  ok\r\n");         
      }
      else{
        Serial.print(" 0  ok\r\n");
      }      
    }    
  } //Fin del if de la interrupcion del puerto serial.  
}
