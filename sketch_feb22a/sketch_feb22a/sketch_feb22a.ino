
#include <SPI.h>
#include <MFRC522.h>     // 引用程式庫

#define RST_PIN      A0        // 讀卡機的重置腳位
#define SS_PIN       10        // 晶片選擇腳位

struct RFIDTag {    // 定義結構
   byte uid[4];
   char *name;
};

struct RFIDTag tags[] = {  // 初始化結構資料
   {{60,209,110,133}, "Arduino"},
   {{0xD4,0xD3,0xC0,0x61}, "Raspberry Pi"},
   {{0x15,0x8,0xA,0x53}, "Espruino"}
};

byte totalTags = sizeof(tags) / sizeof(RFIDTag);

MFRC522 mfrc522(SS_PIN, RST_PIN);  // 建立MFRC522物件

void setup() {
  Serial.begin(9600);
  Serial.println();
  Serial.println("RFID reader is ready!");

  SPI.begin();
  mfrc522.PCD_Init();   // 初始化MFRC522讀卡機模組
}

void loop() {
    // 確認是否有新卡片
    if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
      byte *id = mfrc522.uid.uidByte;   // 取得卡片的UID
      byte idSize = mfrc522.uid.size;   // 取得UID的長度
      bool foundTag = false;            // 是否找到紀錄中的標籤，預設為「否」。
      
      for (byte i=0; i<totalTags; i++) {
        if (memcmp(tags[i].uid, id, idSize) == 0) {
          Serial.println(tags[i].name);  // 顯示標籤的名稱
          foundTag = true;  // 設定成「找到標籤了！」
          break;            // 退出for迴圈
        }
      }

      if (!foundTag) {    // 若掃描到紀錄之外的標籤，則顯示"Wrong card!"。
        Serial.println("Wrong card!");
      }

      mfrc522.PICC_HaltA();  // 讓卡片進入停止模式      
    } 
}
