========================README FOR 8085 ASSEMBLY PROGRAMMING======================

-------------------------Basic syntax for this simulator---------------------------
-----------------------------------------------------------------------------------

My program is sensetive to spaces, tab and number of characters so, please follow the
following instructions.

0-> No spaces or tab before instruction and no multiple spaces or tab between instructions.
	MVI A 20H ✘✘
  MVI A 20H ✘✘
MVI		A	20H ✘✘
MVI A 20H ✔✔

1-> There must be only one space between instructions
MOV A    B ✘✘, MOVAB ✘✘, MOVA B ✘✘
MOV A B ✔✔, STA 2045H ✔✔

2-> All instructions should be in upper case.
mvi b a0h ✘✘, MVI B a0H ✘✘
MVI B A0H ✔✔

3-> There is no comma(,) between instructions but only one space.
MOV A, B ✘✘, MVI A, 21H ✘✘, LXI H, 2040H ✘✘
MOV A B ✔✔,  MVI A 21H ✔✔,  LXI H 2040H ✔✔

4-> Data must be 2-byte and address must be 4-byte followed by capital 'H'
MVI A 20h ✘✘, STA 2000 H ✘✘
LXI H 2020H ✔✔

5-> Any character after particular length of that instruction is ignored so comment can
be wrote down after that length.
MOV A B   ->since length of this instruction is 7, any character after 7th position is
			ignored.
MOV A BThis is comment (✔✔ but not good)
MOV A B This is comment (✔✔ and good)
			-> Do not use ':' in the comment
			-> comment must not be multiline.
MOV A B :This is comment ✘✘
MOV A B THIS
		IS				✘✘
		COMMENT

6->Labe must be decleared before ':', there is no space between label name and ':',
after ':' there is no space  for instruction.
LABEL:MVI A 20H ✘✘
LABEL    :MVI A 20H ✘✘
LABEL : MVI A 20H ✘✘
LABEL :
MVI A 20H		✘✘
LABEL : MVI A 20H ✘✘

LABEL:MVI A 20H	✔✔

7->Write "STOP" after the complition of your code and to execute that code.
If no "STOP" word is found, you cannot terminate from getting newline. STOP
acts as exit from getting new line.

MVI A 20H
MVI B 30H
ADD B						✔✔	
HLT
STOP

8->You can directly edit data.txt file for instructions that concern with read/write
operation with memory like STA, LXI, LDA, STAX etc.

MVI A 20H
STA 0001H
Go to (0001)th position of file to see the result from the instruction.

9->To execuite instruction from file.
	./8085 file_name
	OR
	.\8085.exe file_name

10->To change data of desired location
	Do you want to set memory [y/n]: y (OR Y)
	Enter starting address (4-byte): 4-byte_address
	Enter no. of address to change: 2-byte_data
11->To see data:
	Do you want to see memory[y/n]: y (OR Y)
	Single or multiple [s/m]: (s or m)
	Address (4-byte): 4-byte_address
	if single
		4-byte_address>> 2-byte_data
	else
		Enter no. of address to see: n
		Displays address upto n-1