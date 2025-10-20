# wasd

**wasd** is a custom programming language project implemented in C++.  
It currently supports lexical analysis and tokenization of code written in the language.
## Current features

- Lexical analysis (lexer)
- Tokenization of:
  - Identifiers (letters and digits, must start with a letter)
  - Numbers
  - Operators ( `+`, `-`, `*`, `/`, `=`)
  - Special characters ( `(`, `)`, `;`, `,`, `_`, `{`, `}`, `:` )

## How to use

1. Compile the code:

```bash
g++ main.cpp lexer.cpp -o wasd
```
2. Run with
```bash
./wasd  
```
Enter the path to a .txt file containing code in the language.
The lexer will output a table of tokens with their position, value, and type.

### Example
Suppose example.txt contains:
```ini
sum = 2 + a
```

Running:
```bash
./wasd
Enter filename: example.txt
```
Produces:
```bash
4 | + | Operand
3 | 2 | Number
5 | a | Identifier
2 | = | Operand
1 | sum | Identifier
```
## Future features
- Parser
- Support for functions, loops, and conditionals

## License

[MIT](./LICENSE)
