#ifndef pRadioMsg_h
#define pRadioMsg_h

#include <pGlobals.h>
#include <RF24.h>

/**
 * Códigos de erro
 */
#define rdErr_NotUsed        0
#define rdErr_NothingToRead -1
#define rdErr_WrongSerialN  -2
#define rdErr_WriteFail     -3
#define rdErr_ZeroLen       -4
#define rdErr_AckTimeOut    -5
#define rdErr_InvalidAck    -6
#define rdErr_SendAckFail   -7
#define rdErr_ReadAckFail   -8
#define rdErr_RdErrors       9


typedef rf24_datarate_e TDatarate;

///////////////////////////////////////////////////////////////////////////////
///
/// Classe RadioMessage: Estabelece um formato básico para as mensagens (TRadioMsg). 
/// Uma mensagem é composta por um header (THeader) e opcionalmente um payload 
/// (bloco de bytes). Se a aplicação usar apenas mensagens de um byte o payload não é 
/// necessário, nesse caso apenas o header é enviado/transmitido. O campo msgID do 
/// header não é usado pela classe, serve para transmitir mensagens sem payload.
///

/**
 * Cabeçalho (header) para as mensagens. Uma mensagem é composta por um 
 * header e um payload. O header é obrigatório, mas o payload é opcional.
 */
typedef struct {
   union{
      struct
      {
        byte msgID;
        byte paySize;
        uint serialN;
      };
      long l;
   };
   byte fromNode;
   byte toNode;
} 
THeader;

/**
 * Tamanho máximo do payload das mensagens (28 bytes). 
 */
#define PAYLOAD_MAX_LEN (32-sizeof(THeader))

/**
 * Estrutura para envio e recebimento de mensagens.
 */
typedef struct {
   THeader head;
   byte    buff[PAYLOAD_MAX_LEN];
}
TRadioMsg;

class RadioMessage: protected RF24
{
public:
  /**
   * Construtor
   */
  RadioMessage(int cePin, int csPin):RF24(cePin, csPin){}

  /**
   * Inicia o radio. Chame antes de qualquer outro método.
   *
   * @param pipeIn Pipe para o recebimento de mensagens
   * @param pipeOut Pipe para o envio de mensagens
   * @param rate Taxa de transmissão. As opções são: 
   * RF24_1MBPS, RF24_2MBPS e RF24_250KBPS. O default é RF24_1MBPS. 
   *
   * @note: A taxa de transmissão deve ser a mesma nas duas pontas. 
   * O valor usado para o pipeIn em uma ponta deve ser o mesmo valor 
   * do pipeOut na outra e vice-versa.
   */
  void begin(byte *pipeIn, byte *pipeOut, TDatarate rate);

  // Em teste
  void begin(byte *pipeIn, TDatarate rate, byte myNodeID);
  void addNode(byte *nodePipe, byte nodeID);

  /**
   * makeMessage(): Preenche a estrutura TRadioMsg e a deixa pronta para ser transmitida.
   * msg: Estrutura que será preenchida para envio.
   * msgID: Este campo é armazenado no header da mensagem e não é usado pela classe. 
   *        Use para enviar mensagens sem payload.
   * payloadSize: Quantidade de bytes no payload, o tamanho máximo é informado por 
   *              PAYLOAD_MAX_LEN (28 bytes nesta implementação), mas pode ser zero.
   * payload: Bloco de bytes que será enviado junto com a mensagem.
   *
   * Retorna a estrutura msg já preenchida.
   *
   */
  TRadioMsg* makeMessage(TRadioMsg* msg, byte msgID, byte payloadSize=0, void* payload= NULL);

 /**
   * sendMessage(): Envia uma mensagem para a outra ponta. 
   * msg: Estrutura contendo a mensagem que será enviada.
   *
   * Retorna a quantidade de bytes enviados no 
   * payload (não considera o tamanho do header).
   */
  int sendMessage(TRadioMsg* msg);

 /**
   * readMessage(): Recebe uma mensagem da outra ponta. 
   * msg: Estrutura contendo a mensagem recebida.
   *
   * Retorna a quantidade de bytes recebidos no 
   * payload (não considera o tamanho do header).
   * Se não há mensagems disponíveis para leitura 
   * retorna rdErr_NothingToRead.
   */
  int readMessage(TRadioMsg* msg);

  boolean messageWaiting(){ return available(); }

  /**
   * getMsgID(): Retorna o campo msgID armazenado no header da mensagem.
   */
  byte getMsgID(TRadioMsg* msg);

  /**
   * getPaySize(): Retorna tamanho em bytes do payload.
   */
  byte getMsgPaySize(TRadioMsg* msg);

  /**
   * getPayload(): Retorna um ponteiro para o payload contido na mensagem.
   */
  void* getMsgPayload(TRadioMsg* msg);

  /**
   * copyPayload(): Copia o payload na mensagem para o bloco de bytes informado
   *                em destination. Retorna a quantidade de byte copiados.
   */
  byte copyMsgPayload(TRadioMsg* msg, void* destination);

  /**
   * run(): verifica se há mensagens recebidas e se houver, lê a mensagem e 
   *        dispara o evento onIncommingMsg(). Se este recurso for usado, 
   * este método deve ser chamado frequentemente, de preferência a cada loop.
   */
  void run();

protected:
  // Override to capture, call run() to trigger.
  virtual void onIncommingMsg(TRadioMsg* msg){};

private:
  byte pipes[6][6];
  byte nodes[6];
  byte nodesCount=0;

  uint nextSerial=0;
  THeader* makeHeader(THeader* head, byte msgID, byte payloadSize);
  int readBuff(void* buff, byte maxSize);
  int writeBuff(void* buff, byte sizeBuff);
  void rxMode(){ startListening(); }
  void txMode(){ stopListening();  }
};



#endif

