#include "registersFlags.h"

flags::flags(){ /*to reset all flags*/
	CY = 0;
	Z  = 0;
	S  = 0;
	P  = 0;
	AC = 0;
}

bool flags::flagName(char flagName){ /*to retrive certain flag  value*/
	if(flagName == 'C')
		return CY;
	else if(flagName == 'A')
		return AC;
	else if(flagName == 'S')
		return S;
	else if(flagName == 'P')
		return P;
	else if(flagName == 'Z')
		return Z;
	else
		return 0;
}

void flags::flagSet(char flagName){	/*to set value to certain flag*/
	switch(flagName){
		case 'C':
			CY=1;
			break;
		case 'A':
			AC=1;
			break;
		case 'S':
			S=1;
			break;
		case 'P':
			P=1;
			break;
		case 'Z':
			Z=1;
			break;
	}
}

void flags::flagReset(char flagName){	/*to reset certain flag*/
	switch(flagName){
		case 'C':
			CY=0;
			break;
		case 'A':
			AC=0;
			break;
		case 'S':
			S=0;
			break;
		case 'P':
			P=0;
			break;
		case 'Z':
			Z=0;
			break;
	}
}

void flags::flagDisplay(){
	cout<<" -----------------Flags-----------------\n";
	cout << "|CY\t"<< "|Z\t"<< "|S\t"<< "|P\t"<< "|AC\t|\n";
	cout<<" ---------------------------------------\n";
	cout << "|" << CY << "\t|" << Z << "\t|" << S << "\t|" << P << "\t|" << AC << "\t|\n";
	cout<<" ---------------------------------------\n";
}

registers::registers()	/*to reset all flags*/
{	
	flags();
	A = "00";
	B = "00";
	C = "00";
	D = "00";
	E = "00";
	H = "00";
	L = "00";
}

string registers::registerName(char whichregister){ /*to retrive certain register value*/
	if(whichregister == 'A')
		return A;
	else if(whichregister == 'B')
		return B;
	else if(whichregister == 'C')
		return C;
	else if(whichregister == 'D')
		return D;
	else if(whichregister == 'E')
		return E;
	else if(whichregister == 'H')
		return H;
	else 
		return L;
	
}

void registers::registerSet(char registerName, string data)	/*to set certain register with given value*/
{
	switch (registerName)
	{
	case 'A':
		A = data;
		break;
	case 'B':
		B = data;
		break;
	case 'C':
		C = data;
		break;
	case 'D':
		D = data;
		break;
	case 'E':
		E = data;
		break;
	case 'H':
		H = data;
		break;
	case 'L':
		L = data;
		break;
	}
}

void registers::registerSet(char register1, char register2){	/*to exchange value between two registers*/
	switch(register1){
		case 'A':
			A = registerName(register2);
			break;
		case 'B':
			B = registerName(register2);
			break;
		case 'C':
			C = registerName(register2);
			break;
		case 'D':
			D = registerName(register2);
			break;
		case 'E':
			E = registerName(register2);
			break;
		case 'H':
			H = registerName(register2);
			break;
		case 'L':
			L = registerName(register2);
			break;
	}
}

void registers::registerDisplay()
{
	cout << " -----------------------Registers-----------------------\n";
	cout << "|A\t"<< "|B\t"<< "|C\t"<< "|D\t"<< "|E\t"<< "|H\t"<< "|L\t|\n";
	cout << " -------------------------------------------------------\n";
	cout << "|" << A << "H\t|" << B << "H\t|" << C << "H\t|" << D << "H\t|" << E << "H\t|" << H << "H\t|" << L << "H\t|\n";
	cout << " -------------------------------------------------------\n";
}

string registers::getM(){
	return M;
}
void registers::setM(string data){
	M = data;
	string address = H;
	address += L;
	writeMemory(addressStringToInt(address), dataStringToInt(data));
}