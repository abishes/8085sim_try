#include "dataComparision.h"

int charToInt(char X){  /*Converts character to equivalent integer i.e hexadecimal to decimal*/
	if((int)X >= 48 && (int)X <= 57){   /* ascii code of 0 is 48 and 9 is 57*/
		return ((int)X)-48;
	}
	if((int)X >= 65 && (int)X <= 70){   /*ascii code of 'A' is 65 and 'F' is 70*/
		return ((int)X)-55;
	}
	return 0;
}

char intToChar(int num){ /*converts decimal integer to hexadecimal character*/
	if(num >= 0 && num <= 9){
		return char(num + 48);
	}
	if(num >=10 && num <= 15){
		return char(num + 55);
	}
	return 'X';
}

int dataStringToInt(string dataString){ /*converts whole string(hexaDecimal) into integer(decimal)*/
	return charToInt(dataString[0])*16 + charToInt(dataString[1]);
}

string dataIntToString(int dataInt){    /*converts decimal into hexadecimal string*/
	int higherOrderData = (dataInt & 240) >> 4;	// XXXX AAAA & 240 -> XXXX 0000 and >> 4 gives 0000 XXXX 
	int lowerOrderData = dataInt & 15;
	string dataString;
	dataString.push_back(intToChar(higherOrderData));
	dataString.push_back(intToChar(lowerOrderData));
	return dataString;
}

int addressStringToInt(string address){
	return charToInt(address[0])*16*16*16 + charToInt(address[1])*16*16 + charToInt(address[2])*16 + charToInt(address[3]);
}

string addressIntToString(int addressInt){
	string address;
	int higherOrderAddress = (addressInt & 65280) >> 8;//XXXX XXXX AAAA AAA & 65280 -> XXXX XXXX 0000 0000
	int lowerOrderAddress = addressInt & 255;
	address += dataIntToString(higherOrderAddress);
	address += dataIntToString(lowerOrderAddress);
	return address;
}

bool checkRegister(char registerName)
{
	if ((((int)registerName) >= 65 && ((int)registerName <= 69)) || registerName == 'H' || registerName == 'L')
		return 1;
	return 0;
}

bool checkData(char data)
{
  if (((int)data >= 65 && (int)data <= 70) || ((int)data >= 48 && (int)data <= 57))
		return 1;
	return 0;
}

bool parityChecker(int data){
	int i, count = 0, bit;
	for(i = 0; i < 8; i++){
		bit = data & (1 << i);
		if(bit)
			count++;
	}
	if(count % 2 == 0)
		return 1;
	else
		return 0;
}

bool signChecker(int data){
	data &= 128;
	if(data)
		return 1;
	else
		return 0;
}

bool auxiliaryCarryChecker(string data1, string data2, string operation){
	int ac;
	if(operation == "ADD"){
		ac = charToInt(data1[1]) + charToInt(data2[1]);
		if(ac > 15)
			return 1;
		else
			return 0;
	}
	else if(operation == "SUB"){
		ac = charToInt(data1[1]) - charToInt(data2[1]);
		if(ac < 0)
			return 1;
		else
			return 0;
	}
	else
		return 0;
}
