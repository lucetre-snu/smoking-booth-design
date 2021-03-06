#include <SoftwareSerial.h>        //RX, TX 통신 라이브러리 추가

SoftwareSerial SerialWD(2,3);         //RX ,TX 핀을 2, 3번 핀으로 지정

long pmcf10=0;

long pmcf25=0;

long pmcf100=0;

long pmat10=0;

long pmat25=0;

long pmat100=0;



char buf[50];



void setup() {

  Serial.begin(115200);          //시리얼 통신 시작

  SerialWD.begin(9600);        //RX, TX 통신 시작

}



void loop() {

  int count = 0;

  unsigned char c;

  unsigned char high;

  

  while (SerialWD.available()) {               

    c = SerialWD.read();           //RX, TX 통신을 통한 값을 c로 저장

    if((count==0 && c!=0x42) || (count==1 && c!=0x4d)){

      break;

    }

    if(count > 15){

      break;

    }

    else if(count == 4 || count == 6 || count == 8 || count == 10 || count == 12 || count == 14) {

      high = c;

    }

    else if(count == 5){             //pm1.0의 수치값 계산

      pmcf10 = 256*high + c;

//      Serial.print("CF=1, PM1.0\t\t= ");
//      Serial.println(pmcf10);
      Serial.print(pmcf10);
      Serial.print(" ");
    }

    else if(count == 7){           //pm2.5의 수치값 계산

      pmcf25 = 256*high + c;

//      Serial.print("CF=1, PM2.5\t\t= ");
//      Serial.println(pmcf25);
      Serial.print(pmcf25);
      Serial.print(" ");

    }

    else if(count == 9){           //pm 10의 수치값 계산

      pmcf100 = 256*high + c;

//      Serial.print("CF=1, PM10\t\t= ");
//      Serial.println(pmcf100);
      Serial.print(pmcf100);
      Serial.print(" ");

    }

    else if(count == 11){

      pmat10 = 256*high + c;

//      Serial.print("atmosphere, PM1.0\t= ");
//      Serial.println(pmat10);
      
      Serial.print(pmat10);
      Serial.print(" ");

    }

    else if(count == 13){

      pmat25 = 256*high + c;

//      Serial.print("atmosphere, PM2.5\t= ");
//      Serial.println(pmat25);
      Serial.print(pmat25);
      Serial.print(" ");


    }

    else if(count == 15){

      pmat100 = 256*high + c;

//      Serial.print("atmosphere, PM10\t= ");
//      Serial.println(pmat100);
      Serial.print(pmat100);
      Serial.println(" ");

    }

    count++;

  }

  while(SerialWD.available()) SerialWD.read();

  delay(500);

}
