# Overview

The goal of the assembler is to generate an "object program." 

The object program is saved in a file or device and would be
loaded into the memory of an sic/xe machine (if one existed).

The object program consists of records.
The format of header, text, and end records is described on pg 48-49
Modification records are introduced on pg 64.
The format of define, refer, and modification records is on pg 89.



Text records are the meat of the object program containing 
assembly instruction object codes.

There are 4 object code formats specified to the bit on pg 498.

The format is determined by the nixbpe flags as well as the opcode.

# Summary of nixbpe flags

`n` indirect addressing - the value at the target address is the address of the operand.  (Note: can't be used with immediate addressing or indexed addressing)

`i` immediate addressing - Target address is the operand (Note: can't be used with indirect addressing or indexed addressing)

If `n` and `i` are both 1 or 0, then direct addressing is used. ie. The target address is the address of the operand.

SIC/XE instructions will set both `n` and `i` to 1 if direct addressing is desired, but if `n` and `i` are both 0, 
then the bpe bits are treated as part of the display address making it 15 bits long (this allows SIC instructions to access all 32 kb of it's memory).
If an SIC/XE machine executes an instruction with SIC direct addressing it will use the first 32 kb of it's memory.

`x` indexed addressing - Target address is offset by the contents of register X (TA += (X)) (Can't be used with either indirect or immediate addressing.)

`b` base relative addressing - Target address is offset by the contents of register B (TA += (B))

`p` program counter relative addressing - Target address is offset by the contents of register PC (TA += (PC))

Similar to indirect and immediate addressing, base relative and program counter addressing are mutually exclusive. However both bits will never be set to 1 at the same time.

`e` extended addressing - Target address is 20 bits instead of 12 


# SIC/XE Assembly language
Source files contain lines with 4 tab (`0x49`) delimited columns:
symbol column, operation column, operand column, and comments column.
If a line's first non-tab or space character is a period (`0xE2`) then all following characters on the line are treated as a comment.
Empty lines are treated the same way as comment lines.
Symbols cannot be named the same as other symbols, assembler directives, instruction mnemonics, or register names.


## Assumptions about SIC/XE assembly
Symbols, assembler directives, instruction mnemonics, instruction operands, and comments are not case sensitive.
Symbol names can only consist of ascii word characters (a-zA-Z). Digits, symbols such as `!` and `#`, and non-ascii characters are not supported.
Note: comments can contain these special characters.

Each tab delimited column can be delimited by spaces, or a combination of spaces and tabs.
Lines can begin with whitespace.

The end of a line is indicated by either `\r\n` or `\n`. It shouldn't matter which is used.

## Determining nixbpe flags from SIC/XE assembly

Each SIC/XE instruction has 1 or more valid instruction formats. 
In the case of instructions which can use either format 3 or 4 instructions the ways to determine which format is used are determined by notation provided by the language.
Format 3 is used by default unless a `+` prepends the mnemonic.
eg. `+LDA   SOME_ADDR   SOME_ADDR is a 20 bit address`
This instruction will have it's `e` flag set to 1 making it format 4.

Format 3 instructions can contain display addresses between 0 and 4095. It's the job of the assembler to use either pc relative or base relative addressing if the target
address is too large to be contained in a format 3 instruction.
However if the target address is still to large, it's the job of the programmer to indicate that format 4 should be used.
Note: these problems only exist on SIC/XE machines since SIC can access all of it's memory through direct addressing.

The assembler will first try to indicate the target address via direct addressing, if it's too large, then the assembler tries
pc relative and finally if pc relative doesn't work, base relative is tried. If all of these fail the target address is too large
for a format 3 instruction. It's an error if a target address is to large for a format 3 instruction and format 4 is not indicated. (pg. 59)

ie. The assembler will set the `b` and `p` flags automatically, by determining what the target address of an instruction is.

To tell the assembler what the contents of the base register are we use the directive: BASE SYMBOL which will tell the assembler that the base
register should contain the address of SYMBOL. The directive NOBASE indicates that the contents of the base register no longer
contains anything useful for addressing.
```
//based indicates that the BASE directive is in effect for some symbol.
if((0 <= TA) && (TA < 4096)) {
    //direct addressing
} else if ((PC - 2048 <= TA) && (TA < PC + 2048)) {
    //PC relative addressing
} else if (based && (B <= TA) && (TA < B + 4096)) {
    //base relative addressing
} else {
    //error use format 4
}
```
Assembler directives introduced in section 2.3 such as EQU, ORG, and USE can help overcome the limitations of pc and base relative addressing 
without using format 4 instructions.

To offset the target address by the contents of register X you append `,X` to the operand of an instruction.
eg. `LDA    SOME_ADDR,X    TA = SOME_ADDR + (X)`

To specify indirect addressing you prepend the operand with a `@`.
eg. `LDA    @SOME_ADDR      (A) = ((TA))`

To specify immediate addressing you prepend the operand with a `#`.
eg. `LDA    #SOME_ADDR      (A) = TA`

These can be done in combination with specifying format 4.


