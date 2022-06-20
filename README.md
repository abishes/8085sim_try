======================README FOR 8085 ASSEMBLY PROGRAMMING====================

-----------------------Basic syntax for this simulator-------------------------
-------------------------------------------------------------------------------
0-> Although this program is not case sensitive uppercase is preferred.

1-> There is no comma(,) between instructions but only one space.
MOV A, B ✘✘, MVI A, 21H ✘✘, LXI H, 2040H ✘✘
MOV A B ✔✔,  MVI A 21H ✔✔,  LXI H 2040H ✔✔

2-> Data must be 2-byte and address must be 4-byte hexa-decimal followed by 'h/H'
STA 2000 H ✘✘
LXI H 2020H ✔✔

3-> Any character after particular length of that instruction is ignored so
comment can be wrote down after that length.
MOV A B   ->since length of this instruction is 7, any character after 7th 
			position isignored.
MOV A BThis is comment (✔✔ but not readable)
MOV A B This is comment (✔✔ and readable)
			-> Do not use ':' in the comment
			-> comment must not be multiline.
MOV A B :This is comment ✘✘
MOV A B THIS
		IS				✘✘
		COMMENT

4->Label must be decleared before ':', there is no space between label 
name and ':', after ':' there is no space  for instruction.
LABEL: MVI A 20H ✘✘
LABEL : MVI A 20H ✘✘
LABEL :
MVI A 20H		✘✘
LABEL:MVI A 20H	✔✔

5->Write "EXIT/exit" after the complition of your code and to execute that code.
If no "EXIT/exit" word is found, you cannot terminate from getting newline.
MVI A 20H
MVI B 30H
ADD B						✔✔	
HLT
EXIT

6->You can directly edit data.txt file for instructions that concern with read/write
operation with memory like STA, LXI, LDA, STAX etc.

MVI A 20H
STA 0001H
Go to (0001)th position of file to see the result from the instruction.

7->To execuite instruction from file.
	./8085 file_name
	OR
	.\8085.exe file_name

8->To change data of desired location
	Do you want to set memory [y/n]: y (OR Y)
	Enter starting address (4-byte): 4-byte_address
	Enter no. of address to change: 2-byte_data
9->To see data:
	Do you want to see memory[y/n]: y (OR Y)
	Single or multiple [s/m]: (s or m)
	Address (4-byte): 4-byte_address
	if single
		4-byte_address>> 2-byte_data
	else
		Enter no. of address to see: n
		Displays address upto n-1