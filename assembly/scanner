
.data
inBuf:		.space 80
prToken:		.word	0:3			# space to copy one token at a time
tableHead:	.asciiz "TOKEN    TYPE\n"
st_prompt:	.asciiz	"Enter an input string:\n"
end_prompt:	.asciiz "EXITED CODE 0:\n"
curToken:	.word 	0,0
tabToken:	.word	0:30		# 10 entries in token table
curType:		.word	0

	.text
	#s0 reserved for T
	#s3 reserved for char 
	#t6 iteration(i) for tabtable
	#t0 i for inbuf
main:		
		li	$t0, 0			# i = 0 for inbuf
		li	$t6, 0			#i = 0 in tabtable
		
nextLine:
		jal getline
		lb	$a0, inBuf		# if (inBuf[0] != '#')
		beq	$a0, '#', dump
		la	$s1, Q0
		li	$s0, 1
nextState:	lw	$s2, 0($s1)     #loads states addres ex firsrt iteration loads state 0
		jalr	$v1, $s2		# Save return addr in $v1
		sll	$s0, $s0, 2	# Multiply by 4 for word boundary
		add	$s1, $s1, $s0     
		sra	$s0, $s0, 2
		lw	$s1, 0($s1)
		b	nextState
		
		jal	printTabToken
		jal	clearInbuf
		b 	nextLine
dump:
		li $v0, 10
		syscall
############################################################################################################		
getline:
		la	$a0, st_prompt		# Prompt to enter a new line
		li	$v0, 4
		syscall

		la	$a0, inBuf		# read a new line to inBuf
		li	$a1, 80	
		li	$v0, 8
		syscall

		jr	$ra				
#############################################################################################################
ACT1:
		#read a char from keyboard
		#set t that value
				
nextChar:
		lb	$a0, inBuf($t0)		# $a0: search key
		jal	getTypes		# $s0 = getType(key)
		addi	$t0, $t0, 1		# i++
		beq	$s0, 6, nextChar	# if (char != ' ') goto saveType
		jr	$v1
##############################################################################################################
#act1 helper
#note: $s3 contains char & s0 is T(Type)
getTypes:
		li	$s0, -1			#   not found flag
		li	$t1, 0			#   j = 0
loop:		sll	$t9, $t1, 3		#   $t9 = 8*j for byte offset
		lb	$s3, tabChar($t9) 	#   $s1 = tabChar[j,0]
		beq	$s3, 0x5C, ret		#   if (char == endOfTable) return
		beq	$s3, $a0, found		#   while (tabChar[j,0] != key)
		addi	$t1, $t1, 1		#	j++;
		b	loop
found:		lw	$s0, tabChar+4($t9) 	#   type = Tabchar[j,1]
		lw	$s3, tabChar($t9)	#   char = Tachar[j, 0]			
ret:		jr	$ra
#################################################################################################################
ACT2:
		#using v1 s0 s3, and t1
		#curtoken is empty
		#add first char to token 
		#return T
		sw	$s0, curType		#type is saved in mem
		li 	$t4, 0
##################################################################################################################
ACT3:		
		sb 	$s3, curToken($t4)	#$curToken[0]currchar
		addi	$t4, $t4, 1		#i++
			
		
		jr 	$v1
##################################################################################################################
ACT4:
		#t6 for table iteration
		#token is full or diffrent type was found
		#save token into tabtoken table
		lw 	$s4, curType
		lw 	$s5, curToken		#loads currtoken word
		sw 	$s5, tabToken($t6)		#saves token to tabtoken
		lw 	$s5, curToken+4		#loads currtoken's second word
		sw 	$s5, tabToken+4($t6)		#saves second token to tabtokens second spot
		sw 	$s4, tabToken+8($t6)		#save type in third cell
		addi 	$t6, $t6, 12		#iterate to next line in tabtable
		#clear token  
		sw 	$zero, curToken			
		sw 	$zero, curToken+4
		
		jr 	$v1
##################################################################################################################
RETURN:
		#end program after eol
		#TODO
		move $a3, $t6
		jal	printTabToken
		b 	main
###################################################################################################################
ERROR:
		li $v0, 10
		syscall
		#program is broken goto return
###################################################################################################################
#######################################################################
#
#  printToken:
#	print Token table header
#	copy each entry of tabToken into prToken and print TOKEN
#
#	in Main(), $a3 has the byte index to last entry in the tabToken
#
########################################################################
		


printTabToken:
		la	$a0, tableHead		# print table heading
		li	$v0, 4
		syscall

		# copy 2-word token from tabToken into prToken
		#  run through prToken, and replace 0 (Null) by ' ' (0x20)
		#  so that printing does not terminate prematurely
		li	$t0, 0
loopTok:		bge	$t0, $a3, donePrTok	# if ($t0 <= $a3)
	
		lw	$t1, tabToken($t0)	#   copy tabTok[] into prTok
		sw	$t1, prToken
		lw	$t1, tabToken+4($t0)
		sw	$t1, prToken+4
	
		li	$t7, 0x20		# blank in $t7
		li	$t9, -1			# for each char in prTok
loopChar:	addi	$t9, $t9, 1
		bge	$t9, 8, tokType		
		lb	$t8, prToken($t9)		#   if char == Null
		bne	$t8, $zero, loopChar	
		sb	$t7, prToken($t9)		#       replace it by ' ' (0x20)
		b	loopChar

		# to print type, use four bytes: ' ', char(type), '\n', and Null
		#  in order to print the ASCII type and newline
tokType:
		li	$t6, '\n'			# newline in $t6
		sb	$t7, prToken+8
		#sb	$t7, prToken+9
		lb	$t1, tabToken+8($t0)
		addi	$t1, $t1, 0x30		# ASCII(token type)
		sb	$t1, prToken+9
		sb	$t6, prToken+10		# terminate with '\n'
		sb	$0, prToken+11
		
		la	$a0, prToken		# print token and its type
		li	$v0, 4
		syscall
	
		addi	$t0, $t0, 12
		sw	$0, prToken		# clear prToken
		sw	$0, prToken+4
		b	loopTok

donePrTok:
		jr	$ra


	
#####################################################################################################################

###################################################################################################################
clearInbuf:
		li	$t0, 0				# i=0
rept_clear:
		bge	$t0, 20, ret_clear		# while (i<20) {
		sw	$zero, inBuf($t0)			#   inBuf[i] = 0;
		addi	$t0, $t0, 1			#   i++;
		b	rept_clear			# }
ret_clear:
		jr	$ra
######################################################################################################################
clearToken:
		.data
		
tabState:

Q0:     .word  ACT1
        .word  Q1   # T1
        .word  Q1   # T2
        .word  Q1   # T3
        .word  Q1   # T4
        .word  Q1   # T5
        .word  Q1   # T6
        .word  Q11  # T7

Q1:     .word  ACT2
        .word  Q2   # T1
        .word  Q5   # T2
        .word  Q3   # T3
        .word  Q3   # T4
        .word  Q4   # T5
        .word  Q0   # T6
        .word  Q11  # T7

Q2:     .word  ACT1
        .word  Q6   # T1
        .word  Q7   # T2
        .word  Q7   # T3
        .word  Q7   # T4
        .word  Q7   # T5
        .word  Q7   # T6
        .word  Q11  # T7

Q3:     .word  ACT4
        .word  Q0   # T1
        .word  Q0   # T2
        .word  Q0   # T3
        .word  Q0   # T4
        .word  Q0   # T5
        .word  Q0   # T6
        .word  Q11  # T7

Q4:     .word  ACT4
        .word  Q10  # T1
        .word  Q10  # T2
        .word  Q10  # T3
        .word  Q10  # T4
        .word  Q10  # T5
        .word  Q10  # T6
        .word  Q11  # T7

Q5:     .word  ACT1
        .word  Q8   # T1
        .word  Q8   # T2
        .word  Q9   # T3
        .word  Q9   # T4
        .word  Q9   # T5
        .word  Q9   # T6
        .word  Q11  # T7

Q6:     .word  ACT3
        .word  Q2   # T1
        .word  Q2   # T2
        .word  Q2   # T3
        .word  Q2   # T4
        .word  Q2   # T5
        .word  Q2   # T6
        .word  Q11  # T7
 
Q7:     .word  ACT4
        .word  Q1   # T1
        .word  Q1   # T2
        .word  Q1   # T3
        .word  Q1   # T4
        .word  Q1   # T5
        .word  Q1   # T6
        .word  Q11  # T7

Q8:     .word  ACT3
        .word  Q5   # T1
        .word  Q5   # T2
        .word  Q5   # T3
        .word  Q5   # T4
        .word  Q5   # T5
        .word  Q5   # T6
        .word  Q11  # T7

Q9:     .word  ACT4
        .word  Q1  # T1
        .word  Q1  # T2
        .word  Q1  # T3
        .word  Q1  # T4
        .word  Q1  # T5
        .word  Q1  # T6
        .word  Q11 # T7

Q10:	.word	RETURN
        .word  Q10  # T1
        .word  Q10  # T2
        .word  Q10  # T3
        .word  Q10  # T4
        .word  Q10  # T5
        .word  Q10  # T6
        .word  Q11  # T7

Q11:    .word  ERROR 
	.word  Q4  # T1
	.word  Q4  # T2
	.word  Q4  # T3
	.word  Q4  # T4
	.word  Q4  # T5
	.word  Q4  # T6
	.word  Q4  # T7
 
tabChar:
	.word	0x09, 6		# tab
	.word 	0x0a, 6		# LF

 	.word ' ', 6
 	.word '#', 5
	.word '$', 4
	.word '(', 4 
	.word ')', 4 
	.word '*', 3 
	.word '+', 3 
	.word ',', 4 
	.word '-', 3 
	.word '.', 4 
	.word '/', 3 

	.word '0', 1
	.word '1', 1 
	.word '2', 1 
	.word '3', 1 
	.word '4', 1 
	.word '5', 1 
	.word '6', 1 
	.word '7', 1 
	.word '8', 1 
	.word '9', 1 

	.word ':', 4 

	.word 'A', 2
	.word 'B', 2 
	.word 'C', 2 
	.word 'D', 2 
	.word 'E', 2 
	.word 'F', 2 
	.word 'G', 2 
	.word 'H', 2 
	.word 'I', 2 
	.word 'J', 2 
	.word 'K', 2
	.word 'L', 2 
	.word 'M', 2 
	.word 'N', 2 
	.word 'O', 2 
	.word 'P', 2 
	.word 'Q', 2 
	.word 'R', 2 
	.word 'S', 2 
	.word 'T', 2 
	.word 'U', 2
	.word 'V', 2 
	.word 'W', 2 
	.word 'X', 2 
	.word 'Y', 2
	.word 'Z', 2

	.word 'a', 2 
	.word 'b', 2 
	.word 'c', 2 
	.word 'd', 2 
	.word 'e', 2 
	.word 'f', 2 
	.word 'g', 2 
	.word 'h', 2 
	.word 'i', 2 
	.word 'j', 2 
	.word 'k', 2
	.word 'l', 2 
	.word 'm', 2 
	.word 'n', 2 
	.word 'o', 2 
	.word 'p', 2 
	.word 'q', 2 
	.word 'r', 2 
	.word 's', 2 
	.word 't', 2 
	.word 'u', 2
	.word 'v', 2 
	.word 'w', 2 
	.word 'x', 2 
	.word 'y', 2
	.word 'z', 2

	.word	0x5c, -1		# if you â€˜\â€™ as the end-of-table symbol
