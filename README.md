# wasd

**wasd** is a custom programming language project implemented in C++.  

It features a complete compiler pipeline, including lexical analysis, recursive-descent parsing, semantic analysis with intermediate representation (IR) generation, and a virtual machine interpreter to execute the code.
## Current features

- Lexical analysis (lexer) - Tokenizes source code into identifiers, numbers, operators, and keywords.
- Tokenization of:
  - Identifiers (letters and digits, must start with a letter)
  - Numbers
  - Operators ( `+` `-` `*` `/` `=` `<` `>` )
  - Special characters ( `(` `)` `{` `}` `:` `;` `,` `_` )
  - Keywords ( `print` `while` `input`)
- Recursive-Descent Parser:
  - Consumes the token stream from the lexer.
  - Validates syntax against a formal grammar.
  - Provides error messages.
- Intermediate Representation (IR):
  - Performs Semantic Analysis during parsing.
  - Generates a linear Instruction Table based on Quadruples. ( `Op` `Arg1` `Arg2` `Result` )
  - Supports arithmetic, assignment, I/O and control flow branching ( `goto` )
- Interpreter:
  - Executes the IR commands via direct-mapped memory for high performance
  
## Supported grammar
The parser currently validates code structured according to the following grammar rules (BNF):
```
Z      -> Head Body
Head   -> "_" ident ":" 
Body   -> "{" block* "}" 
block  -> stm | Body
stm    -> assignment_stm | print_stm | assignment_stm | input_stm
 
assignment_stm -> ident "=" expr
while_stm -> "while" comparison ":" Body
print_stm -> "print" expr 
input_stm -> "input" ident

comparison -> expr ("<" | ">") expr
expr   -> term ( ("+" | "-")  term )*
term   -> factor ( ("*" | "/") factor )*
factor -> ident | integer | "(" expr ")"
```


## How to use

1. Compile the code:

```bash
g++ main.cpp lexer.cpp parser.cpp semantic.cpp interpreter.cpp -o wasd
```
2. Run with
```bash
./wasd  
```
Enter the path to a .txt file containing code in the language.

### Example
Suppose example.txt contains:
```ini
_wasd:
{
    input i
    a = 5
    while i + 2 < a+(10*2):
    {
       i = i + 1
       print i
    }
}
```

Running:
```bash
./wasd
Enter filename: example.txt
```
Produces:
```bash
--- Parser Start ---
--- Parser End Successfully ---
--- Symbol Table ---
11 | &5 | Identifier | value: 0
8 | &2 | Identifier | value: 0
7 | &1 | Identifier | value: 0
5 | 10 | Number | value: 10
10 | &4 | Identifier | value: 0
6 | 1 | Number | value: 1
3 | 5 | Number | value: 5
2 | a | Identifier | value: 0
4 | 2 | Number | value: 2
1 | i | Identifier | value: 0
9 | &3 | Identifier | value: 0
--- Token Stream ---
0 | _ | SpecialChar
1 | wasd | Identifier
2 | : | SpecialChar
3 | { | SpecialChar
4 | input | Keyword
5 | i | Identifier
6 | a | Identifier
7 | = | Operand
8 | 5 | Number
9 | while | Keyword
10 | i | Identifier
11 | + | Operand
12 | 2 | Number
13 | < | Operand
14 | a | Identifier
15 | + | Operand
16 | ( | SpecialChar
17 | 10 | Number
18 | * | Operand
19 | 2 | Number
20 | ) | SpecialChar
21 | : | SpecialChar
22 | { | SpecialChar
23 | i | Identifier
24 | = | Operand
25 | i | Identifier
26 | + | Operand
27 | 1 | Number
28 | print | Keyword
29 | i | Identifier
30 | } | SpecialChar
31 | } | SpecialChar

 -------- Instruction Table --------
Op | Arg1 | Arg2 | Res
INPUT   0       0       1
ASSIGN  3       0       2
ADD     1       4       7
MULT    5       4       8
ADD     2       8       9
SMALLER 7       9       10
GOTO_F  10      11      0
ADD     1       6       11
ASSIGN  11      0       1
PRINT   1       0       0
GOTO    2       0       0
Exit    0       0       0
----------------------------------------------

--- PROGRAM OUTPUT ---
Input value: 1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
--- EXIT INSTRUCTION REACHED ---
```
## Future features
- Support for more functions, loops and conditionals
- Debugger

## License

[MIT](./LICENSE)
