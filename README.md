# wasd

**wasd** is a custom programming language project implemented in C++.  

It currently supports lexical analysis, tokenization and a recursive-descent parser that validates the language's grammar and generates an Intermediate Representation (IR) using Quadruples.
## Current features

- Lexical analysis (lexer)
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
g++ main.cpp lexer.cpp parser.cpp semantic.cpp -o wasd
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
    i = 1
    while i < 10: 
    {
       i = i + 1
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
10 | 10 | Number
8 | while | Keyword
12 | } | SpecialChar
6 | = | Operand
11 | + | Operand
9 | < | Operand
5 | i | Identifier
7 | 1 | Number
4 | { | SpecialChar
3 | : | SpecialChar
2 | wasd | Identifier
1 | _ | SpecialChar

--- Token Stream ---
0 | _ | SpecialChar
1 | wasd | Identifier
2 | : | SpecialChar
3 | { | SpecialChar
4 | i | Identifier
5 | = | Operand
6 | 1 | Number
7 | while | Keyword
8 | i | Identifier
9 | < | Operand
10 | 10 | Number
11 | : | SpecialChar
12 | { | SpecialChar
13 | i | Identifier
14 | = | Operand
15 | i | Identifier
16 | + | Operand
17 | 1 | Number
18 | } | SpecialChar
19 | } | SpecialChar

 -------- Instruction Table --------
Op | Arg1 | Arg2 | Res
INPUT   -       -       i
ASSIGN  5       -       a
ADD     i       2       &1
MULT    10      2       &2
ADD     a       &2      &3
SMALLER &1      &3      &4
GOTO_F  &4      11      -
ADD     i       1       &5
ASSIGN  &5      -       i
PRINT   i       -       -
GOTO    2       -       -
```
## Future features
- Support for more functions, loops and conditionals
- Interpreter

## License

[MIT](./LICENSE)
