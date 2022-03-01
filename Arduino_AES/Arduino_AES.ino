#include <Crypto.h>
#include <AES.h>
#include <string.h>

AES128 aes128;

byte key[32] = {0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78};
String padding_character = "/";

byte buffer[256];
byte cipher_buffer[256];
byte buffer_tmp[17];



void setup()
{
    Serial.begin(115200);
}

void loop()
{

    //Prepare Key
    Serial.println("START : ");
    aes128.setKey(key, aes128.keySize());

    //Prepare Message
    String message = "xxxxxxxxxxxxxx//xxxxxxxxxxxxxx";
    while (message.length()%16 != 0)
    {message = message + padding_character;}
    message.getBytes(buffer, message.length()+1);

    //Print Clear
    Serial. print("(Hex) Plain  : ");
    for (int i = 0; i < message.length(); i++ ){
       Serial.printf("%02x", buffer[i]);
    }
    Serial.println("");
    
    //Encrypt 16 by 16
    for (int i = 0; i < message.length(); i=i+16){
      for (int j = 0 ; j < 16 ; j++){
        buffer_tmp[j] = buffer[i+j];
      }
      aes128.encryptBlock(buffer_tmp, buffer_tmp);
      for (int j = 0 ; j < 16 ; j++){
        cipher_buffer[i+j] = buffer_tmp[j];
      }
    }
    
    //Print Encrypted
    Serial. print("(Hex) Cipher : ");
    for (int i = 0; i < message.length(); i++ ){
       Serial.printf("%02x", cipher_buffer[i]);
    }
    Serial.println("");

    //Decrypt 16 by 16
    for (int i = 0; i < message.length(); i=i+16){
      for (int j = 0 ; j < 16 ; j++){
        buffer_tmp[j] = cipher_buffer[i+j];
      }
      aes128.decryptBlock(buffer_tmp, buffer_tmp);
      for (int j = 0 ; j < 16 ; j++){
        buffer[i+j] = buffer_tmp[j];
      }
    }

    //Print Decrypted
    Serial. print("(Hex) Clear  : ");
    for (int i = 0; i < message.length(); i++ ){
       Serial.printf("%02x", buffer[i]);
    }
    Serial.println("");
}
