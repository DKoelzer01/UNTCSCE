	.data
	.type	arr, %object
	.size	arr, 8

arr:
	.xword	8, 7, 6, 5, 4, 3, 2, 1


	.text                 // program section
	.global	main          // main
	.arch armv8-a+fp+simd // processor type
	.type main, %function // main function

main:
	//clear variables, as the stored value matters in calculations.
	MOV X20, XZR
	MOV X21, XZR
	MOV X22, XZR
	MOV X23, XZR

	ADR X9, arr
	LDUR X10, [X9, #0]
	ADD X20, X20, X10	//Add arr[0] to sum
	ADD X23, X23, X10	//Add arr[0] to calculate range

	LDUR X10, [X9, #8]
	ADD X20, X20, X10	//Add arr[1] to sum

	LDUR X10, [X9, #16]
	ADD X20, X20, X10	//Add arr[2] to sum

	LDUR X10, [X9, #24]
	ADD X20, X20, X10	//Add arr[3] to sum
	ADD X22, X22, X10	//Add arr[3] to calculate median

	LDUR X10, [X9, #32]
	ADD X20, X20, X10	//Add arr[4] to sum
	ADD X22, X22, X10	//Add arr[4] to calculate median

	LSR X22, X22, #1	//Find median by (arr[3] + arr[4]) / 2

	LDUR X10, [X9, #40]
	ADD X20, X20, X10	//Add arr[5] to sum

	LDUR X10, [X9, #48]
	ADD X20, X20, X10	//Add arr[6] to sum

	LDUR X10, [X9, #56]
	ADD X20, X20, X10	//Add arr[7] to sum
	SUB X23, X23, X10	//Sub arr[7] from arr[0] to find range

	ADD X21, X20, X21	//Take precalculated sum, find mean
	LSR X21, X21, #3	//Divide by 8
