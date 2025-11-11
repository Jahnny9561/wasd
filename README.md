# wasd

**wasd** is a custom programming language project implemented in C++.  

It currently supports lexical analysis, tokenization and a recursive-descent parser that validates the language's grammar.
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

## Supported grammar
The parser currently validates code structured according to the following grammar rules (BNF):
```
Z      -> Head Body
Head   -> "_" ident ":" 
Body   -> "{" block* "}" 
block  -> stm | Body
stm    -> assignment_stm | print_stm
 
assignment_stm -> ident "=" comparison
while_stm -> "while" comparison ":" Body
print_stm -> "print" comparison 
input_stm -> "input" ident

comparison -> expr ( ("<" | ">") expr )*
expr   -> term ( ("+" | "-")  term )*
term   -> factor ( ("*" | "/") factor )*
factor -> ident | integer | "(" comparison ")"
```


## How to use

1. Compile the code:

```bash
g++ main.cpp lexer.cpp parser.cpp -o wasd
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
```
## Future features
- Support for more functions, loops and conditionals
- Interpreter

## License

[MIT](./LICENSE)
