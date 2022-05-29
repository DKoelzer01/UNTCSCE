	.text                 // program section
	.global	main          // main
	.arch armv8-a+fp+simd // processor type
	.type main, %function // main function

main:
	MOV X20, XZR
	ADD X20, X20, #4 	// Value can be changed to test.
						// Using formula n^2 ( (2 * n^2) - 1)
	MUL X9, X20, X20 	// n^2
	LSL X10, X9, #1 	// 2*n^2
	SUB X10, X10, #1 	// 2*n^2 - 1
	MUL X21, X9, X10 	// Result
