# A Simple Calculator App for leaning C++

## Instructions
```bash
mkdir build
```
```bash
cd build; cmake ..
```
```bash
# If using a editor such as Neovim run this to enable completions in your LSP (clangd)
ln -s compile_commands.json ../
```

## Building
```bash
cd build; cmake --build .
```
Remaining Suggestions from Josh:
```
1) Add support for real numbers, scientific notation, roots, and exponents. Don't forget expressions that result in NaN or infinity.

2) Add more detailed error messages like "Error in expression at N" where N is the character index the error occurred. Consider displaying a compiler like error that draws the expression and an arrow pointing to the error. Custom exception types will be helpful here.

3) Advanced: Split the implementation into a tokenizer/lexer, parser, and evaluator. A postfix (reverse polish notation) workflow will help you with the evaluator. Rather than RPN, you could try an Abstract Syntax Tree, but these are pretty advanced to setup and evaluate. My suggestion is use RPN for now.
```
```
