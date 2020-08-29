#include <SPI.h>
#include <avr/pgmspace.h>
#pragma once
#define COMMAND_1 0b00000000
#define COMMAND_2 0b01000000
#define COMMAND_3 0b11000000
#define COMMAND_4 0b10000000
//parameters COMMAND_1
#define DIG8_SEG20 0b0000
#define DIG9_SEG19 0b1000
#define DIG10_SEG18 0b1001
#define DIG11_SEG17 0b1010
#define DIG12_SEG16 0b1011
#define DIG13_SEG15 0b1100
#define DIG14_SEG14 0b1101
#define DIG15_SEG13 0b1110
#define DIG16_SEG12 0b1111
//parameters COMMAND_2
#define NORMAL_OPERATION_MODE 0b0000
#define TEST_MODE 0b1000
#define INCREMENT_ADDRESS 0b000
#define FIXED_ADDRESS 0b100
#define WRITE_DATA_TO_DISPLAY_MODE 0b00
#define WRITE_DATA_TO_LED_PORT 0b01
#define READ_KEY_DATA 0b10
#define READ_SW_DATA 0b11
//parameters COMMAND_4
#define DISPLAY_ON 0b1000
#define DISPLAY_OFF 0b0000
#define PULSE_WIDTH1 0b000
#define PULSE_WIDTH2 0b001
#define PULSE_WIDTH4 0b010
#define PULSE_WIDTH10 0b011
#define PULSE_WIDTH11 0b100
#define PULSE_WIDTH12 0b101
#define PULSE_WIDTH13 0b110
#define PULSE_WIDTH14 0b111

class pt6311{
  private:
    const int spi_timeout = 25;
    int CS;
    int numOfDigit;
    int displayState;
    int displayBrighthess;
    int buf[16];
	uint8_t ledState_;
    
  public:
  void SendByte(byte data);
    short int symbolList[512];
    pt6311(int CS_pin, int num_Of_Digit);
    void setBrightness(int br); // from 0 to 7
    void displayOn();
    void displayOff();
    int getBrightness(); //return brightness
    bool getState(); // return on or off
    void setDigit(int pos, char _data); // pos from 0 to numOfDigit
	void setLeds(int data);
	void ledWrite(uint8_t number, uint8_t state);
	
	void writeDigit(int pos, char _data);
	void cmd2(void);
	void writeChar(int pos, char _data);
	void writeLine(int pos, char _data);
};
//								MSB										LSB
//								  1  2 3 4 5 6 7 8 9  10 11 12 13 14 15 16
// bit position -> character map: 0 DP N M L K J H G2 G1 F  E  D  C  B  A
/*
	C1-1 = L
	C1-2 = E
	C1-3 = G2
	C1-4 = G1
	C1-5 = B
	C1-6 = K
	C1-7 = J
	C1-8 = H
	
	C2-1 = NC
	C2-2 = NC
	C2-3 = A
	C2-4 = F
	C2-5 = D
	C2-6 = C
	C2-7 = N
	c2-8 = M
	
	0-8
	1-9
	2-14
	3-15
	4-0
	5-5
	6-6
	7-7
	8-2
	9-3
	10-11
	11-1
	12-12
	13-13
	14-4
	15-10
	
8 9 14 15 0 5 6 7 2 3 11 1 12 13 4 10
9 10 15 16 1 6 7 3 4 12 2 13 14 5 11
*/
static const uint16_t alphafonttable[] PROGMEM = {

    0b0000000000000001, 0b0000000000000010, 0b0000000000000100,
    0b0000000000001000, 0b0000000000010000, 0b0000000000100000,
    0b0000000001000000, 0b0000000010000000, 0b0000000100000000,
    0b0000001000000000, 0b0000010000000000, 0b0000100000000000,
    0b0001000000000000, 0b0010000000000000, 0b0100000000000000,
    0b1000000000000000, 0b0000000000000000, 0b0000000000000000,
    0b0000000000000000, 0b0000000000000000, 0b0000000000000000,
    0b0000000000000000, 0b0000000000000000, 0b0000000000000000,
    0b0001001011001001, 0b0001010111000000, 0b0001001011111001,
    0b0000000011100011, 0b0000010100110000, 0b0001001011001000,
    0b0011101000000000, 0b0001011100000000,
    0b0000000000000000, //
    0b0000000000000110, // !
    0b0000001000100000, // "
    0b0001001011001110, // #
    0b0001001011101101, // $
    0b0000110000100100, // %
    0b0010001101011101, // &
    0b0000010000000000, // '
    0b0010010000000000, // (
    0b0000100100000000, // )
    0b0011111111000000, // *
    0b0001001011000000, // +
    0b0000100000000000, // ,
    0b0000000011000000, // -
    0b0000000000000000, // .
    0b0000110000000000, // /
    0b0000110000111111, // 0
    0b0000000000000110, // 1
    0b0000000011011011, // 2
    0b0000000010001111, // 3
    0b0000000011100110, // 4
    0b0010000001101001, // 5
    0b0000000011111101, // 6
    0b0000000000000111, // 7
    0b0000000011111111, // 8
    0b0000000011101111, // 9
    0b0001001000000000, // :
    0b0000101000000000, // ;
    0b0010010000000000, // <
    0b0000000011001000, // =
    0b0000100100000000, // >
    0b0001000010000011, // ?
    0b0000001010111011, // @
    0b0000000011110111, // A
    0b0001001010001111, // B
    0b0000000000111001, // C
    0b0001001000001111, // D
    0b0000000011111001, // E
    0b0000000001110001, // F
    0b0000000010111101, // G
    0b0000000011110110, // H
    0b0001001000000000, // I
    0b0000000000011110, // J
    0b0010010001110000, // K
    0b0000000000111000, // L
    0b0000010100110110, // M
    0b0010000100110110, // N
    0b0000000000111111, // O
    0b0000000011110011, // P
    0b0010000000111111, // Q
    0b0010000011110011, // R
    0b0000000011101101, // S
    0b0001001000000001, // T
    0b0000000000111110, // U
    0b0000110000110000, // V
    0b0010100000110110, // W
    0b0010110100000000, // X
    0b0001010100000000, // Y
    0b0000110000001001, // Z
    0b0000000000111001, // [
    0b0010000100000000, //
    0b0000000000001111, // ]
    0b0000110000000011, // ^
    0b0000000000001000, // _
    0b0000000100000000, // `
    0b0001000001011000, // a
    0b0010000001111000, // b
    0b0000000011011000, // c
    0b0000100010001110, // d
    0b0000100001011000, // e
    0b0000000001110001, // f
    0b0000010010001110, // g
    0b0001000001110000, // h
    0b0001000000000000, // i
    0b0000000000001110, // j
    0b0011011000000000, // k
    0b0000000000110000, // l
    0b0001000011010100, // m
    0b0001000001010000, // n
    0b0000000011011100, // o
    0b0000000101110000, // p
    0b0000010010000110, // q
    0b0000000001010000, // r
    0b0010000010001000, // s
    0b0000000001111000, // t
    0b0000000000011100, // u
    0b0010000000000100, // v
    0b0010100000010100, // w
    0b0010100011000000, // x
    0b0010000000001100, // y
    0b0000100001001000, // z
    0b0000100101001001, // {
    0b0001001000000000, // |
    0b0010010010001001, // }
    0b0000010100100000, // ~
    0b0011111111111111,

};