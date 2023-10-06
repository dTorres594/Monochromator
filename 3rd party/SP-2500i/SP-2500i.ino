String data; //variable para comandos miscelaneos
String temp;
double current_pos = 0;
double desired_pos = 0;

void setup()
{                     //Inicion del void setup.
  Serial.begin(9600); //Inicia el puerto.
  while(!Serial) { Serial.println("Conectando a puerto..."); } 
}                     //Fin del void setup.

void loop(){                    //Inicio del void loop.
  int index;
  String text;

  if (current_pos < desired_pos){
    current_pos += 20;
  }
  else if (current_pos > desired_pos){
    current_pos -= 20;
  }
  //Serial.println(current_pos);
  
  
  if (Serial.available()){
    data = Serial.readStringUntil('\r');
    Serial.read();    // Discard any remaining characters after \r
    delay(100);

    //index = data.indexOf("GOTO");
    if (data.indexOf("GOTO") != -1){
      temp = data.substring(0, index-2);
      desired_pos = temp.toDouble();
      delay(1000);
      current_pos = desired_pos;
      //Serial.print(" 1  ok\r\n");
    } 
    
    else if (data.indexOf("MODEL") != -1){
      Serial.print(" SP-2-500i  ok\r\n");    
    }
    
    else if (data.indexOf(">NM")!=-1){
      temp = data.substring(0, index-2);
      desired_pos = temp.toDouble();      
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
