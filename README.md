# CompilerDesign


### Lexical Analyser :

It creates tokens from thw given input C program. Tokens includes keywords(main, int, float, etc..), identifiers(variable names), operators(+, -, *, /, etc..), literals(variable values). The C program takes in input as the form of a C text file which then creates tokens present in every lines.


### Working :

- read line by line from the input file(LexicalAnalyser.txt).
- convert lines to a cluster of words.
- For each word, check if it is an operator, keyword, literals, identifiers.
- print corresponding token generated after the same.