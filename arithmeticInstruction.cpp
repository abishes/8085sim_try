#include "arithmeticInstruction.h"

void ADD_ADC(string& line, registers& R){
	char registerName = line[4];
	if(line.length() < 5)
		throw(error_instructionSize);
	if( !checkRegister(registerName))
		throw(error_register);
	int dataInt;
	if (registerName == 'M')
		dataInt =  dataStringToInt(R.registerName('A')) + dataStringToInt(R.getM());
	else
		dataInt = dataStringToInt(R.registerName('A')) + dataStringToInt(R.registerName(registerName));
	if(line[2]== 'C'){	//line[2]='C' is possible in ADC only
		dataInt +=R.flagName('C');
	}
	int carry = (dataInt & 256) >> 8;  /*246 in binary is 1 0000 0000, used for getting carry*/
	dataInt &= 255;
	string dataString= dataIntToString(dataInt);
	/*Flags*/
	/*Carry flag*/
	if(carry)
		R.flagSet('C');
	else
		R.flagReset('C');
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
	/*Auxilary flag*/
	if(auxiliaryCarryChecker(R.registerName('A'), R.registerName(registerName), "ADD"))
		R.flagSet('A');
	else
		R.flagReset('A');
	R.registerSet('A',dataString);
}

void ADI_ACI(string& line, registers& R){
	string dataString;
	char dataChar = line[4];
	if(line.length() < 7)
		throw(error_instructionSize);
	
	if(!checkData(dataChar))
		throw(error_data);

	dataString.push_back(dataChar);
	dataChar = line[5];
	if(!checkData(dataChar))
		throw(error_data);

	dataString.push_back(dataChar);
	if(line[6] != 'H')
		throw(error_H);

	int dataInt = dataStringToInt(R.registerName('A')) + dataStringToInt(dataString);
	if(line[1]=='C'){	//line[1]='C' is possible only in ACI instruction 
		dataInt +=R.flagName('C');
	}
	int carry = (dataInt & 0x100) >> 8;  /*hex(100) in binary is 1 0000 0000, used for getting carry*/
	dataInt &= 0xff;
	dataString= dataIntToString(dataInt);
	/*Flags*/
	/*Carry flag*/
	if(carry)
		R.flagSet('C');
	else
		R.flagReset('C');
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
	/*Auxilary flag*/
	if(auxiliaryCarryChecker(R.registerName('A'), dataString, "ADD"))
		R.flagSet('A');
	else
		R.flagReset('A');
	R.registerSet('A',dataString);
}

void SUB_SBB(string& line, registers& R){
	char registerName = line[4];
	if(line.length() < 5)
		throw(error_instructionSize);
	if( !checkRegister(registerName))
		throw(error_register);

	int dataInt;
	if (registerName == 'M')
		dataInt = dataStringToInt(R.registerName('A')) - dataStringToInt(R.getM());
	else
		dataInt = dataStringToInt(R.registerName('A')) - dataStringToInt(R.registerName(registerName));
	if(line[1]=='B'){	//line[1]='B' in SBB instruction only
		dataInt -=R.flagName('C');
	}
	int borrow;
	if(dataInt < 0){
		dataInt = 0x100 + dataInt;	//since data is -ve, hex(100) - data is the required data
		borrow = 1;
	}
	else
		borrow = 0;
	string dataString= dataIntToString(dataInt);
	/*Flags*/
	/*Carry flag*/
	if(borrow)
		R.flagSet('C');
	else
		R.flagReset('C');
	//Zero flag
	if (dataInt == 0)
		R.flagSet('Z');
	else
		R.flagReset('Z');
	//sign flag
	if(borrow)
		R.flagSet('S');
	else
		R.flagReset('S');
	/*parity flag*/
	if(parityChecker(dataInt))
		R.flagSet('P');
	else
		R.flagReset('P');
	/*Auxilary flag*/
	if(auxiliaryCarryChecker(R.registerName('A'), R.registerName(registerName), "SUB"))
		R.flagSet('A');
	else
		R.flagReset('A');
	R.registerSet('A',dataString);
}

void SUI_SBI(string& line, registers& R){
	string dataString;
	char dataChar = line[4];
	if(line.length() < 7)
		throw(error_instructionSize);

	if(!checkData(dataChar))
		throw(error_data);

	dataString.push_back(dataChar);
	dataChar = line[5];
	if(!checkData(dataChar))
		throw(error_data);

	dataString.push_back(dataChar);
	if(line[6] != 'H')
		throw(error_H);

	int dataInt = dataStringToInt(R.registerName('A')) - dataStringToInt(dataString);
	if(line[1]=='B'){ 	//line[1]='B' in SBI only
		dataInt -=R.flagName('C');
	}
	int borrow;
	if(dataInt < 0){
		dataInt = 0x100 + dataInt;	//since data is -ve, hex(100) - data is the required data
		borrow = 1;
	}
	else
		borrow = 0;
	dataString= dataIntToString(dataInt);
	/*Flags*/
	/*Carry flag*/
	if(borrow)
		R.flagSet('C');
	else
		R.flagReset('C');
	//Zero flag
	if (dataInt == 0)
		R.flagSet('Z');
	else
		R.flagReset('Z');
	//sign flag
	if(borrow)
		R.flagSet('S');
	else
		R.flagReset('S');
	/*parity flag*/
	if(parityChecker(dataInt))
		R.flagSet('P');
	else
		R.flagReset('P');
	/*Auxilary flag*/
	if(auxiliaryCarryChecker(R.registerName('A'), dataString, "SUB"))
		R.flagSet('A');
	else
		R.flagReset('A');
	R.registerSet('A',dataString);
}

void INR(string& line, registers& R){
	char registerName = line[4];
	if(line.length() < 5)
		throw(error_instructionSize);
	if(!checkRegister(registerName))
		throw(error_register);

	int dataInt;
	if(registerName == 'M')
		dataInt = (dataStringToInt(R.getM()) + 1) % 0x100;	//highest increase can be ff only
	else
	dataInt = (dataStringToInt(R.registerName(registerName)) + 1) % 0x100;//hex(1000) is 1 0000 0000 so the range is 00 to ff

	string dataString = dataIntToString(dataInt);
	if (registerName == 'M')
		R.setM(dataString);
	else
		R.registerSet(registerName, dataString);
}

void DCR(string& line, registers& R){
	char registerName = line[4];
	if(line.length() < 5)
		throw(error_instructionSize);
	if(!checkRegister(registerName))
		throw(error_register);

	int dataInt;
	if(registerName == 'M')
		dataInt = dataStringToInt(R.getM()) - 1;
	else
		dataInt = dataStringToInt(R.registerName(registerName)) - 1;
	if(dataInt < 0){
		dataInt = 0xff;
	}
	string dataString = dataIntToString(dataInt);
	if (registerName == 'M')
		R.setM(dataString);
	else
		R.registerSet(registerName, dataString);
	if(dataInt == 0)
		R.flagSet('Z');
	else
		R.flagReset('Z');
}

void INX_DCX(string& line, registers& R){
	if(line.length() < 5)
		throw(error_instructionSize);
	if(line[4] == 'B' || line[4] == 'D' || line[4] == 'H'){
		string address;
		if(line[4] == 'H'){
			address += R.registerName('H');
			address += R.registerName('L');
		}
		else{
			address += R.registerName(line[4]);
			address += R.registerName(char(line[4] + 1));
		}
		int addressInt = addressStringToInt(address);
		if(line[0] == 'I'){
			if((addressInt + 1) > 0xffff)
				throw(error_memoryExceed);
			addressInt++;
		}
		else{
			if((addressInt - 1) < 0)
				throw(error_memoryExceed);
			addressInt--;
		}
		address = addressIntToString(addressInt);
		string lowerAdderss;
		lowerAdderss.push_back(address[2]);
		lowerAdderss.push_back(address[3]); 
		string higherAdderss;
		higherAdderss.push_back(address[0]);
		higherAdderss.push_back(address[1]);
		if(line[4] == 'H'){
			R.registerSet('H', higherAdderss);
			R.registerSet('L', lowerAdderss);
		}
		else{
			R.registerSet(line[4], higherAdderss);
			R.registerSet(char (line[4]+1), lowerAdderss);
		}
	}
	else
		throw(error_registerPair);
}

void DAA(string& line,registers& R){
	string dataString = R.registerName('A');
	int carry = 0;
	int HigherData = charToInt(dataString[0]);
	int LowerData = charToInt(dataString[1]);
	if(LowerData > 9 || R.flagName('A')){
		LowerData += 6;
		if(LowerData > 15){
			LowerData -= 16;
			carry = 1;
			R.flagSet('A');
		}
	}
	HigherData += carry;
	if(HigherData <= 9 && !R.flagName('C')){
		R.flagReset('C');
	}
	if(HigherData > 9 || R.flagName('C')){
		HigherData += 6;
		if(HigherData > 15){
			HigherData -= 16;
			R.flagSet('C');
		}
	}
	dataString[0] = intToChar(HigherData);
	dataString[1] = intToChar(LowerData);
	R.registerSet('A',dataString);
	//Zero flag
	if (dataStringToInt(dataString) == 0)
		R.flagSet('Z');
	else
		R.flagReset('Z');
	//sign flag
	if(signChecker(dataStringToInt(dataString)))
		R.flagSet('S');
	else
		R.flagReset('S');
	/*parity flag*/
	if(parityChecker(dataStringToInt(dataString)))
		R.flagSet('P');
	else
		R.flagReset('P');
}

void DAD(string& line, registers& R){
	if(line.length() < 5)
		throw(error_instructionSize);
	if( line[4] == 'B'|| line[4] == 'D'|| line[4] == 'H'){	//line[4] is register pair name
		int data16_1 = (dataStringToInt(R.registerName('H')) << 8) + dataStringToInt(R.registerName('L'));
							// shifting << 8 gives XXXX XXXX 0000 0000
		int data16_2;
		if(line[4] == 'H')
			data16_2 = data16_1;
		else
			data16_2 = (dataStringToInt(R.registerName(line[4])) << 8) + dataStringToInt(R.registerName(char(line[4] + 1)));
		
		data16_1 += data16_2;
		if(data16_1 > 0xffff){
			R.flagSet('C');
			data16_1 -= 0x10000;
		}
		else
			R.flagReset('C');
		string dataString = addressIntToString(data16_1);
		string dataStrHigher, dataStrLower;
		dataStrHigher.push_back(dataString[0]);
		dataStrHigher.push_back(dataString[1]);
		dataStrLower.push_back(dataString[2]);
		dataStrLower.push_back(dataString[3]);
		R.registerSet('H', dataStrHigher);
		R.registerSet('L', dataStrLower);
	}
	else
		throw(error_registerPair);
}
