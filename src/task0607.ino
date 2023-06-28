#include <Servo.h> //ライブラリ<Servo.h>を組み込む
#define RPIN 5
#define YPIN 3
#define RLPIN A1
#define YLPIN A2

int value;

Servo sv; //Servoオブジェクト“sv”を作成する

void setup() {
 Serial.begin(9600); //シリアル通信のデータ転送レートを9600ビット/秒に設定する

 // servo
 sv.attach(6, 500, 2400);//svの出力をリセットした上で、D6番ピンに割り当て、パルス幅を500～2400マイクロ秒とする
 
 // led
 pinMode(RPIN, OUTPUT);
 digitalWrite(RPIN, LOW);
 pinMode(YPIN, OUTPUT);
 digitalWrite(YPIN, LOW);
}

void loop() {
  // servo
  int angle = analogRead(0) ; //変数angleをA0番ピンの入力値とする
  sv.writeMicroseconds(map(angle, 0, 1023, 500, 2400)) ;  //angleを500～2400の整数値に変換してD6番端子に出力する
  delay(20) ;
 
  //  led
  while (Serial.available()) {
    String str = Serial.readString();//cmd = str
    char ini = str[0];

    if(ini == 'r'||ini == 'y'){
      int value = str.substring(2).toInt();
      Serial.println(value);
      if(ini == 'r'){
        analogWrite(RPIN,value);
        delay(20);
      }else{
        analogWrite(YPIN,value);
        delay(20);
      }
    }else if(ini == 'w'){
      int Comma = str.indexOf(",", 2);
      int value_r = str.substring(2, Comma).toInt();
      int value_y = str.substring(Comma+1).toInt();
      Serial.println(value_r);
      Serial.println(value_y);
      analogWrite(RPIN, value_r);
      analogWrite(YPIN, value_y);
    }else if(ini == 's'){
      int value_r = map(analogRead(RLPIN),0,1023,0,255);
      int value_y = map(analogRead(YLPIN),0,1023,0,255);
      Serial.println("==== status ====");
      Serial.println("RED LED : ");
      Serial.println(value_r);
      Serial.println("YELLOW LED : ");
      Serial.println(value_y);
    }
  }
}
