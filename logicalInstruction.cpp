#include "logicalInstruction.h"

void CMP(string& line, registers& R){ /*compare instruction with accmulator: to compare two datas*/
	char registerName = line[4];
	if(line.length() < 5)
		throw(error_instructionSize);
	if(!checkRegister(registerName))
		throw(error_register);
	int result;
	if(registerName == 'M')
		result = (R.registerName('A')).compare(R.getM());
	else
		result = (R.registerName('A')).compare(R.registerName(registerName));/*comparing strings in register A and given register*/
	if(result == 0){
		R.flagSet('Z');
	}
	else if(result < 0){
		R.flagSet('C');
	}
	else{
		R.flagReset('Z');
		R.flagReset('C');
	}
}

void CPI(string& line, registers& R){   /*compare immediate eith accmulator instruction*/
	string dataString;
	if(line.length() < 7)
		throw(error_instructionSize);
	char dataChar = line[4];
	if(!checkData(dataChar))
		throw(error_data);
	dataString.push_back(dataChar);
	dataChar = line[5];
	if(!checkData(dataChar))
		throw(error_data);
	dataString.push_back(dataChar);
	if(line[6] != 'H')
		throw(error_H);
	int result = (R.registerName('A')).compare(dataString);
	if(result == 0){
		R.flagSet('Z');
	}
	else if(result < 0){
		R.flagSet('C');
	}
	else{
		R.flagReset('Z');
		R.flagReset('C');
	}
}

void ANA_ORA_XRA(string& line, registers& R){
	char registerName = line[4];
	if(line.length() < 5)
		throw(error_instructionSize);
	if (!checkRegister(registerName))
		throw(error_register);
	int dataInt;
	if(registerName == 'M'){
		if(line[0]=='A')	//line[0]='A' for ANA instruction
			dataInt = dataStringToInt(R.registerName('A')) & dataStringToInt(R.getM());
		if(line[0]=='O')	//line[0]='O' for ORA instruction
			dataInt = dataStringToInt(R.registerName('A')) | dataStringToInt(R.getM());
		if(line[0]=='X')	//line[0]='X' for XRA instruction
			dataInt = dataStringToInt(R.registerName('A')) ^ dataStringToInt(R.getM());
	}
	else{
		if(line[0]=='A')
			dataInt = dataStringToInt(R.registerName(registerName)) & dataStringToInt(R.registerName('A'));
		if(line[0]=='O')
			dataInt = dataStringToInt(R.registerName(registerName)) | dataStringToInt(R.registerName('A'));
		if(line[0]=='X')
			dataInt = dataStringToInt(R.registerName(registerName)) ^ dataStringToInt(R.registerName('A'));
	}
	string dataString = dataIntToString(dataInt);
	//flags
	//Zero flag
	if (dataInt == 0)
		R.flagSet('Z');
	else
		R.flagReset('Z');
	//sign flag
	if(signChecker(dataInt))
		R.flagSet('S');
	else
		R.flagReset('S');
	/*parity flag*/
	if(parityChecker(dataInt))
		R.flagSet('P');
	else
		R.flagReset('P');
	R.flagReset('C');   /* cary flag is always reset*/
	R.flagSet('A');     /* auxilary flag is always set */

	R.registerSet('A',dataString);
}

void ANI_ORI_XRI(string& line, registers& R){
	string dataString;
	if(line.length() < 7)
		throw(error_instructionSize);
	char dataChar = line[4];
	if(!checkData(dataChar))
		throw(error_data);
	dataString.push_back(dataChar);
	dataChar = line[5];
	if(!checkData(dataChar))
		throw(error_data);
	dataString.push_back(dataChar);
	if(line[6] != 'H')
		throw(error_H);
	
	int dataInt;
	if(line[0]=='A')	//line[0]='A' for ANI instruction
		dataInt = dataStringToInt(R.registerName('A')) & dataStringToInt(dataString);
	if(line[0]=='O')	//line[0]='O' for ORI instruction
		dataInt = dataStringToInt(R.registerName('A')) | dataStringToInt(dataString);
	if(line[0]=='X')	//line[0]='X' for XRI instruction
		dataInt = dataStringToInt(R.registerName('A')) ^ dataStringToInt(dataString);
	dataString = dataIntToString(dataInt);
	//flags
	//Zero flag
	if (dataInt == 0)
		R.flagSet('Z');
	else
		R.flagReset('Z');
	//sign flag
	if(signChecker(dataInt))
		R.flagSet('S');
	else
		R.flagReset('S');
	/*parity flag*/
	if(parityChecker(dataInt))
		R.flagSet('P');
	else
		R.flagReset('P');
	R.flagReset('C');   /* cary flag is always reset*/
	R.flagSet('A');     /* auxilary flag is always set */
	R.registerSet('A',dataString);
}

void RLC(registers& R){
	string dataString = R.registerName('A');
	int dataInt=dataStringToInt(dataString);
	int carry= (dataInt & 128) >> 7;    /*to find if MSB is 0 or 1*/
	if(carry)
		R.flagSet('C');
	else
		R.flagReset('C');
	dataInt = (dataInt << 1) + carry;   /*shifting with adding carry gives rlc */
	dataInt &= 255;
	dataString = dataIntToString(dataInt);
	R.registerSet('A', dataString);
	return;
}

void RRC(registers& R){
	string dataString = R.registerName('A');
	int dataInt = dataStringToInt(dataString);
	int carry = dataInt & 1;
	if(carry)
		R.flagSet('C');
	else
		R.flagReset('C');
	
	dataInt = (dataInt >> 1) + (carry * 128);   /*128 is 1000 0000, which is multiplied with 0 or 1 to and added to make MSB*/
	dataString = dataIntToString(dataInt);
	R.registerSet('A', dataString);
}

void RAL(registers& R){
	int carryFlag = R.flagName('C');
	string dataString = R.registerName('A');
	int dataInt=dataStringToInt(dataString);
	int carry= (dataInt & 128) >> 7;
	if(carry)
		R.flagSet('C');
	else
		R.flagReset('C');
	dataInt = (dataInt << 1) + carryFlag;
	dataInt &= 255;
	dataString = dataIntToString(dataInt);
	R.registerSet('A', dataString);
	return;
}

void RAR(registers& R){
	int carryFlag =R.flagName('C');
	string dataString = R.registerName('A');
	int dataInt = dataStringToInt(dataString);
	int carry = dataInt & 1;
	if(carry)
		R.flagSet('C');
	else
		R.flagReset('C');
	
	dataInt = (dataInt >> 1) + (carryFlag * 128);
	dataString = dataIntToString(dataInt);
	R.registerSet('A', dataString);
}

void CMA(registers& R){ /*complement Accmulator instruction*/
	string dataString = R.registerName('A');
	int dataInt = dataStringToInt(dataString);
	dataInt = ~dataInt;
	dataString =dataIntToString(dataInt);
	R.registerSet('A', dataString);
}

void CMC(registers& R){ /*complement carry flag instruction*/
	int carryFlag = R.flagName('C');
	if(carryFlag)
		R.flagReset('C');
	else
		R.flagSet('C');
}

void STC(registers& R){ /*set carry flag instruction*/
	R.flagSet('C');
}
