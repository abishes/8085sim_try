#include "dataTransfer.h"

void MVI(string &line, registers &R, int lineNumber)
{
	char registerNname = line[4];
	if (!checkRegister(registerNname))
	{
		cout << "No such register in line :"<<lineNumber<<endl;
		return;
	}
	if (line[5] != SPACE)
	{
		cout << "Space required between Register and data in line :"<<lineNumber<<endl;
		return;
	}
	if (!(checkData(line[6]) && checkData(line[7])))
	{
		cout << "invalid data in line :"<<lineNumber<<endl;
		return;
	}
	string dataString;
	dataString.push_back(line[6]);
	dataString.push_back(line[7]);
	
	if (line[8] != 'H')
	{
		cout << "Data must end with H to indicate hexa in line :"<<lineNumber<<endl;
		return;
	}
	R.registerSet(registerNname, dataString);
	return;
}

void MOV(string &line, registers &R, int lineNumber)
{
	char register1 = line[4];
	if (line[5] != SPACE)
	{
		cout << "No spaces between registers in line :"<<lineNumber<<endl;
		return;
	}
	char register2 = line[6];
	if (!(checkRegister(register1) && checkRegister(register2)))
	{
		cout << "No such registers in line :"<<lineNumber<<endl;
		return;
	}
	R.registerSet(register1, register2);
	return;
}

void LDA_STA(string &line, registers &R, int lineNumber){
	string address;
	if (line[8] != 'H')
	{
		cout << "Data must end with H in line :"<<lineNumber<<endl;
		return;
	}
	for(int i =0; line[i+4] !='H';i++){
		if(!checkData(line[i+4])){
			cout<<"Invalid data in line:" << lineNumber <<endl;
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

void LXI(string& line, registers& R, int lineNumber){
	string Haddress;	//higher order address
	string Laddress;	//lower order address
	if(line[5] != ' '){
		cout<<"No space in line: "<< lineNumber << endl;
	}
	if(line[4] == 'B' || line[4] == 'D' || line[4] == 'H'){
		if(line[10] != 'H'){
			cout << "Data must be of 4-byte and end with H in line: "<< lineNumber<< endl;
		}
		for(int i =0; line[i+8] !='H';i++){
			if(!checkData(line[i+6]) || !checkData(line[i+8])){
				cout<<"Invalid data in line:" << lineNumber <<endl;
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
		cout<<"No such register pair in line: " << lineNumber << endl;
		return;
	}
}

void LDAX_STAX(string& line, registers& R, int lineNumber){
	if(line[5] == 'B' || line[5] == 'D'){
		string lineToLDA = "LDA ";
		string lineToSTA = "STA ";
		string Haddress = R.registerName(line[5]);
		string Laddress = R.registerName(char(line[5] + 1));
		if(line[0] == 'L'){
			lineToLDA = lineToLDA + Haddress + Laddress;
			lineToLDA += 'H';
			LDA_STA(lineToLDA, R, lineNumber);
		}
		else{
			lineToSTA = lineToSTA + Haddress + Laddress;
			lineToSTA += 'H';
			LDA_STA(lineToSTA, R, lineNumber);
		}
	}
	else{
		cout<<"Invalid register pair(B/D) in line: "<<lineNumber<<endl;
	}
}

void LHLD(string& line, registers& R, int lineNumber){
	string address;
	if (line[9] != 'H')
	{
		cout << "Data must end with H in line :"<<lineNumber<<endl;
		return;
	}
	for(int i =0; line[i+5] !='H';i++){
		if(!checkData(line[i+5])){
			cout<<"Invalid data in line:" << lineNumber <<endl;
			return;
		}
		address.push_back(line[i+5]);
	}
	R.registerSet('L', readMemory(addressStringToInt(address)));
	if((addressStringToInt(address) + 1) > 65535){
		cout << "Exceed memory FFFF\n";
		return;
	}
	R.registerSet('H', readMemory(addressStringToInt(address) + 1));
}

void SHLD(string& line, registers& R, int lineNumber){
	string address;
	if (line[9] != 'H')
	{
		cout << "Data must end with H in line :"<<lineNumber<<endl;
		return;
	}
	for(int i =0; line[i+5] !='H';i++){
		if(!checkData(line[i+5])){
			cout<<"Invalid data in line:" << lineNumber <<endl;
			return;
		}
		address.push_back(line[i+5]);
	}
	writeMemory(addressStringToInt(address), dataStringToInt(R.registerName('L')));
	if(addressStringToInt(address) > 65535){
		cout << "Exceed memory FFFF\n";
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
