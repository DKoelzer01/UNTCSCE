 	.data
 	.type	pi, %object
 pi:
 	.float 3.1416

    .text                 // program section
	.global main
	.arch armv8-a+fp+simd // processor type
	.type main, %function

	//Volume and Surface Area of Cone
	//Diameter and Height in S20 and S21
	//Pi in data section
	//Compute Volume and Surface Area in S22 and S23
main:
	FMOV S20, 10.0			//TESTER VALUE
	FMOV S21, 5.0			//TESTER VALUE

	ADR X9, pi				//Load address of Pi
	FMOV S9, S20			//Store Diameter in S9
	FMOV S10, 2.0			//Load 2.0 into S10 for FDIV
	FDIV S9, S9, S10		//Divide diameter by 2
	FMUL S10, S9, S9		//r^2
	LDUR S12, [X9, #0]		//Load pi into S12
	FMUL S22, S10, S12		//pi * r^2
	FMOV S13, 3.0
	FDIV S11, S21, S13		//h/3
	FMUL S22, S22, S11		//Calculate Volume

	FMUL S11, S21, S21		//h^2
	FADD S11, S11, S10		//h^2 + r^2
	FSQRT S11, S11			//SQRT ( h^2 + r^2 )
	FADD S11, S11, S9		//Add r
	FMUL S10, S12, S9		//pi * r
	FMUL S23, S10, S11		//Calculate Surface Area
	NOP
