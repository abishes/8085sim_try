#include "dataTransfer.h"

void MVI(string &line, registers &R)
{
	char registerNname = line[4];
	if(line.length() < 9){
		throw(error_instructionSize);
		return;
	}
	if (!checkRegister(registerNname)){
		throw(error_register);
		return;
	}

	if (line[5] != SPACE){
		throw(error_space);
		return;
	}

	if (!(checkData(line[6]) && checkData(line[7]))){
		throw(error_data);
		return;
	}

	if (line[8] != 'H'){
		throw(error_H);
		return;
	}
	string dataString;
	dataString.push_back(line[6]);
	dataString.push_back(line[7]);

	if (registerNname == 'M'){ // for M (memory HL pair)
		R.setM(dataString);
		return;
	}
	
	R.registerSet(registerNname, dataString);
	return;
}

void MOV(string &line, registers &R)
{
	char register1 = line[4];
	if(line.length() < 7){
		throw(error_instructionSize);
		return;
	}
	if (line[5] != SPACE){
		throw(error_space);
		return;
	}
	char register2 = line[6];
	if (!(checkRegister(register1) && checkRegister(register2))){
		throw(error_register);
		return;
	}
	if(register1 == 'M'){
		throw(error_H);
		return;
	}
	if( register2 == 'M'){
		R.registerSet(register1, R.getM());
		return;
	}
	R.registerSet(register1, register2);
	return;
}

void LDA_STA(string &line, registers &R){
	string address;
	if(line.length() < 9){
		throw(error_instructionSize);
		return;
	}
	if (line[8] != 'H')
	{
		throw(error_H);
		return;
	}
	for(int i =0; line[i+4] !='H';i++){
		if(!checkData(line[i+4])){
			throw(error_data);
			return;
		}
		address.push_back(line[i+4]);
	}
	if(line[0] == 'L')
	R.registerSet('A', readMemory(addressStringToInt(address)));
	else{
		writeMemory(addressStringToInt(address),dataStringToInt(R.registerName('A')));
	}
	//OR
	// int addressInt = addressStringToInt(address);
	// string data = readMemory(addressStringToInt(address));
	// R.registerSet('A', data);
}

void LXI(string& line, registers& R){
	string Haddress;	//higher order address
	string Laddress;	//lower order address
	if(line.length() < 11){
		throw(error_instructionSize);
		return;
	}
	if(line[5] != ' '){
		throw(error_space);
		return;
	}
	if(line[4] == 'B' || line[4] == 'D' || line[4] == 'H'){
		if(line[10] != 'H'){
			throw(error_H);
			return;
		}
		for(int i =0; line[i+8] !='H';i++){
			if(!checkData(line[i+6]) || !checkData(line[i+8])){
				throw(error_data);
				return;
			}
			Haddress.push_back(line[i+6]);
			Laddress.push_back(line[i+8]);
		}
		if(line[4] == 'H'){ //for HL
			R.registerSet('H', Haddress);
			R.registerSet('L', Laddress);
		}
		else{	//for BC and DE pair
			R.registerSet(line[4], Haddress);
			R.registerSet(char (line[4] + 1), Laddress);
		}
	}
	else{
		throw(error_registerPair);
		return;
	}
}

void LDAX_STAX(string& line, registers& R, int lineNumber){
	if(line.length()< 6){
		throw(error_instructionSize);
		return;
	}
	if(line[5] == 'B' || line[5] == 'D'){
		string lineToLDA = "LDA ";
		string lineToSTA = "STA ";
		string Haddress = R.registerName(line[5]);
		string Laddress = R.registerName(char(line[5] + 1));
		if(line[0] == 'L'){		//line[0]='l' represents it is ldax instruction.
			lineToLDA = lineToLDA + Haddress + Laddress;
			lineToLDA += 'H';
			LDA_STA(lineToLDA, R);
		}
		else{
			lineToSTA = lineToSTA + Haddress + Laddress;
			lineToSTA += 'H';
			LDA_STA(lineToSTA, R);
		}
	}
	else{
		cout<<"Invalid register pair(B/D) in line: "<<lineNumber<<endl;
	}
}

void LHLD(string& line, registers& R){
	string address;
	if(line.length() < 10){
		throw(error_instructionSize);
		return;
	}
	if (line[9] != 'H')
	{
		throw(error_H);
		return;
	}
	for(int i =0; line[i+5] !='H';i++){
		if(!checkData(line[i+5])){
			throw(error_data);
			return;
		}
		address.push_back(line[i+5]);
	}
	R.registerSet('L', readMemory(addressStringToInt(address)));
	if((addressStringToInt(address) + 1) > 0xffff){
		throw(error_memoryExceed);
		return;
	}
	R.registerSet('H', readMemory(addressStringToInt(address) + 1));
}

void SHLD(string& line, registers& R){
	string address;
	if(line.length() < 10){
		throw(error_instructionSize);
		return;
	}
	if (line[9] != 'H')
	{
		throw(error_H);
		return;
	}
	for(int i =0; line[i+5] !='H';i++){
		if(!checkData(line[i+5])){
			throw(error_data);
			return;
		}
		address.push_back(line[i+5]);
	}
	writeMemory(addressStringToInt(address), dataStringToInt(R.registerName('L')));
	if(addressStringToInt(address) > 0xffff){
		throw(error_memoryExceed);
		return;
	}
	writeMemory((addressStringToInt(address) + 1),dataStringToInt(R.registerName('H')));
}

void XCHG(registers& R){
	string temp = R.registerName('H');
	R.registerSet('H', R.registerName('D'));
	R.registerSet('D', temp);
	temp = R.registerName('L');
	R.registerSet('L', R.registerName('E'));
	R.registerSet('E', temp);
}
