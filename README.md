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
- Debugger:
  - Executes the IR commands in steps and helps the user track down any errors
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


## How to build

### Prerequisites

```bash
A C++ compiler (G++, Clang, or MSVC) supporting C++11 or higher
```
### Compile 

```bash
g++ main.cpp lexer.cpp parser.cpp semantic.cpp interpreter.cpp -o wasd
```
## How to run 

### Method 1: Launcher
Simply run the executable.
```bash
./wasd  
```
Enter the path to a .txt/.wasd file containing code in the language.

### Method 2: Command Line Argument
Pass the filename directly to the executable.
```bash
./wasd example.wasd
```
### Method 3: Custom File Extension (Windows)
- You can associate .wasd files so they open automatically with your interpreter:

  - Create a script file and name it test.wasd.

  - Right-click the file and select Open With > Choose another app.

  - Scroll to the bottom and click More apps > Look for another app on this PC.

  - Select your compiled wasd.exe.

  - Check "Always use this app to open .wasd files".

  - Now, simply double-clicking any .wasd file will execute your code!

## Debugger mode

When running a program, you can choose Debug Mode (d). This launches the visual debugger:
- **Step-by-step execution**: Press `Enter` to continue
- **Live Instruction View**: See exactly which operation (ADD, SUB, JUMP, etc) is happening.
- **Memory Tracking**: The console reports exactly which variable changed and shows the old -> new value.

## Code examples

### Loop 
example.wasd:
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
### Fibonacci Sequence
fibunacci.wasd:
```ini
_fibonacci:
{
    input limit
    
    a = 0
    b = 1
    
    print a
    print b
    
    current = a + b
    
    while current < limit :
    {
        print current
        
        a = b
        b = current
        current = a + b
    }
}
```

## Future features
- Support for more functions, loops and conditionals

## License

[MIT](./LICENSE)
