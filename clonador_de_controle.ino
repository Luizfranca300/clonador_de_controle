/*Desenvolvedor: Luiz Fernando França
 * clonador de controle
 */
#include <RCSwitch.h>
RCSwitch RF = RCSwitch();

int codigo[10], bit[10], protocol[10], i = 1, j, estado = 0;

void setup() {
  Serial.begin(9600);
RF.enableTransmit(0);
RF.enableReceive(14);
}
//____________________________RECEBE O CÓDIGO E GRAVA NA MEMORIA_______________________________//
void rec() {
  if ((i < 10) && (estado == 1)) {
    if (RF.available()) {
      codigo[i] = RF.getReceivedValue();
      bit[i] = RF.getReceivedBitlength();
      protocol[i] = RF.getReceivedProtocol();
      delay(100);
      Serial.print("\n____________");
      Serial.print("\nREC CONTROLE:");
      Serial.print(i+1);
      Serial.print("\nCodigo:");
      Serial.print(codigo[i]);
      Serial.print("\nBit:");
      Serial.print(bit[i]);
      Serial.print("\nProtocolo:");
      Serial.print(protocol[i]);
      i = i + 1;
      RF.resetAvailable();
      estado=0;
    }
  }
}
//_____________________________EXIBIR OS CONTROLES GRAVADOS__________________//
void exibir() {
  for (int j = 0; j < 10; j++) {
    Serial.print("\n____________");
    Serial.print("\nCONTROLE:");
    Serial.print(j+1);
    Serial.print("\nCodigo:");
    Serial.print(codigo[j]);
    Serial.print("\nBit:");
    Serial.print(bit[j]);
    Serial.print("\nProtocolo:");
    Serial.print(protocol[j]);
  }
}
void executar(int exe){
  RF.setProtocol(protocol[exe]);
  RF.send(codigo[exe],bit[exe]);
  delay(1000);
}
//__________________________EXCLUI TODOS OS CONTROLES SALVOS_______________//
void formatar() {
  Serial.print("\n Formatando mémoria");
  for (int h = 1; h < 10; h++) {
    codigo[h] =0; 
    bit[h] =0;
    protocol[h] =0;
  }
  i = 0;   
}
//___________________________Serial_________________________//
void serial(){
   int dados;
  String d = "";
  if (Serial.available()) { // verifica se existem bytes a serem lidos da porta serial virtual
    while (Serial.available() > 0)
    {
      char z = Serial.read();
      d += z;
    }
    dados = atoi(d.c_str());
     if (dados < 10) {
      executar(dados);
    }
    if (dados == 10) {
      executar(0);
    }
    if (dados == 11) {
      estado = 1;
      rec();
    }
    if (dados == 12) {
      exibir();
    }
    if (dados == 13) {
      formatar();
    }
}
}

void loop() {
  serial();
  if (estado == 1) {
    rec();
  }
}
