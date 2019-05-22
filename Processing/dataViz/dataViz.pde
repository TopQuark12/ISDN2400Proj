//Author: Alex Wong Tat Hang

import processing.serial.*;

Serial serial;

int packetLength = 842; 
int rowElements = 20;
int colElements = 20;
int elementNum = rowElements * colElements;
int windowSize = 1000;
int cellWidth = windowSize / colElements;
int cellHeight = windowSize / rowElements;
boolean print = false;
int maxReading = 3900;

boolean packetRev = false;
boolean pressed = false;
byte rawBuf[] = new byte [2048];
int mapData[][] = new int [rowElements][colElements];
float mapRes[][] = new float [rowElements][colElements];

void setup() {
  
  size(1000, 1000);
  background(0);
  
  printArray(Serial.list());
  serial = new Serial(this, Serial.list()[0], 115200);
  serial.bufferUntil(255);
  
  colorMode(HSB, 255, 255, 255);
  
}

void draw() {
    
  if (packetRev) {
    packetRev = false;
    int index = 0;
    for (int i = 0; i < rowElements; i++) {
     for (int j = 0; j < colElements; j++) {
       int LSB = rawBuf[index] < 0 ? 256 + (int)rawBuf[index] : rawBuf[index];
       int MSB = rawBuf[index + 1] < 0 ? 256 + (int)rawBuf[index + 1] : rawBuf[index + 1];
       mapData[i][j] = LSB + MSB * 200;
       mapRes[i][j] = 660 / map(mapData[i][j], 0, 4096, 0, 3.3) - 200;
       fill(map(mapData[i][j], 0, maxReading, 255 / 2, 0), 220, 255);
       //fill(map(mapRes[i][j], 2000, 0, 255 / 2, 0), 255, 255);
       rect(j * cellWidth, i * cellHeight, cellWidth, cellHeight);
       if (print) {
         print(mapData[i][j]);
         print('\t');
       }
       index += 2;
     }
     if (print) println();
     index += 2;
    }      
    if (print) println();    
    
    if (pressed) {
      pressed = false;
       println("Saving sensor data");
       String[] outArray = new String[rowElements];
       for (int i = 0; i < rowElements; i++) {
         outArray[i] = "";
         for (int j = 0; j < colElements; j++) {
            outArray[i] = outArray[i] + nf(mapData[i][j]) + '\t';
         }
       }
       saveStrings("./../../input/pressureMap.pres", outArray);
       delay(2000);
    }
  }
    
}

void serialEvent(Serial serial) {
  
  int dataLen = serial.readBytesUntil(255, rawBuf);
  serial.clear();
  packetRev = dataLen == packetLength;
  
}

void keyPressed() {
  pressed = true;
}
