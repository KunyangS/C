#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// Define important constant character pointers and variables at here :))
const char* TOKEN_IDENTIFIER = "IDENTIFIER";
const char* TOKEN_ARITHMETIC_OP = "ARITHMETIC_OP";
const char* TOKEN_OPEN_PAREN = "OPEN_PAREN";
const char* TOKEN_CLOSE_PAREN = "CLOSE_PAREN";
const char* TOKEN_REAL_CONSTANT = "REAL_CONSTANT";
const char* TOKEN_PRINT_STMT = "PRINT_STMT";
const char* TOKEN_LINE_END = "LINE_END";
const char* TOKEN_INDENTATION = "INDENTATION";
const char* TOKEN_COMMA_SEPARATOR = "COMMA_SEPARATOR";
const char* TOKEN_UNKNOWN = "UNKNOWN_TOKEN";
const char* TOKEN_FUNCTION_KEYWORD = "FUNCTION_KEYWORD";
const char* TOKEN_RETURN_STMT = "RETURN_STMT";
const char* TOKEN_ASSIGNMENT_OP = "ASSIGNMENT_OP";

#define MAX_LINE_LENGTH 1000
#define ASSIGN_OP "<-"
#define MAX_TOKEN_COUNT 256
int MAX_VARIABLES =  10;

// Create a Token structure to represent each token
typedef struct {
    char text[256];
    const char* type;
} Token;

// Functions work for analyzing source code, performing tokenization and parsing
Token extract_next_token(char **line);
char* skip_whitespace(char *line);
char* extract_word(char *line, char *word);
char* extract_number(char *line, char *number);
void strip_comment(char* line);
bool parse_factor(Token** token_list, FILE* write_file);
bool parse_term(Token** token_list, FILE* write_file);
bool parse_expression(Token** token_list, FILE* write_file);
bool parse_bracketed_expression(Token** token_list, FILE* write_file);
bool parse_statement(Token** token_list, FILE* write_file);
void process_line_content(char* line, FILE* read_file, FILE* write_file, bool inside_function);
bool parse_assignment(Token** token_list, FILE* write_file);
bool parse_function_call(Token** token_list, FILE* write_file);
void handle_error(const char *message);
bool parse_function_body(Token** token_list, FILE* read_file, FILE* write_file);
bool parse_function(Token** token_list, FILE* read_file, FILE* write_file);
bool parse_program_term(Token** token_list, FILE* read_file, FILE* write_file);
bool parse_program(Token** token_list, FILE* read_file, FILE* write_file);
bool is_assignment_operator(char **line, Token *token);
bool is_arithmetic_operator(char character, Token *token);
bool is_symbol(char character, Token *token);
bool is_identifier_or_keyword(char **line, Token *token);
bool is_real_constant(char **line, Token *token);

// Function works by handling errors
void handle_error_and_exit(const char *error_message) {
    fprintf(stderr, "!%s\n", error_message);// Print error message to stand error
    exit(EXIT_FAILURE);
}


bool contains_print(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        handle_error_and_exit("Error! No input file provided.");
        return false;
    }

    char line[1024];

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "print ") != NULL) {
            fclose(file);
            return true;
        }
    }

    fclose(file);
    return false;
}

/*
    Function works for open a file and managing errors if the file cannot be opened
    Parameters:
    - file_name: A constant string representing the name of the file to open
    - mode: A constant string representing the file opening mode (e.g., "r" for read, "w" for write)
    Return:
    - If successful, return the file pointer
    - If failed, return NULL
*/
FILE* open_file(const char* file_name, const char* mode) {
    FILE* file = fopen(file_name, mode);
    if (!file) {
        char error_message[256];// Buffer to hold the error message
        snprintf(error_message, sizeof(error_message), "Error: Could not open file '%s'.", file_name);// Format the error message
        handle_error_and_exit(error_message);// Print the error message and exit the program
    }
    return file;
}

// This function automates the compilation of a C file with the GCC compiler and executes the generated executable file
void compile_and_execute(const char* source_file, const char* executable) {
    char compile_command[256];
    snprintf(compile_command, sizeof(compile_command), "gcc -o %s %s", executable, source_file);
    //printf("%s",compile_command);
    if (system(compile_command) != 0) {
        handle_error_and_exit("Error: Compilation failed.");
    }

    char execute_command[256];
    snprintf(execute_command, sizeof(execute_command), "./%s", executable);
    system(execute_command);
}

void write_code_to_file(FILE* c_file) {
    const char *code =
            "#include <stdio.h>\n"
            "void print_number(double num) {\n"
            "    if (num == (int)num) {\n"
            "        printf(\"%.0f\\n\", num);\n"
            "    } else {\n"
            "        printf(\"%.6f\\n\", num);\n"
            "    }\n"
            "}\n";

    fputs(code, c_file);

}

// Function to check if file extension is .ml
void check_file_extension(const char* filename) {
    const char* dot = strrchr(filename, '.');
    if (!dot || strcmp(dot, ".ml") != 0) {
        char error_message[256];
        snprintf(error_message, sizeof(error_message), "!Error: Invalid file extension for file '%s'. "
                                                       "Expected a .ml file.", filename);
        handle_error_and_exit(error_message);
    }
}

//  Function to check if file is empty
void check_empty_file(const char* filename) {
    FILE* file =  open_file(filename, "r");
    // fseek function sets the file position of the stream to the given offset.
    fseek(file, 0, SEEK_END);
    if (ftell(file) == 0) {
        fclose(file);
        char error_message[256];
        snprintf(error_message, sizeof(error_message), "!Error: file input '%s' is empty.", filename);
        handle_error_and_exit(error_message);
    }
    fseek(file, 0, SEEK_SET);
    fclose(file);
}

/*
    This function translates input, compiles to C, runs, and cleans up
    Return:
    - if successful without errors, return EXIT_SUCCESS
    - if failed (like missing input file or compilation failure), the program terminates early via handle_error_and_exit()
*/
int main(int argc, char* argv[]) {
    // Check if only one file is provided
    if (argc != 2) {
        handle_error_and_exit("!Error, No input file provided.\n Usage: runml <inputfile>");
    }

    // Open the input and output files
    const char* input_file_name = argv[1];

    // check if file extension is .ml
    check_file_extension(input_file_name);

    // check if file is empty
    check_empty_file(input_file_name);

    bool has_print = contains_print(input_file_name);

    FILE* ml_file = open_file(input_file_name, "r");

    const char* temp_source_file = "temp_code.c";
    FILE* c_file = open_file(temp_source_file, "w");

    // if code have 'print' .then write print_number function into c file;
    if(has_print){
        write_code_to_file(c_file);
    }

    fprintf(c_file, "int main() {\n");

    // Process the input file line by line
    char current_line[MAX_LINE_LENGTH];
    while (fgets(current_line, sizeof(current_line), ml_file)) {
        process_line_content(current_line, ml_file, c_file, false);
    }

    // Close the main function in the output file
    fprintf(c_file, "return 0;\n}");

    // Close files
    fclose(ml_file);
    fclose(c_file);

    // Compile and execute the generated C code
    const char* temp_executable = "temp_exec";
    compile_and_execute(temp_source_file, temp_executable);

     //Clean up temporary files
    remove(temp_source_file);
    remove(temp_executable);

    return EXIT_SUCCESS;
}

/*
    This function breaks down the code into tokens and figures out what type each token is
    Parameter:
    - line: a double pointer to the current position in the line of code
*/
Token extract_next_token(char **line) {
    Token token;
    char *current_position = skip_whitespace(*line);  // Skip unnecessary whitespaces
    char current_char = *current_position;

    // Return a token indicating end of line when the line is reached
    if (*current_position == '\0') {
        strcpy(token.text, "");
        token.type = TOKEN_LINE_END;
        return token;
    } else if (*current_position == '\t') {// Check if the current character is a tab
        strcpy(token.text, "\t");
        token.type = TOKEN_INDENTATION;
        *line = current_position + 1;// Move to next character
    } else if (is_assignment_operator(&current_position, &token)) {// Verify if the current position contains an assignment operator
        *line = current_position;
    } else if (is_arithmetic_operator(current_char, &token) || is_symbol(current_char, &token)) {// Make sure if the current character is an arithmetic operator or symbol
        *line = current_position + 1;
    } else if (is_identifier_or_keyword(&current_position, &token)) {//If the current position represents an identifier or keyword
        *line = current_position;
    } else if (is_real_constant(&current_position, &token)) {//If the current position represents a real constant
        *line = current_position;
    } else {// If no token type matches
        token.type = TOKEN_UNKNOWN;
        token.text[0] = current_char;
        token.text[1] = '\0';
        *line = current_position + 1;
    }

    return token;
}

/*
    Helper function to check for assignment operator
    Return:
    - The function returns `true` if the assignment operator `"<-"` is found.
    - It returns `false` if the operator is not found at the current position.
*/
bool is_assignment_operator(char **line, Token *token) {
    char *current_position = *line;
    if (current_position[0] == '<' && current_position[1] == '-') {
        strcpy(token->text, ASSIGN_OP);
        token->type = TOKEN_ASSIGNMENT_OP;
        *line = current_position + 2;
        return true;
    }
    return false;
}

/*
    Function works to check if the given character is an arithmetic operator
    Parameters:
    - character: it represents a potential arithmetic operator
    - token: pointer to a Token structure that will hold the operator's type and text information
    Return:
    - if it returns 'true', which means the character is a valid arithmetic operator
*/

bool is_arithmetic_operator(char character, Token *token) {
    switch (character) {
        // Check if the character matches any of the arithmetic operators
        case '+':
        case '-':
        case '*':
        case '/':
            token->type = TOKEN_ARITHMETIC_OP;
            token->text[0] = character;
            token->text[1] = '\0';
            return true;
        default:
            return false;
    }
}

/*
    checks if a character is a recognized symbol like parentheses or commas in expressions
    Parameters:
    - character: check if character matches one of the recognized symbols
    - token: if a symbol is found, the token's text and type will be stored
*/
bool is_symbol(char character, Token *token) {
    switch (character) {
        case '(':
            token->type = TOKEN_OPEN_PAREN;
            token->text[0] = '(';
            token->text[1] = '\0';
            return true;
        case ')':
            token->type = TOKEN_CLOSE_PAREN;
            token->text[0] = ')';
            token->text[1] = '\0';
            return true;
        case ',':
            token->type = TOKEN_COMMA_SEPARATOR;
            token->text[0] = ',';
            token->text[1] = '\0';
            return true;
        default:
            return false;
    }
}

/*
    Helper function to check for identifier or keyword
    Parameters:
    - line: it help function to update the caller's line pointer
    - token: if an identifier or keyword is found, the token's text and type will be stored
    Return:
    - if successful, which means the token has been successfully identified and processed
*/
bool is_identifier_or_keyword(char **line, Token *token) {
    char word[256];  // Buffer for the extracted word
    *line = extract_word(*line, word);  // Extract the word from the line

    if (strlen(word) > 0) {
        strcpy(token->text, word);

        // Check for keywords
        if (strcmp(word, "print") == 0) {
            token->type = TOKEN_PRINT_STMT;
        } else if (strcmp(word, "function") == 0) {
            token->type = TOKEN_FUNCTION_KEYWORD;
        } else if (strcmp(word, "return") == 0) {
            token->type = TOKEN_RETURN_STMT;
        } else {
            token->type = TOKEN_IDENTIFIER;
        }

        return true;
    }

    return false;
}

/*
    Check if the line contains a real constant
    Parameters:
    - line: it help function to update the caller's line pointer
    - token: if a real constant is found, the token's text and type will be stored
    Return:
    - if successful, which means the token has been successfully identified and processed
*/
bool is_real_constant(char **line, Token *token) {
    char number[256];  // Buffer for the extracted number
    *line = extract_number(*line, number);  // Extract the number from the line

    if (strlen(number) > 0) {
        strcpy(token->text, number);
        token->type = TOKEN_REAL_CONSTANT;
        return true;
    }

    return false;
}

/*
    Function works to skip whitespaces and return the new line pointer
    Parameter:
    - line: the function processes the line and moves the pointer forward until non-whitespace character is encountered
    Return:
    - returns pointer after skipping leading spaces, newlines, or returns, pointing to the first meaningful character
*/
char* skip_whitespace(char *line) {
    while (*line == ' ' || *line == '\n' || *line == '\r') {
        line++;
    }
    return line;
}

/*
    Defined extract_number function to extract a numeric value from a line of code
    Parameters:
    - line: pointer to the code's current position 
    - number: pointer to a buffer that will store the extracted number as a string
*/
char* extract_number(char *line, char *number) {
    char *start = line;
    char *number_ptr = number;

    // Extract digits and periods (for decimal numbers)
    while (isdigit((unsigned char)*start) || *start == '.') {
        *number_ptr = *start;
        number_ptr++;
        start++;
    }

    // Null-terminate the number
    *number_ptr = '\0';

    return start;  // Return the updated line pointer
}

/*
    Designed extract_word function to extract a word from the line
    Parameters:
    - line: pointer to the code's current position and function extracts a word starting from here
    - word: pointer to a buffer that will store the extracted word as a string
*/
char* extract_word(char *line, char *word) {
    char *start = line;
    char *word_ptr = word;

    // Extract characters that form a valid word (letters only)
    while (islower((unsigned char)*start)) {
        *word_ptr = *start;
        word_ptr++;
        start++;
    }

    // Null-terminate the word
    *word_ptr = '\0';

    return start;  // Return the updated line pointer
}

// Function works by distinguishing errors
void handle_error(const char *message) {
    fprintf(stderr, "!%s\n", message);  // Output the error message to stderr
}

// Function works to remove comments from a line of code by truncating it, keeping only the executable portion
void strip_comment(char* line) {
    // Iterate through the characters of the line
    for (int i = 0; line[i] != '\0'; i++) {
        // If a comment symbol '#' is found, terminate the string at that position
        if (line[i] == '#') {
            line[i] = '\0';  // Replace '#' with the null terminator
            break;  // Exit the loop once comment symbol is found
        }
    }
}

/*
    Function works by removing comments, tokenizes the line, parses it , validates syntax, and also handles errors with unknown tokens
    Parameters:
    - line: pointer to the line of code that needs to be processed
    - read_file: pointer to the file that is being read
    - write_file: pointer the the file where the processed output is written
    - inside_function: it is a boolean flag, if the line is insided a function body, the function body is processed
*/
void process_line_content(char* line, FILE* read_file, FILE* write_file, bool inside_function) {
    strip_comment(line);  // Remove comments from the line

    if (strlen(line) > 0) {
        Token tokens[MAX_TOKEN_COUNT];  // Token array
        int token_idx = 0;
        char *line_ptr = line;

        // Tokenize the line
        while (token_idx < MAX_TOKEN_COUNT) {
            Token token = extract_next_token(&line_ptr);

            if (strcmp(token.type, TOKEN_UNKNOWN) == 0) {
                handle_error("Error: Unknown token encountered.");
                //exit(EXIT_FAILURE);
            }

            tokens[token_idx++] = token;

            if (strcmp(token.type, TOKEN_LINE_END) == 0) {
                break;  // Stop processing if the token is line end
            }
        }

        Token* token_ptr = tokens;  // Pointer to tokens array

        // Process function body if inside a function
        if (inside_function) {
            parse_function_body(&token_ptr, read_file, write_file);
        } else {
            if (!parse_program(&token_ptr, read_file, write_file)) {
                handle_error("Syntax Error: Invalid program syntax.");
            }
        }
    }
}

/*
    Function parses a function body by verifying indentation, parsing each statement, and ensuring correct syntax, handling errors if parsing fails.
    Parameters:
    - token_list: pointer to the current list of tokens
    - read_file: pointer to the input file
    - write_file: pointer to the file where the processed output is written
    Return:
    - if returned true, which means all statements within the function body are parsed successfully
*/
bool parse_function_body(Token** token_list, FILE* read_file, FILE* write_file) {
    if (strcmp((*token_list)->type, TOKEN_INDENTATION) == 0) {
        (*token_list)++;
        while (strcmp((*token_list)->type, TOKEN_LINE_END) != 0) {
            if (!parse_statement(token_list, write_file)) {
                handle_error("SyntaxError-Failed to Parse Statement!");
                return false;
            }
        }
    }
    return true;
}

/*
    Function works by parsing the entire program by processing the token list
    Parameters:
    - token_list: pointer to the current list of tokens
    - read_file: pointer to the input file
    - write_file: pointer to the file where the processed output is written
    Return:
    - if returned true, which means the program is successfully parsed without any error
*/
bool parse_program(Token** token_list, FILE* read_file, FILE* write_file) {
    // Loop until we reach the end of the tokens (TOKEN_LINE_END)
    while ((*token_list)->type != TOKEN_LINE_END) {

        // Attempt to parse the current token as a program term (statement, function, etc.)
        bool success = parse_program_term(token_list, read_file, write_file);
        if (!success) {
            // If parsing fails, handle the error and return false to indicate failure
            handle_error("SyntaxError: Failed to Parse Program!");
            return false;
        }

        // Move to the next token in the token list
        //token_list++;
    }

    // Successfully parsed the program
    return true;
}

/*
    Function works by parsing a program item, which could be either a function definition or a statement
    Parameters:
    - token_list: pointer to the current list of tokens
    - read_file: pointer to the input file
    - write_file: pointer to the file where the processed output is written
    Return:
    - if it turned 'true', which means the token list is successfully parsed as a valid statement or function
*/
bool parse_program_term(Token** token_list, FILE* read_file, FILE* write_file) {

    // If not a function, try to parse it as a statement
    bool is_statement = parse_statement(token_list, write_file);
    if (is_statement) {
        return true;  // Successfully parsed a statement
    }

    // First, try to parse the token list as a function definition
    bool is_function = parse_function(token_list, read_file, write_file);
    if (is_function) {
        return true;  // Successfully parsed a function
    }

    // If neither a function nor a statement, it's a syntax error
    handle_error("SyntaxError: Failed to Parse Program Item!");
    return false;  // Parsing failed
}

/*
    Function works by parsing a function definition
    Parameters:
    - token_list: pointer to the current list of tokens
    - read_file: pointer to the input file
    - write_file: pointer to the file where the processed output is written
    Return:
    - if it returned 'true', which means the function definition is successfully parsed and written to the output file
*/
bool parse_function(Token** token_list, FILE* read_file, FILE* write_file) {
    int no_statements = 0;
    char body_lines[256];
    int no_parameters = 0;
    char parameters[MAX_VARIABLES][256];

    if (strcmp((*token_list)->type, TOKEN_FUNCTION_KEYWORD) != 0) {
        return false;
    }
    (*token_list)++;

    // Parse function name
    if (strcmp((*token_list)->type, TOKEN_IDENTIFIER) != 0) {
        handle_error("SyntaxError-Expected function name!");
        return false;
    } else {
        fprintf(write_file, "double %s ", (*token_list)->text);
        (*token_list)++;
    }

    fprintf(write_file, "(");

    // Parse parameters (zero or more)
    while (strcmp((*token_list)->type, TOKEN_IDENTIFIER) == 0) {
        strncpy(parameters[no_parameters], (*token_list)->text, sizeof(parameters[no_parameters]) - 1);
        parameters[no_parameters][sizeof(parameters[no_parameters]) - 1] = '\0'; // Null byte at end
        no_parameters++;
        (*token_list)++;
    }

    // Output the function parameters
    for (int i = 0; i < no_parameters; i++) {
        if (i != 0) {
            fprintf(write_file, ", ");
        }
        fprintf(write_file, "double %s", parameters[i]);
    }

    fprintf(write_file, ") {\n");

    // Parse the function body (handling indentation)
    while (fgets(body_lines, sizeof(body_lines), read_file) && body_lines[0] == '\t') {
        process_line_content(body_lines, read_file, write_file, true);
        no_statements++;
    }

    fprintf(write_file, "}\n");

    if (no_statements > 0) {
        return true;
    } else {
        handle_error("SyntaxError-Expected function body!");
        return false;
    }
}

/*
    Function works by checking if the current token is a print statement
    Paramesters:
    - token_list: pointer to the current list of tokens
    - write_file: pointer to the file where the processed output is written
    Return:
    - if it returned 'true', which means a print statement is successfully parsed and written to the output file
*/
bool is_print_statement(Token** token_list, FILE* write_file) {
    if (strcmp((*token_list)->text, "print") == 0) {
        // Handle print statement
        //fprintf(write_file, "printf(\"%%.6f\\n\", ");

        // print_number
        fprintf(write_file, "print_number(");

        (*token_list)++;  // Move to the next token

        // Parse the expression following the print statement
        if (parse_expression(token_list, write_file)) {
            fprintf(write_file, ");\n");
            return true;
        } else {
            handle_error("!SyntaxError: Expression expected after 'print'");
            return false;
        }
    }

    return false;  // Not a print statement
}

/*
    Function works by checking and parsing return statement
    Parameters:
    - token_list: pointer to the current list of tokens
    - write_file: pointer to the file where the processed output is written
    Return:
    - if it returned 'true', which means statement is successfully parsed and written to the output file
*/
bool is_return_statement(Token** token_list, FILE* write_file) {
    if (strcmp((*token_list)->text, "return") == 0) {
        // Handle return statement
        fprintf(write_file, "return ");
        (*token_list)++;  // Move to the next token

        // Parse the expression following the return statement
        if (parse_expression(token_list, write_file)) {
            fprintf(write_file, ";\n");
            return true;
        } else {
            handle_error("!SyntaxError: Expression expected after 'return'");
            return false;
        }
    }

    return false;  // Not a return statement
}

/*
    Function works to parse a statement from the token list
    Parameters:
    - token_list: pointer to the current list of tokens
    - write_file: pointer to the file where the processed output is written
    Return:
    - if it returned 'true', which means statement is successfully parsed and written to the output file
*/
bool parse_statement(Token** token_list, FILE* write_file) {
    // Check if it's a print statement
    if (is_print_statement(token_list, write_file)) {
        return true;
    }

    // Check if it's a return statement
    if (is_return_statement(token_list, write_file)) {
        return true;
    }

    // Check if it's an assignment statement
    if (parse_assignment(token_list, write_file)) {
        fprintf(write_file, ";\n");
        return true;
    }

    // Check if it's a function call
    if (parse_function_call(token_list, write_file)) {
        fprintf(write_file, ";\n");
        return true;
    }
    //printf("%s",(*token_list)->text);
    //printf("%s",(*token_list)->type);

    // If none of the above, report a syntax error
    //handle_error("SyntaxError: Failed to parse statement");
    return false;
}

/*
    Function works by cheching is the current token is '('
    Parameters:
    - token_list: pointer to the current list of tokens
    - write_file: pointer to the file where the processed output is written
    Return:
    - it returned 'true', when '(' is found and processed successfully
*/
bool check_open_parenthesis(Token** token_list) {
    if (strcmp((*token_list)->type, TOKEN_OPEN_PAREN) == 0) {
        (*token_list)++;  // Move to the next token after '('
        return true;
    }
    return false;
}

/*
    Function works by checking if a token is a valid function identifier, ensuring correct syntax
    Parameters:
    - token_list: pointer to the current list of tokens
    - write_file: pointer to the file where the processed output is written
    Return:
    - it returned 'true', if the token list represents a valid function identifier
*/
bool is_valid_function_identifier(Token** token_list, FILE* write_file) {
    if (strcmp((*token_list)->type, TOKEN_IDENTIFIER) == 0) {
        char * fuction_name = (*token_list)->text;
        (*token_list)++;
        if(check_open_parenthesis( token_list)){
            fprintf(write_file, "%s(", fuction_name);  // Print the function name
            //(*token_list)++;  // Move to the next token
            return true;
        }
        (*token_list)--;
    }
    return false;
}

/*
    Function parses and validates function call arguments, reporting errors if invalid
    Parameters:
    - token_list: pointer to the current list of tokens
    - write_file: pointer to the file where the processed output is written
    Return:
    - if returned 'true', which means all function arguments are parsed and written successfully
*/
bool parse_function_arguments(Token** token_list, FILE* write_file) {
    // First argument must be an expression
    if (!parse_expression(token_list, write_file)) {
        handle_error("!InvalidFunctionCall - Expected expression after '('");
        return false;
    }

    // Handle multiple arguments separated by commas
    while (strcmp((*token_list)->type, TOKEN_COMMA_SEPARATOR) == 0) {
        fprintf(write_file, ", ");
        (*token_list)++;  // Move to the next token

        // Parse the next argument expression
        if (!parse_expression(token_list, write_file)) {
            handle_error("!InvalidFunctionCall - Expected expression after ','");
            return false;
        }
    }

    return true;  // All arguments parsed successfully
}

/*
    Function checks if the current token is `)`
    Parameters:
    - token_list: pointer to the current list of tokens
    - write_file: pointer to the file where the processed output is written
    Return:
    - it returns 'true', when ')' is found and processed successfully.
*/
bool check_close_parenthesis(Token** token_list, FILE* write_file) {
    if (strcmp((*token_list)->type, TOKEN_CLOSE_PAREN) == 0) {
        fprintf(write_file, ")");  // Print closing parenthesis for the function call
        (*token_list)++;  // Move to the next token after ')'
        return true;
    } else {
        //handle_error("InvalidFunctionCall - Expected ')'");
        return false;
    }
}

/*
    Function works by parsing a function call from the token list
    Parameters:
    - token_list: pointer to the current list of tokens
    - write_file: pointer to the file where the processed output is written
    Return:
    - it returns 'true', when the function call is successfully parsed and written to the output file
*/
bool parse_function_call(Token** token_list, FILE* write_file) {
    // Check if the token is a valid function identifier
    if (!is_valid_function_identifier(token_list, write_file)) {
        return false;  // Not a function call
    }

    // if it is ')', which means no parameter, end the program
    bool is_close_parenthesis = check_close_parenthesis(token_list, write_file);
    if (is_close_parenthesis) {
        return true;
    }

    // if it is not ')', which means parameter exsits, need to parse parameter
    if (!parse_function_arguments(token_list, write_file)) {
        return false;
    }

    // Check if the token is a close parenthesis ')'
    if (!check_close_parenthesis(token_list, write_file)) {
        handle_error("!InvalidFunctionCall - Expected ')'");
        return false;
    }

    return true;  // Successfully parsed the function call
}

/*
    Function parses a mathematical expression from the token list
    Parameters:
    - token_list: pointer to the current list of tokens
    - write_file: pointer to the file where the processed output is written
    Return:
    - if it returns 'true', which means the expression is successfully parsed and written to the output file
*/
bool parse_expression(Token** token_list, FILE* write_file) {
    // Parse the first term in the expression
    bool has_valid_term = parse_term(token_list, write_file);
    if (!has_valid_term) {
        handle_error("!InvalidExpression - Expression must start with a valid term.");
        return false;
    }

    // Check if the next token is an arithmetic operator
    bool is_arithmetic_op = strcmp((*token_list)->type, TOKEN_ARITHMETIC_OP) == 0;

    // Continue parsing while there are arithmetic operators
    while (is_arithmetic_op) {
        // Print the arithmetic operator (e.g., +, -, *, /)
        fprintf(write_file, " %s ", (*token_list)->text);
        printf("%s",(*token_list)->text);
        // Move to the next token after the operator
        (*token_list)++;

        // Parse the next term after the operator
        has_valid_term = parse_term(token_list, write_file);
        if (!has_valid_term) {
            handle_error("!InvalidExpression - Expected a valid term after the arithmetic operator.");
            return false;
        }

        // Update the condition for the next iteration
        is_arithmetic_op = strcmp((*token_list)->type, TOKEN_ARITHMETIC_OP) == 0;
    }

    return true;  // Successfully parsed the expression
}

/*
    Function works by parsing a **term** in a mathematical expression from the token list
    Parameters:
    - token_list: pointer to the current list of tokens
    - write_file: pointer to the file where the processed output is written
    Return:
    - if returned 'true', which means successfully parsed the term
*/
bool parse_term(Token** token_list, FILE* write_file) {
    // First, parse the initial factor
    bool has_valid_factor = parse_factor(token_list, write_file);
    if (!has_valid_factor) {
        handle_error("!InvalidExpression - Term must have a valid factor");
        return false;
    }

    // Check if the current token is an arithmetic operator
    bool is_arithmetic_op = strcmp((*token_list)->type, TOKEN_ARITHMETIC_OP) == 0;

    // While the current token is an arithmetic operator, keep parsing the next factors
    while (is_arithmetic_op) {
        // Print the arithmetic operator (e.g., +, -, *, /)
        fprintf(write_file, " %s ", (*token_list)->text);

        // Move to the next token
        (*token_list)++;

        // Parse the next factor after the operator
        has_valid_factor = parse_factor(token_list, write_file);
        if (!has_valid_factor) {
            handle_error("!InvalidExpression - Term must have a valid factor");
            return false;
        }

        // Update the condition for the next iteration
        is_arithmetic_op = strcmp((*token_list)->type, TOKEN_ARITHMETIC_OP) == 0;
    }

    return true;  // Successfully parsed the term
}

/*
    Function works to parse a factor (constant, identifier, function call, or expression in parentheses)
    Parameters:
    - token_list: pointer to the current list of tokens
    - write_file: pointer to the file where the processed output is written
*/
bool parse_factor(Token** token_list, FILE* write_file) {

    // Check if the factor is a function call
    bool is_function_call = parse_function_call(token_list, write_file);
    if (is_function_call) {
        return true;
    }

    // Check if the factor is a bracketed expression
    bool is_bracketed_expression = parse_bracketed_expression(token_list, write_file);
    if (is_bracketed_expression) {
        return true;
    }

    // Check if the factor is a real constant
    bool is_real_constant = strcmp((*token_list)->type, TOKEN_REAL_CONSTANT) == 0;

    // Check if the factor is an identifier
    bool is_identifier = strcmp((*token_list)->type, TOKEN_IDENTIFIER) == 0;

    // If the factor is either a real constant or an identifier, print and consume the token
    if (is_real_constant || is_identifier) {
        fprintf(write_file, "%s", (*token_list)->text);
        (*token_list)++;  // Move to the next token
        return true;
    }

    return false;
}

/*
    Function works to parse an expression enclosed in parentheses from the token list
    Parameters:
    - token_list: pointer to the current list of tokens
    - write_file: pointer to the file where the processed output is written
    Return:
    - if returned 'true', which means the bracketed expression is successfully parsed and written to the output file
*/
bool parse_bracketed_expression(Token** token_list, FILE* write_file) {
    // Check if the current token is an open parenthesis '('
    bool is_open_parenthesis = strcmp((*token_list)->type, TOKEN_OPEN_PAREN) == 0;
    if (!is_open_parenthesis) {
        return false;  // If not an open parenthesis, it's not a bracketed expression
    }

    (*token_list)++;

    // Parse the expression inside the parentheses
    bool has_valid_expression = parse_expression(token_list, write_file);
    if (!has_valid_expression) {
        handle_error("!InvalidBracketedExpression - Expression expected");
        return false;
    }

    // Check if the current token is a closing parenthesis ')'
    bool is_close_parenthesis = strcmp((*token_list)->type, TOKEN_CLOSE_PAREN) == 0;
    if (!is_close_parenthesis) {
        handle_error("!InvalidBracketedExpression - Expected ')'");
        return false;
    }

    (*token_list)++;
    return true;  // Successfully parsed a bracketed expression
}

/*
    Function works to parse an assignment statement from the token list
    Parameters:
    - token_list: pointer to the current list of tokens
    - write_file: pointer to the file where the processed output is written
    Return:
    - if returned 'true', which means the assignment statement is successfully parsed
*/
bool parse_assignment(Token** token_list, FILE* write_file) {
    // Check if the token is an identifier (variable name)
    bool is_identifier = strcmp((*token_list)->type, TOKEN_IDENTIFIER) == 0;
    if (!is_identifier) {
        return false;  // Not an assignment if there is no identifier
    }

    // Store the variable name
    char variable[256];
    strcpy(variable, (*token_list)->text);
    (*token_list)++;  // Move to the next token

    // Check if the next token is an assignment operator '<-'
    bool is_assignment_operator = strcmp((*token_list)->type, TOKEN_ASSIGNMENT_OP) == 0;
    if (!is_assignment_operator) {
        (*token_list)--;  // Rollback if it's not an assignment operator
        return false;
    }

    (*token_list)++;  // Move to the next token after assignment operator

    // Print the variable and prepare for expression
    fprintf(write_file, "double %s = ", variable);

    // Parse the expression following the assignment operator
    bool has_valid_expression = parse_expression(token_list, write_file);
    if (!has_valid_expression) {
        handle_error("!InvalidAssignment - Expected expression after assignment operator");
        return false;
    }

    // Successfully parsed the assignment statement
    return true;
}