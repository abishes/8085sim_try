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

//for labels
void labelPush(string line,int lineNumber, mappingLabel& M){
	string labelName;
	for(int i = 0; i < (int)line.length();i++){
		if(line[i] == ':')
			break;
		labelName.push_back(line[i]);
	}
	M.putLabel(labelName, lineNumber);
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
