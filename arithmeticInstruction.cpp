#include "arithmeticInstruction.h"

void ADD_ADC(string& line, registers& R, string instruction, int lineNumber){
	char registerName = line[4];
	if( !checkRegister(registerName)){
		cout<<"No such register in line :"<<lineNumber<<endl;
		return;
	}
	int dataInt;
	if (registerName == 'M')
		dataInt =  dataStringToInt(R.registerName('A')) + dataStringToInt(R.getM());
	else
		dataInt = dataStringToInt(R.registerName('A')) + dataStringToInt(R.registerName(registerName));
	if(instruction == "ADC"){
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

void ADI_ACI(string& line, registers& R, string instruction, int lineNumber){
	string dataString;
	char dataChar = line[4];
	if(!checkData(dataChar)){
		cout<<"invalid data in line :"<<lineNumber<<endl;
		return;
	}
	dataString.push_back(dataChar);
	dataChar = line[5];
	if(!checkData(dataChar)){
		cout<<"invalid data in line :"<<lineNumber<<endl;
		return;
	}
	dataString.push_back(dataChar);
	if(line[6] != 'H'){
		cout<<"data must end with 'H' in line :"<<lineNumber<<endl;
		return;
	}
	int dataInt = dataStringToInt(R.registerName('A')) + dataStringToInt(dataString);
	if(instruction == "ACI"){
		dataInt +=R.flagName('C');
	}
	int carry = (dataInt & 256) >> 8;  /*246 in binary is 1 0000 0000, used for getting carry*/
	dataInt &= 255;
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

void SUB_SBB(string& line, registers& R, string instruction, int lineNumber){
	char registerName = line[4];
	if( !checkRegister(registerName)){
		cout<<"No such register in line :"<<lineNumber<<endl;
		return;
	}
	int dataInt;
	if (registerName == 'M')
		dataInt = dataStringToInt(R.registerName('A')) - dataStringToInt(R.getM());
	else
		dataInt = dataStringToInt(R.registerName('A')) - dataStringToInt(R.registerName(registerName));
	if(instruction == "SBB"){
		dataInt -=R.flagName('C');
	}
	int borrow;
	if(dataInt < 0){
		dataInt = -dataInt;
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

void SUI_SBI(string& line, registers& R, string instruction, int lineNumber){
	string dataString;
	char dataChar = line[4];
	if(!checkData(dataChar)){
		cout<<"invalid data in line :"<<lineNumber<<endl;
		return;
	}
	dataString.push_back(dataChar);
	dataChar = line[5];
	if(!checkData(dataChar)){
		cout<<"invalid data in line :"<<lineNumber<<endl;
		return;
	}
	dataString.push_back(dataChar);
	if(line[6] != 'H'){
		cout<<"data must end with 'H' in line :"<<lineNumber<<endl;
		return;
	}
	int dataInt = dataStringToInt(R.registerName('A')) - dataStringToInt(dataString);
	if(instruction == "SBI"){
		dataInt -=R.flagName('C');
	}
	int borrow;
	if(dataInt < 0){
		dataInt = -dataInt;
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

void INR(string& line, registers& R, int lineNumber){
	char registerName = line[4];
	if(!checkRegister(registerName)){
		cout<<"No such register in line :"<<lineNumber<<endl;
		return;
	}
	int dataInt;
	if(registerName == 'M')
		dataInt = dataStringToInt(R.getM()) + 1;
	else
	dataInt = dataStringToInt(R.registerName(registerName)) + 1;
	if(dataInt > 255){
		dataInt &= 255;
	}
	string dataString = dataIntToString(dataInt);
	if (registerName == 'M')
		R.setM(dataString);
	else
		R.registerSet(registerName, dataString);
}

void DCR(string& line, registers& R, int lineNumber){
	char registerName = line[4];
	if(!checkRegister(registerName)){
		cout<<"No such register in line :"<<lineNumber<<endl;
		return;
	}
	int dataInt;
	if(registerName == 'M')
		dataInt = dataStringToInt(R.getM()) - 1;
	else
		dataInt = dataStringToInt(R.registerName(registerName)) - 1;
	if(dataInt < 0){
		dataInt = 255;
	}
	string dataString = dataIntToString(dataInt);
	if (registerName == 'M')
		R.setM(dataString);
	else
		R.registerSet(registerName, dataString);
}

void INX_DCX(string& line, registers& R, int lineNumber){
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
			if((addressInt + 1) > 65535){
				cout<<"Exceed memory ffff\n";
				return;
			}
			addressInt++;
		}
		else{
			if((addressInt - 1) < 0){
				cout<<"Exceed memory 0000\n";
				return;
			}
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
	else{
		cout<<"No such resister pairin line :"<<lineNumber;
	}
}