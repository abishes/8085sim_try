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
	char data[3];
	data[0] = line[6];  //higher order data
	data[1] = line[7];  //lower order data
	data[2] = '\0';
	if (!(checkData(data[0]) && checkData(data[1])))
	{
		cout << "invalid data in line :"<<lineNumber<<endl;
		return;
	}
	if (line[8] != 'H')
	{
		cout << "Data must end with H to indicate hexa in line :"<<lineNumber<<endl;
		return;
	}
	string dataString=data; // full data in string
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

void LDA(string &line, registers &R, int lineNumber){
	string address;
	if (line[8] != 'H')
	{
		cout << "Data must end with H to indicate hexa in line :"<<lineNumber<<endl;
		return;
	}
	for(int i =0; line[i+4] !='H';i++){
		if(!checkData(line[i+4])){
			cout<<"Invalid data in line:" << lineNumber <<endl;
			return;
		}
		address.push_back(line[i+4]);
	}
	R.registerSet('A', readMemory(addressStringToInt(address)));
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