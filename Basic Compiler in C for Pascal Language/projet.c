#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Define constants for different token types used in lexical analysis
// These constants represent various keywords, operators, and symbols
#define program 1         // "program" keyword
#define id 2              // Identifier (variable names)
#define pt 3              // '.' symbol
#define pv 4              // ';' symbol
#define var 5             // "var" keyword
#define dp 6              // ':' symbol
#define v 7               // ',' symbol
#define integer 8         // "integer" keyword
#define chart 9           // "chart" keyword
#define begin 10          // "begin" keyword
#define end 11            // "end" keyword
#define iff 12            // "iff" keyword (if statement)
#define whilee 13         // "whilee" keyword (while loop)
#define write 14          // "write" keyword
#define writeln 15        // "writeln" keyword
#define read 16           // "read" keyword
#define readln 17         // "readln" keyword
#define aff 18            // Assignment operator ":="
#define po 19             // '(' symbol (opening parenthesis)
#define pf 20             // ')' symbol (closing parenthesis)
#define opadd 21          // Addition operators: '+', '-', '||'
#define opmul 22          // Multiplication operators: '*', '%', '&&', '/'
#define oprel 23          // Relational operators: '<', '>', '<>', '<=', '>='
#define nb 24             // Numbers (numeric values)
#define elsee 25          // "elsee" keyword (else statement)
#define then 26           // "then" keyword (if-then condition)
#define do 27             // "do" keyword (used in loops)
#define ppe 28            // '<=' operator (less than or equal to)
#define dif 29            // '<>' operator (not equal to)
#define ppq 30            // '<' operator (less than)
#define pgq 31            // '>' operator (greater than)
#define pge 32            // '>=' operator (greater than or equal to)
#define ega 33            // '=' operator (equal to)
#define add 34            // '+' operator (addition)
#define sub 35            // '-' operator (subtraction)
#define or 36             // "||" operator (logical OR)
#define mul 37            // '*' operator (multiplication)
#define div 38            // '/' operator (division)
#define mod 39            // '%' operator (modulus)
#define and 40            // "&&" operator (logical AND)
#define comment 41        // Comment block "(* ... *)"

// Structure representing a lexical unit
// 'ul' represents the token type, 'att' represents additional attributes (like identifier index or numeric value)
typedef struct unilex {
    int ul;   // Token type
    int att;  // Attribute (index or value)
} unilex;

// Global variables
int c = 0;                // Counter for identifiers
FILE *file_input;                 // Pointer to the input file
FILE *file_output;                 // Pointer to the output file

// Array of keyword token values
int mot_cle[20] = {1, 10, 5, 8, 9, 11, 12, 13, 14, 15, 16, 17, 25, 26, 27};

// Array of keyword strings
char tab_mot_cle[20][20] = {"program", "begin", "var", "integer", "chart", "end", "iff", "whilee", "write", "writeln", "read", "readln", "elsee", "then", "do"};

// Array to store identifiers
char tab_iden[100][20];
char car;               // Current character being analyzed
unilex symbole;         // Current lexical unit
char ch[20];            // Buffer to store a word or number
int z = 0;              // Buffer index

// Function to move the file pointer backward by 'k' positions
void reculer(int k) {
    fseek(file_input, -k, SEEK_CUR);
}

// Function to read the next character from the file
char carsuivant() {
    return fgetc(file_input);
}

// Function to identify if the current word is a keyword or an identifier
int unilexid() {
    int k = 0;
    int i = 0;
    while (i < 15 && !k) {
        if (strcmp(tab_mot_cle[i], ch) == 0) {  // Check if the word matches a keyword
            k = 1;
        } else {
            i++;
        }
    }
    if (k == 1) {
        return mot_cle[i];
    } else {
        return id;
    }  // Return the corresponding token value or 'id' for identifiers
}

// Function to store an identifier in the symbol table and return its index
int rangerid(int k, int *c) {
    int s = 0;
    if (k == id) {  // Only store identifiers
        while ((strcmp(tab_iden[s], ch) != 0) && (s < (*c))) {
            s++;  // Search for the identifier in the table
        }
        if (s < *c) {
            return s;  // Return the index if found
        } else {
            strcpy(tab_iden[*c], ch);  // Add new identifier to the table
            return (*c)++;
        }
    } else {
        return 0;
    }
}

// Main lexical analysis function
unilex analex() {
    int etat = 0;        // Initial state
    int colonne = 0;     // Column position in the file
    int ligne = 1;       // Line number in the file

    while (1) {
        switch (etat) {
            case 0:
                car = carsuivant();
                if (isspace(car)) {  // Handle whitespace characters
                    if (car == '\n') {
                        ligne++;      // New line
                        colonne = 0;
                    } else if (car == '\t') {
                        colonne += 3;  // Tab character
                    } else {
                        colonne++;     // Space character
                    }
                } else if (isalpha(car)) {  // Handle alphabetic characters (start of identifiers or keywords)
                    z = 0;
                    ch[0] = car;
                    etat = 1;
                } else if (isdigit(car)) {  // Handle numeric characters
                    etat = 3;
                } else {
                    // Handle various special characters and operators
                    switch (car) {
                        case '<': etat = 5; break;
                        case '>': etat = 9; break;
                        case '=': etat = 12; break;
                        case '+': etat = 13; break;
                        case '-': etat = 14; break;
                        case '|': etat = 15; break;
                        case '*': etat = 18; break;
                        case '/': etat = 19; break;
                        case '%': etat = 20; break;
                        case '&': etat = 21; break;
                        case ':': etat = 23; break;
                        case ';': symbole.ul = pv; return symbole;
                        case '.': symbole.ul = pt; return symbole;
                        case ',': symbole.ul = v; return symbole;
                        case '(': symbole.ul = po; return symbole;
                        case ')': symbole.ul = pf; return symbole;
                        case '$': symbole.ul = 100; return symbole;
                        default:
                            printf("Caractère non reconnu: %c\n", car);
                            exit(1);
                    }
                }
                break;

            case 1:
                car = carsuivant();
                if (isalpha(car) || isdigit(car)) {
                    ch[++z] = car;  // Continue reading the identifier or keyword
                } else {
                    ch[z + 1] = '\0';  // Null-terminate the string
                    reculer(1);         // Move file pointer back by one position
                    symbole.ul = unilexid();  // Determine if it's a keyword or identifier
                    symbole.att = rangerid(symbole.ul, &c);  // Store the identifier if needed
                    return symbole;
                }
                break;

            case 3:
                if (isdigit(car = carsuivant())) {
                    ch[++z] = car;  // Continue reading the number
                } else {
                    ch[z + 1] = '\0';  // Null-terminate the number
                    reculer(1);         // Move file pointer back by one position
                    symbole.ul = nb;    // Set token type to number
                    symbole.att = atoi(ch);  // Convert string to integer
                    return symbole;
                }
                break;

            case 5:
                car = carsuivant();
                if (car == '=') {
                    symbole.ul = oprel;
                    symbole.att = ppe;  // "<=" operator
                    return symbole;
                } else if (car == '>') {
                    symbole.ul = oprel;
                    symbole.att = dif;  // "<>" operator
                    return symbole;
                } else {
                    reculer(1);  // Handle "<" operator
                    symbole.ul = oprel;
                    symbole.att = ppq;
                    return symbole;
                }
                break;

            case 9:
                car = carsuivant();
                if (car == '=') {
                    symbole.ul = oprel;
                    symbole.att = pge;  // ">=" operator
                    return symbole;
                } else {
                    reculer(1);  // Handle ">" operator
                    symbole.ul = oprel;
                    symbole.att = pgq;
                    return symbole;
                }
                break;

            case 12:
                symbole.ul = oprel;
                symbole.att = ega;  // "=" operator
                return symbole;

            case 13:
                symbole.ul = opadd;
                symbole.att = add;  // "+" operator
                return symbole;

            case 14:
                symbole.ul = opadd;
                symbole.att = sub;  // "-" operator
                return symbole;

            case 15:
                if ((car = carsuivant()) == '|') {
                    symbole.ul = opadd;
                    symbole.att = or;  // "||" operator
                    return symbole;
                } else {
                    reculer(1);
                    printf("Erreur : caractère inattendu |.\n");
                    exit(1);
                }
                break;

            case 18:
                symbole.ul = opmul;
                symbole.att = mul;  // "*" operator
                return symbole;

            case 19:
                symbole.ul = opmul;
                symbole.att = div;  // "/" operator
                return symbole;

            case 20:
                symbole.ul = opmul;
                symbole.att = mod;  // "%" operator
                return symbole;

            case 21:
                if ((car = carsuivant()) == '&') {
                    symbole.ul = opmul;
                    symbole.att = and;  // "&&" operator
                    return symbole;
                } else {
                    reculer(1);
                    printf("Erreur : caractère inattendu &.\n");
                    exit(1);
                }
                break;

            case 23:
                if ((car = carsuivant()) == '=') {
                    symbole.ul = aff;  // ":=" assignment operator
                    return symbole;
                } else {
                    reculer(1);
                    symbole.ul = dp;  // ":" symbol
                    return symbole;
                }
        }
    }
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure to store symbol information (name and type)
typedef struct {
    char name[20];  // Symbol name (e.g., variable name)
    int type;       // Symbol type (e.g., integer or character)
} SymbolType;

// Symbol table to store up to 100 symbols and a counter to track the number of symbols
SymbolType symbolTypeTable[100];
int symbolCount = 0;

// Function to find a symbol in the symbol table by name
int findSymbol(char *name) {
    for (int i = 0; i < symbolCount; i++) {
        if (strcmp(symbolTypeTable[i].name, name) == 0)
            return i;  // Return the index of the symbol if found
    }
    return -1;  // Return -1 if symbol is not found
}

// Function to add a symbol to the symbol table
void addSymbol(char *name, int type) {
    if (symbolCount < 100) {
        // If there is space in the symbol table, add the symbol
        strcpy(symbolTypeTable[symbolCount].name, name);
        symbolTypeTable[symbolCount].type = type;
        symbolCount++;
    } else {
        // If the table is full, print an error and terminate the program
        printf("Erreur : Table des symboles pleine.\n");
        exit(1);
    }
}

// Function to handle semantic errors and exit the program
void semanticError(const char *message) {
    printf("Erreur sémantique : %s\n", message);
    exit(1);  // Exit the program on semantic error
}

// Variable to hold the current data type (integer or char)
int currentDataType;

void dcl();
void inst_comp();
void d1();
unilex symbole_suivant();
void erreur(const char *message);
void accepter(int);
void p();
void l_id();
void l1();
void type();
void inst();
void l_inst();
void l_inst1();
void i();
void expression();
void exp_simple();
void exp1();
void terme();
void exp_simple1();
void terme1();
void facteur();

// Function to return the next symbol in the input (using analex function)
unilex symbole_suivant() {
    return analex();  // Return the next symbol from the lexical analyzer
}

// Function to handle errors and terminate the program
void erreur(const char *message) {
    printf("Erreur : %s\n", message);
    exit(1);  // Exit on error
}

// Function to accept a symbol if it matches the expected type
void accepter(int t) {
    if (symbole.ul == t) {
        symbole = symbole_suivant();  // Move to the next symbol if the current one matches
    } else {
        // Print error if the symbol does not match the expected type
        printf("Symbole attendu : %d, Symbole trouvé : %d\n", t, symbole.ul);
        erreur("Symbole non accepté !");
    }
}

// Function to emit output to a file
void emettre(char* ch) {
    if (file_output == NULL) {
        // If the file pointer is not initialized, print an error
        fprintf(stderr, "Erreur : fichier non initialisé.\n");
        return;
    }
    fprintf(file_output, "%s\n", ch);  // Write the string to the file
}

// Main function to start the syntax analysis
void p() {
    printf("Début de l'analyse syntaxique de p().\n");
    if (symbole.ul == program) {
        emettre(ch);
        accepter(program);
        accepter(id);
        accepter(pv);
        dcl();  // Handle declarations
        inst_comp();  // Handle compound instructions
        if (symbole.ul == pt)
            printf("Algorithme correct.\n");
        else
            erreur("Point final attendu.");  // Error if no final point is found
    } else {
        erreur("Mot-clé 'program' attendu.");  // Error if 'program' keyword is missing
    }
    printf("Fin de l'analyse syntaxique de p().\n");
}

// Declare an array for the current list of identifiers being processed
int idsCurrent[20];
int count = 0;

// Function to handle declarations in the program
void dcl() {
    printf("Début de l'analyse syntaxique de dcl().\n");
    emettre(ch);
    d1();  // Process the first part of the declaration
    printf("Fin de l'analyse syntaxique de dcl().\n");
}

// Recursive function to handle the declaration of multiple variables
void d1() {
    printf("Début de l'analyse syntaxique de d1().\n");
    emettre(ch);
    if (symbole.ul == var) {
        accepter(var);  // Accept the 'var' keyword
        l_id();  // Process the list of identifiers
        accepter(dp);  // Accept the ':' symbol
        type();  // Process the variable type (integer or char)
        accepter(pv);  // Accept the semicolon
        d1();  // Recursively process further declarations
    }
    printf("Fin de l'analyse syntaxique de d1().\n");
}

// Function to handle the list of identifiers in a declaration
void l_id() {
    printf("Début de l'analyse syntaxique de l_id().\n");
    emettre(ch);
    if (symbole.ul == id) {
        int index = findSymbol(tab_iden[symbole.att]);
        if (index != -1) {
            printf("Erreur : Identificateur %s déjà déclaré.\n", tab_iden[symbole.att]);
        } else {
            idsCurrent[count] = symbole.att;
            count++;
        }
        accepter(id);  // Accept the identifier
        l1();  // Process the next identifier or end of list
    } else {
        erreur("Identificateur attendu.");  // Error if identifier is expected but not found
    }
    printf("Fin de l'analyse syntaxique de l_id().\n");
}

// Function to handle the continuation of a list of identifiers
void l1() {
    printf("Début de l'analyse syntaxique de l1().\n");
    emettre(ch);
    if (symbole.ul == v) {
        accepter(v);  // Accept the ',' symbol for additional identifiers
        int index = findSymbol(tab_iden[symbole.att]);
        if (index != -1) {
            printf("Erreur : Identificateur %s déjà déclaré.\n", tab_iden[symbole.att]);
        } else {
            idsCurrent[count] = symbole.att;
            count++;
        }
        accepter(id);  // Accept the identifier
        l1();  // Recursively process additional identifiers
    }
    printf("Fin de l'analyse syntaxique de l1().\n");
}


// Function to handle the variable type (integer or char)
void type() {
    printf("Début de l'analyse syntaxique de type().\n");
    emettre(ch);
    int type;
    if (symbole.ul == integer) {
        type = integer;  // Set type to integer
        accepter(integer);  // Accept the 'integer' type keyword
    } else if (symbole.ul == chart) {
        type = chart;  // Set type to char
        accepter(chart);  // Accept the 'char' type keyword
    } else {
        erreur("Type attendu (integer ou chart).");  // Error if neither integer nor char
    }
    if (type == integer || type == chart) {
        // Add the variables to the symbol table with the selected type
        for (int i = 0; i < count; i++) {
            addSymbol(tab_iden[idsCurrent[i]], type);
        }
    } else {
        erreur("Type invalide.");  // Error for invalid type
    }
    printf("Fin de l'analyse syntaxique de type().\n");
}

// Function to handle a compound instruction (e.g., block of instructions enclosed in 'begin' and 'end')
void inst_comp() {
    printf("Début de l'analyse syntaxique de inst_comp().\n");
    emettre(ch);
    if (symbole.ul == begin) {
        accepter(begin);  // Accept the 'begin' keyword
        l_inst();  // Process the list of instructions
        accepter(end);  // Accept the 'end' keyword
    } else {
        erreur("Mot-clé 'begin' attendu.");  // Error if 'begin' is missing
    }
    printf("Fin de l'analyse syntaxique de inst_comp().\n");
}

// Function to handle the list of instructions in the program
void l_inst() {
    printf("Début de l'analyse syntaxique de l_inst().\n");
    emettre(ch);
    i();  // Process the first instruction
    l_inst1();  // Process further instructions if any
    printf("Fin de l'analyse syntaxique de l_inst().\n");
}

// Function to handle additional instructions in a list
void l_inst1() {
    printf("Début de l'analyse syntaxique de l_inst1().\n");
    emettre(ch);
    if (symbole.ul == pv) {
        accepter(pv);  // Accept the semicolon to separate instructions
        i();  // Process the next instruction
        l_inst1();  // Recursively process further instructions
    }
    printf("Fin de l'analyse syntaxique de l_inst1().\n");
}

// Function to check if the assignment is type-compatible
void checkAssignmentCompatibility(int idDataType, int expDataType) {
    if (idDataType != expDataType) {
        printf("Erreur : Incompatibilité de types lors de l'affectation\n");
        erreur("semantique");
        exit(1);  // Exit if the types are incompatible
    }
}
void i() {
    printf("Début de l'analyse syntaxique de i().\n");
    emettre(ch);  // Emit current symbol
    if (symbole.ul == id) {  // Check if the symbol is an identifier
        int idIndex = findSymbol(tab_iden[symbole.att]);  // Find the symbol in the symbol table
        if (idIndex == -1) {  // If the symbol is not declared
            printf("Erreur : Identificateur %s non déclaré.\n", tab_iden[symbole.att]);
        }
        accepter(id);  // Accept the identifier symbol
        accepter(aff);  // Accept the assignment operator
        exp_simple();  // Process the expression on the right-hand side of the assignment
        checkAssignmentCompatibility(symbolTypeTable[idIndex].type, currentDataType);  // Check type compatibility
    } else if (symbole.ul == iff) {  // Handle 'if' statement
        accepter(iff);  // Accept the 'if' keyword
        expression();  // Process the condition of the 'if' statement
        accepter(then);  // Accept the 'then' keyword
        i();  // Process the 'if' block
        accepter(elsee);  // Accept the 'else' keyword
        i();  // Process the 'else' block
    } else if (symbole.ul == whilee) {  // Handle 'while' loop
        accepter(whilee);  // Accept the 'while' keyword
        expression();  // Process the loop condition
        accepter(do);  // Accept the 'do' keyword
        i();  // Process the loop body
    } else if (symbole.ul == read) {  // Handle 'read' statement (input)
        accepter(read);  // Accept the 'read' keyword
        accepter(po);  // Accept the opening parenthesis
        if (symbole.ul == id) {  // Check if the identifier is valid
            int idIndex = findSymbol(tab_iden[symbole.att]);  // Find the symbol in the symbol table
            if (idIndex == -1) {
                printf("Erreur : Identificateur %s non déclaré.\n", tab_iden[symbole.att]);
            }
            accepter(id);  // Accept the identifier
        }
        accepter(pf);  // Accept the closing parenthesis
    } else if (symbole.ul == readln) {  // Handle 'readln' statement (input with newline)
        accepter(readln);  // Accept the 'readln' keyword
        accepter(po);  // Accept the opening parenthesis
        if (symbole.ul == id) {  // Check if the identifier is valid
            int idIndex = findSymbol(tab_iden[symbole.att]);  // Find the symbol in the symbol table
            if (idIndex == -1) {
                printf("Erreur : Identificateur %s non déclaré.\n", tab_iden[symbole.att]);
            }
            accepter(id);  // Accept the identifier
        }
        accepter(pf);  // Accept the closing parenthesis
    } else if (symbole.ul == write) {  // Handle 'write' statement (output)
        accepter(write);  // Accept the 'write' keyword
        accepter(po);  // Accept the opening parenthesis
        if (symbole.ul == id) {  // Check if the identifier is valid
            int idIndex = findSymbol(tab_iden[symbole.att]);  // Find the symbol in the symbol table
            if (idIndex == -1) {
                printf("Erreur : Identificateur %s non déclaré.\n", tab_iden[symbole.att]);
            }
            accepter(id);  // Accept the identifier
        }
        accepter(pf);  // Accept the closing parenthesis
    } else if (symbole.ul == writeln) {  // Handle 'writeln' statement (output with newline)
        accepter(writeln);  // Accept the 'writeln' keyword
        accepter(po);  // Accept the opening parenthesis
        if (symbole.ul == id) {  // Check if the identifier is valid
            int idIndex = findSymbol(tab_iden[symbole.att]);  // Find the symbol in the symbol table
            if (idIndex == -1) {
                printf("Erreur : Identificateur %s non déclaré.\n", tab_iden[symbole.att]);
            }
            accepter(id);  // Accept the identifier
        }
        accepter(pf);  // Accept the closing parenthesis
    } else {
        erreur("Instruction attendue.");  // If no valid instruction is found, report an error
    }
    printf("Fin de l'analyse syntaxique de i().\n");
}

void expression() {
    printf("Début de l'analyse syntaxique de expression().\n");
    emettre(ch);  // Emit current symbol
    exp_simple();  // Process the simple expression part
    exp1();  // Process any relational operator and the following expression part
    printf("Fin de l'analyse syntaxique de expression().\n");
}

void exp1() {
    printf("Début de l'analyse syntaxique de exp1().\n");
    emettre(ch);  // Emit current symbol
    if (symbole.ul == oprel) {  // If there is a relational operator, process it
        accepter(oprel);  // Accept the relational operator
        exp_simple();  // Process the simple expression after the relational operator
    }
    printf("Fin de l'analyse syntaxique de exp1().\n");
}

void exp_simple() {
    printf("Début de l'analyse syntaxique de exp_simple().\n");
    emettre(ch);  // Emit current symbol
    terme();  // Process the term (left-hand side of the expression)
    exp_simple1();  // Process additional parts of the simple expression (addition/subtraction)
    printf("Fin de l'analyse syntaxique de exp_simple().\n");
}

void exp_simple1() {
    printf("Début de l'analyse syntaxique de exp_simple1().\n");
    emettre(ch);  // Emit current symbol
    if (symbole.ul == opadd) {  // If there is an addition or subtraction operator
        accepter(opadd);  // Accept the addition or subtraction operator
        terme();  // Process the next term
        exp_simple1();  // Recursively process any further addition/subtraction
    }
    printf("Fin de l'analyse syntaxique de exp_simple1().\n");
}

void terme() {
    printf("Début de l'analyse syntaxique de terme().\n");
    emettre(ch);  // Emit current symbol
    facteur();  // Process the factor (left-hand side of the term)
    terme1();  // Process any additional multiplication/division
    printf("Fin de l'analyse syntaxique de terme().\n");
}

void terme1() {
    printf("Début de l'analyse syntaxique de terme1().\n");
    emettre(ch);  // Emit current symbol
    if (symbole.ul == opmul) {  // If there is a multiplication or division operator
        accepter(opmul);  // Accept the multiplication or division operator
        facteur();  // Process the next factor
        terme1();  // Recursively process further multiplication/division
    }
    printf("Fin de l'analyse syntaxique de terme1().\n");
}

void facteur() {
    printf("Début de l'analyse syntaxique");
    emettre(ch);  // Emit current symbol
    if (symbole.ul == id) {  // If the symbol is an identifier, process it
        int idIndex = findSymbol(tab_iden[symbole.att]);  // Find the identifier in the symbol table
        if (idIndex == -1) {  // If the identifier is not declared
            printf("Erreur : Identificateur %s non déclaré.\n", tab_iden[symbole.att]);
        }
        currentDataType = symbolTypeTable[idIndex].type;  // Set the current data type based on the symbol's type
        accepter(id);  // Accept the identifier
    } else if (symbole.ul == nb) {  // If the symbol is a number, process it
        currentDataType = integer;  // Set the data type to integer
        accepter(nb);  // Accept the number
    } else if (symbole.ul == po) {  // If the symbol is an opening parenthesis, process the enclosed expression
        accepter(po);  // Accept the opening parenthesis
        exp_simple();  // Process the expression inside the parentheses
        accepter(pf);  // Accept the closing parenthesis
    } else {
        erreur("Facteur attendu.");  // Report error if none of the expected symbols are found
    }
    printf("Fin de l'analyse syntaxique de facteur().\n");
}

int main() {



   printf("Debut de compilation de code  <---------------------------------->\n");
   file_output = fopen("C:\\Users\\Eagle\\OneDrive\\Desktop\\Today\\emet.txt", "w");   // Open output file to emit the code
   file_input = fopen("C:\\Users\\Eagle\\OneDrive\\Desktop\\Today\\teste.txt", "r");  // Open input file for the program to compile

    if (file_input == NULL) {  // Check if the file is opened successfully
        printf("Impossible d'ouvrir le fichier.\n");
        return 1;
    }

    symbole = symbole_suivant();  // Get the first symbol from the lexical analyzer
    p();  // Start
    fclose(file_input);
    fclose(file_output);
    return 0;
}
