//---------------------------------------------------------------------------
#include "stdafx.h"
#include "MyWave.h"
//---------------------------------------------------------------------------
#define SAMPLE_FREQUENCY 8000
#define RECOGNIZE_UNIT_LEN 3
using namespace std;
//---------------------------------------------------------------------------

MyWave::MyWave()
{
	riff[0] = 'R'; //"RIFF";
	riff[1] = 'I';
	riff[2] = 'F';
	riff[3] = 'F';

	wave[0] = 'W'; //"WAVE";
	wave[1] = 'A';
	wave[2] = 'V';
	wave[3] = 'E';

	fmt[0] = 'f';  //"fmt";
	fmt[1] = 'm';
	fmt[2] = 't';
	fmt[3] = ' ';

	unuse[0] = 16; //unuse[4]
	unuse[1] = 0;
	unuse[2] = 0;
	unuse[3] = 0;

	format = 1;    //int16_t PCM

	chnls = 1;     //int16_t; 1表示单声道、2表示双声道

	sampleRate = SAMPLE_FREQUENCY;    //int32_t
	dataRate = SAMPLE_FREQUENCY * 2;  //int32_t
	dataBlock = 2;	//  int16_t

	bits = 16;      //int16_t 
	data[0] = 'd';  //"data";
	data[1] = 'a';
	data[2] = 't';
	data[3] = 'a';

	voiceLen = (int32_t)(RECOGNIZE_UNIT_LEN * dataRate);   //  int32_t
	fileLen = (int32_t)(RECOGNIZE_UNIT_LEN * dataRate + sizeof(MyWave)-8);   //文件长度int32_t
}

MyWave::~MyWave()
{
}


