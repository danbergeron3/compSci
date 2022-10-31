
.data
inBuf:		.space 80
prToken:		.word	0:2			# space to copy one token at a time
tableHead:	.asciiz "TabSym:\n"
st_prompt:	.asciiz	"Enter an input string:\n"
end_prompt:	.asciiz "EXITED CODE 0:\n"
tab:		.word	' '
nl:		.word	0x0a
curToken:	.word 	0,0
tabToken:	.word	0:60		# 12 entries in token table
curType:	.word	0
tabSym:		.word	0:60
prSymTok:	.word	0:3
LOC:		.word	0x0400
LOCchar:	.word	0
              #will store address of current tabtoken

	.text
	#s0 reserved for T
	#s3 reserved for char 
	#t6 iteration(i) for tabtable
	#t0 i 
	#t7 iteration for tabSym
		li	$t7, 0			#j = 0 in tabSym
main:		
###################################################################################
#HW4
		
		
nextLine:
		li	$t6, 0			#i = 0 in tabtoken
		li	$t0, 0			# i = 0 for inbuf
		jal 	getline
		lb	$a0, inBuf		# if (inBuf[0] != '#')
		beq	$a0, '#', exit
		la	$s1, Q0
		li	$s0, 1
nextState:	lw	$s2, 0($s1)     	#loads states addres ex firsrt iteration loads state 0
		jalr	$v1, $s2		# Save return addr in $v1
		sll	$s0, $s0, 2		# Multiply by 4 for word boundary
		add	$s1, $s1, $s0     
		sra	$s0, $s0, 2
		lw	$s1, 0($s1)
		b	nextState
#end of hw4
##########################################################################
	#using s4, s5, $t3 = defen, t2 = comma t0 = i $t7 = j or tabSym index
nextTok:
 	#:   if (tabToken[i+1][0] != ‘:’) goto operator
 	addi 	$t0, $t0, 12		#i + 1
 	lw	$s4, tabToken($t0)
 	subi	$t0, $t0, 12		#i - 1
 	bne	$s4, ':', operator
	#curtoken = tabtoken[i][0]
	lw	$s4, tabToken($t0)
	sw	$s4, curToken
	lw	$s4, tabToken+4($t0)
	sw	$s4, curToken+4 	
 	li	$t3, 1			#defen = 1
 	jal	VAR
 	addi	$t0, $t0, 24		#i = i + 2  check 
 
operator:

#	lw	$s5, LOC
#	addi	$s5, $s5, 4		#LOC += 4
#	sw	$s5, LOC	
	addi	$t0, $t0, 12    	#i++ 		
	li	$t2, 1			#isComma = true
chkVar: 
	#if (tabToken[i][0] == ‘#’) goto dump	// ‘#’
	lw	$s5, tabToken($t0) 	#tabtoken[i][0]
	beq	$s5, '#', dump 		#if'		' == '#') goto dump
	#if (!isComma || tabToken[i][1]!=2) goto nextVar
	beq	$t2, 0, nextVar		#!isComma //short circuit eval
	lw	$s5, tabToken+8($t0)	#tabToken[i][1] Note: the one is the the next column tabtoken so where type is stored
	bne	$s5, 2, nextVar		#'             ' != 2
	#curToken = tabToken[i][0]
	lw	$s4, tabToken($t0)#check
	sw	$s4, curToken
	lw	$s4, tabToken+4($t0)
	sw	$s4, curToken+4
	li	$t3, 0			#defen = 0
	jal	VAR			#VAR (curToken, 0)
	
nextVar:
	#:  isComma = (tabToken[i][0] == ‘,’) //t2 == iscomma
	lw	$s4, tabToken($t0)
	beq	$s4, ',', nextVar2
	b 	nextVar3
nextVar2:
	#iscomma = bool val true
	li 	$t2, 1
	b 	nextVarDone
nextVar3:
	#iscomma = bool val false
	li	$t2, 0
	b	nextVarDone
nextVarDone:
	addi 	$t0, $t0, 12	#i++
	b	chkVar		#goto chkVar
	
############################################################################
VAR:	#stores items in symbol table in this order curtoken, Loc, defen, 
	#store reg is s4
	#t3 is defn $t7 = j for tabSym
	lw	$s5, curToken
	sw	$s5, tabSym($t7)
	lw	$s5, curToken+4
	sw	$s5, tabSym+4($t7)
	lw	$s5, LOC
	sw	$s5, tabSym+8($t7)
	sw	$t3, tabSym+12($t7)	#defn = tabSym[3]
	addi	$t7, $t7, 16			#j++
	sw	$zero, curToken
	sw	$zero, curToken+4	#zeros curtoken
	jr	$ra
		

############################################################################################################		
dump:
		lw	$s5, LOC
		addi	$s5, $s5, 4		#LOC += 4
		sw	$s5, LOC
		jal	clearInbuf
		jal	clearTabToken
		
		
		
		b	nextLine
exit:
		move	$a3, $t7 # end of list
		la	$t3, printTabSym 
		jalr	$v1, $t3
		li 	$v0, 10
		syscall
############################################################################################################
printTabSym:
		#a3 holds end of list t7 index t2 = byte index
		#print head 
		la	$a0, tableHead		# title
		li	$v0, 4
		syscall
		li 	$t7, 0		#i = 0 
		
printRept:	
		bge	$t7, $a3, printDone 
		#repeat untill it reaches end
		#load item first item into outbuff 
		#loads the labels to print
		lw	$s4, tabSym($t7)
		sw	$s4, prSymTok
		lw	$s4, tabSym+4($t7)
		sw	$s4, prSymTok+4
		
		
		la	$a0, prSymTok	
		li	$v0, 4
		syscall
		
		#tab
		la	$a0, tab
		li	$v0, 4
		syscall		
		
		lw	$a0, tabSym+8($t7)
		jal	hex2char
		
		sw	$v0, LOCchar
		la	$a0, LOCchar	
		li	$v0, 4   
		syscall
		
		la	$a0, tab
		li	$v0, 4
		syscall
		
		lw	$a0, tabSym+12($t7)
		li	$v0, 1
		syscall
		#newline
		la	$a0, nl
		li	$v0, 4
		syscall
		
		# zeros prSymTok
		sw	$0, prSymTok
		sw	$0, prSymTok+4
		
		addi 	$t7, $t7, 16	#i++
		b	printRept
printDone:
		jr	$v1
	
	
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
#		beq	$s0, 6, nextChar	# if (char != ' ') goto saveType
		
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

		move 	$a3, $t6
		#jal	printTabToken
		li 	$t0, 0	#i =0 // index to tabToken[][]
		b 	nextTok
###################################################################################################################
ERROR:
		li $v0, 10
		syscall
		#program is broken goto return
###################################################################################################################
###################################################################################################################
clearInbuf:
		li	$t0, 0				# i=0
rept_clear:
		bge	$t0, 20, ret_clear		# while (i<20) {
		sw	$zero, inBuf($t0)		#   inBuf[i] = 0;
		addi	$t0, $t0, 4			#   i++;
		b	rept_clear			# }
ret_clear:
		jr	$ra
######################################################################################################################
clearTabToken:	
		li	$t0, 0		# i = 0 for clear 	 
rept_clear2:		
		bge 	$t0, 240, clearTokDone	#while i < 15 
		sw  	$zero, tabToken($t0)	#tabtok[i] = 0
		addi	$t0, $t0, 4		#i++
		b	rept_clear2 	
clearTokDone:
		li	$t0, 0		# i = 0 for clear 
		jr	$ra
###########################################################################################################		
###########################################################################################################
###########################################################################################################
# 	hex2char:
#	    Function used to print a hex value into ASCII string.
#	    Convert a hex value in $a0 to char hex in $v0 (0x6b6a in $a0, $v0 should have 'a''6''b''6')
#
#	    4-bit mask slides from right to left in $a0.
#		As corresponding char is collected into $v0,
#		$a0 is shifted right by four bits for the next hex digit in the last four bits
#
#	Make it sure that you are handling nested function calls in return addresses
#
		.data
saveReg:	.word	0:3

		.text
hex2char:
		# save registers
		sw	$t0, saveReg($0)	# hex digit to process
		sw	$t1, saveReg+4($0)	# 4-bit mask
		sw	$t9, saveReg+8($0)

		# initialize registers
		li	$t1, 0x0000000f		# $t1: mask of 4 bits
		li	$t9, 3			# $t9: counter limit

nibble2char:
		and 	$t0, $a0, $t1		# $t0 = least significant 4 bits of $a0

		# convert 4-bit number to hex char
		bgt	$t0, 9, hex_alpha	# if ($t0 > 9) goto alpha
		# hex char '0' to '9'
		addi	$t0, $t0, 0x30		# convert to hex digit
		b	collect

hex_alpha:
		addi	$t0, $t0, -10		# subtract hex # "A"
		addi	$t0, $t0, 0x61		# convert to hex char, a..f

		# save converted hex char to $v0
collect:
		sll	$v0, $v0, 8		# make a room for a new hex char
		or	$v0, $v0, $t0		# collect the new hex char

		# loop counter bookkeeping
		srl	$a0, $a0, 4		# right shift $a0 for the next digit
		addi	$t9, $t9, -1		# $t9--
		bgez	$t9, nibble2char

		# restore registers
		lw	$t0, saveReg($0)
		lw	$t1, saveReg+4($0)
		lw	$t9, saveReg+8($0)
		jr	$ra
######################################################################################################

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

