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
int maxReading = 512;

boolean packetRev = false;
byte rawBuf[] = new byte [packetLength];
int mapData[][] = new int [rowElements][colElements];

void setup() {
  
  size(1000, 1000);
  background(0);
  
  printArray(Serial.list());
  serial = new Serial(this, Serial.list()[0], 115200);
  serial.bufferUntil(255);
  delay(3000);
  serial.write(65);
  
}

void draw() {
    
  if (packetRev) {
    packetRev = false; //<>//
    int index = 0;
    for (int i = 0; i < rowElements; i++) {
     for (int j = 0; j < colElements; j++) {
       int LSB = rawBuf[index] < 0 ? 256 + (int)rawBuf[index] : rawBuf[index];
       int MSB = rawBuf[index + 1] < 0 ? 256 + (int)rawBuf[index + 1] : rawBuf[index + 1];
       mapData[i][j] = LSB + MSB * 200;
       fill(map(mapData[i][j], 0, maxReading, 0, 255));
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
    //delay(100);
  }
  delay(50); 
  serial.write(65);

  
}

void serialEvent(Serial serial) {
  
  int dataLen = serial.readBytesUntil(255, rawBuf);
  if (print) { //<>//
    for (int i = 0; i < dataLen; i++) {
      if (i % 20 == 0) {
       println(); 
      }
      print(rawBuf[i]);
      print('\t');
    }
  }
  serial.clear();
  packetRev = dataLen == packetLength;
  
}
