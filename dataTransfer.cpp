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
	// int addressInt = addressStringToInt(address);
	// string data = readMemory(addressStringToInt(address));
	// R.registerSet('A', data);
	// OR in 1 line
	R.registerSet('A', readMemory(addressStringToInt(address)));
}