#include "branchAndMemory.h"
//for memory
void openMemory(){
	cout<<"Setting memory\n";
	srand(time(0));
	int data;
	ifstream file("data.txt");
	if(!file.is_open()){
		file.close();
		ofstream fileTemp("data.txt");
		if(fileTemp.is_open()){
			for(int i = 0; i <= 65535; i++){
			data = rand()%255;
			if(data < 16)
				fileTemp << hex << 0 << data <<" ";
			else
				fileTemp << hex << data << " ";
			}
		}
		else{
			cout<<"File cannot creat\n";
		}
		fileTemp.close();
	}	
}

string readMemory(int memory){
	string data;
	ifstream file("data.txt");
	if(!file.is_open()){
		cout<<"Cannot open the file\n";
		return string("XX");
	}
	file.seekg(memory * 3);
	file>> data;
	file.close();
	data[0]=toupper(data[0]);
	data[1]=toupper(data[1]);
	return data;
}

void writeMemory(int address, int data){
	fstream file("data.txt");
	if(!file.is_open()){
		cout<<"Cannot open the file\n";
		return;
	}
	file.seekp(address * 3);
	if(data < 16)
		file << hex << 0 << data <<" ";
	else
		file << hex << data << " ";
	file.close();
}

void setMemory(){
	char choice;
	while (1){
		cout << "Do you want to set memory [y/n]: ";
		cin >> choice;
		if(choice == 'y'|| choice == 'Y' || choice == 'n' || choice == 'N')
			break;
	}
	if(choice == 'n' || choice == 'N')
		return;
	string startingAddressStr;
	string data;
	int startingAddress;
	int no_OfAddress;
	while(1){
		cout << "Enter starting address (4-byte): ";
		cin >> startingAddressStr;
		if(checkAddress(startingAddressStr))
			break;
	}
	startingAddress = addressStringToInt(startingAddressStr);
	cout << "Enter no. of address to change: ";
	cin >> no_OfAddress;
	cout << "Enter data\n";
	for(int i = 0; i < no_OfAddress && startingAddress < 0xffff; i++){
		cout << addressIntToString(startingAddress) << ">> ";
		cin >> data;
		if(!check2BitData(data)){
			cout << " Enter again ";
			i--;
			startingAddress--;
		}
		else
			writeMemory(startingAddress, dataStringToInt(data));
		startingAddress++;
	}
}

void seeMemory(){
	char choice;
	while(1){
		cout << "Single or multiple [s/m]: ";
		cin >> choice;
		if(choice == 's' || choice == 'S' || choice == 'm' || choice == 'M')
			break;
	}
	string startingAddressStr;
	int startingAddress;
	while(1){
		cout << "Address (4-byte): ";
		cin >> startingAddressStr;
		if(checkAddress(startingAddressStr))
			break;
	}
	startingAddress = addressStringToInt(startingAddressStr);
	if(choice == 'm' || choice == 'M'){
		int no_OfAddress;
		cout << "Enter no. of address to see: ";
		cin >> no_OfAddress;
		for(int i = 0; i < no_OfAddress && startingAddress < 0xffff; i++){
			cout << addressIntToString(startingAddress + i) << ">> ";
			cout << readMemory(startingAddress + i) << endl;
		}
		return;
	}
	cout << readMemory(startingAddress) << endl;
}

void codeFromFile(const char* fileName, vector<string>& code, mappingLabel& M, int& lineNumber){
	ifstream file(fileName);
	string line;
	while(getline(file, line)){
		cout << line << endl;
		if(line[0] != '\0')
			code.push_back(line);
		if(line.find(':') != string::npos){
			labelPush(line, lineNumber, M);
		}
		lineNumber++;
	}
}
//for labels
void labelPush(string line,int lineNumber, mappingLabel& M){
	string labelName;
	for(int i = 0; i < (int)line.length();i++){
		if(line[i] == ':')
			break;
		labelName.push_back(line[i]);
	}
	M.putLabel(labelName, lineNumber-1);
}

void mappingLabel::putLabel(string labelName,int lineNumber){
		if(label.find(labelName) != label.end()){
			return;
		}
		label[labelName]=lineNumber;
	}

int mappingLabel::getLabel(string labelName){
		int number = label[labelName];
		if(number != 0){
		int lineNumber = label[labelName];
		return lineNumber;
		}
		else{
			cout<<"No such label as \""<<labelName<<"\"\n";
			return -10;
		}
}
