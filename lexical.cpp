#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <set>
using namespace std;

// Symbol Table
set<string> symbolTable;
// chnage in system
// hello
// not

// Keyword check
int isKeyword(const string& word) 
{
    string keywords[] = 
    {
        "auto","break","case","char","const","continue","default","do",
        "double","else","enum","extern","float","for","goto","if",
        "int","long","register","return","short","signed","sizeof","static",
        "struct","switch","typedef","union","unsigned","void","volatile","while"
    };

    for (string key : keywords)
        if (word == key) 
            return 1;

    return 0;
}


int main() 
{
    string filename;
    cout << "Enter source file name: ";
    cin >> filename;

    ifstream file(filename);
    if (!file) {
        cout << "Error: Unable to open file!" << endl;
        return 1;
    }

    char ch;
    string word;

    cout << "\n====== LEXICAL ANALYZER OUTPUT ======\n\n";

    while (file.get(ch)) 
    {

        if (isspace(ch))
            continue;

        if (ch == '#') 
        {
            word = ch;
            while (file.get(ch) && ch != '\n')
                word += ch;

            if (word.find("#include") == 0)
                cout << "#include : Preprocessor Directive (Include)\n";
            else if (word.find("#define") == 0)
                cout << "#define : Preprocessor Directive (Macro Definition)\n";
            else if (word.find("#undef") == 0)
                cout << "#undef : Preprocessor Directive (Macro Undefinition)\n";
            else if (word.find("#ifdef") == 0)
                cout << "#ifdef : Preprocessor Directive (If Defined)\n";
            else if (word.find("#ifndef") == 0)
                cout << "#ifndef : Preprocessor Directive (If Not Defined)\n";
            else if (word.find("#if") == 0)
                cout << "#if : Preprocessor Directive (Conditional Compilation)\n";
            else if (word.find("#elif") == 0)
                cout << "#elif : Preprocessor Directive (Else If)\n";
            else if (word.find("#else") == 0)
                cout << "#else : Preprocessor Directive (Else)\n";
            else if (word.find("#endif") == 0)
                cout << "#endif : Preprocessor Directive (End If)\n";
            else if (word.find("#pragma") == 0)
                cout << "#pragma : Preprocessor Directive (Pragma)\n";
            else if (word.find("#line") == 0)
                cout << "#line : Preprocessor Directive (Line Control)\n";
            else if (word.find("#error") == 0)
                cout << "#error : Preprocessor Directive (Error)\n";
            else
                cout << word << " : Preprocessor Directive\n";
        }
    // String Literal
        else if (ch == '"') 
        {
            word = ch;
            while (file.get(ch) && ch != '"')
                word += ch;

            word += '"';  // closing quote
            cout << word << " : String Literal\n";
        }


        // Keyword or Identifier
        else if (isalpha(ch) || ch == '_') 
        {
            word = ch;
            while (isalnum(file.peek()) || file.peek() == '_')
                word += file.get();

            if (isKeyword(word))
                cout << word << " : Keyword\n";
            else {
                cout << word << " : Identifier\n";
                symbolTable.insert(word);
            }
        }

        else if (isdigit(ch)) 
        {
            word = ch;
            bool isFloat = false;
            while (isdigit(file.peek()) || file.peek() == '.') 
            {
                if (file.peek() == '.') isFloat = true;
                word += file.get();
            }
            if (isFloat)
                cout << word << " : Floating Constant\n";
            else
                cout << word << " : Integer Constant\n";
        }

        else if (ch == '/') 
        {
            if (file.peek() == '/') 
            {
                while (file.get(ch) && ch != '\n');
                cout << "// : Single Line Comment\n";
            }
            else if (file.peek() == '*') 
            {
                file.get(ch);
                while (file.get(ch)) {
                    if (ch == '*' && file.peek() == '/') 
                    {
                        file.get(ch);
                        break;
                    }
                }
                cout << "/* */ : Multi Line Comment\n";
            }
            else 
            {
                cout << "/ : Arithmetic Operator (Division)\n";
            }
        }

        else if (ch == '+')
            cout << "+ : Arithmetic Operator (Addition)\n";
        else if (ch == '-')
            cout << "- : Arithmetic Operator (Subtraction)\n";
        else if (ch == '*')
            cout << "* : Arithmetic Operator (Multiplication)\n";
        else if (ch == '=')
            cout << "= : Assignment Operator\n";
        else if (ch == '<')
            cout << "< : Relational Operator (Less Than)\n";
        else if (ch == '>')
            cout << "> : Relational Operator (Greater Than)\n";

        // Brackets / Separators
        else if (ch == '(')
            cout << "( : Opening Parenthesis\n";
        else if (ch == ')')
            cout << ") : Closing Parenthesis\n";
        else if (ch == '{')
            cout << "{ : Opening Curly Brace\n";
        else if (ch == '}')
            cout << "} : Closing Curly Brace\n";
        else if (ch == '[')
            cout << "[ : Opening Square Bracket\n";
        else if (ch == ']')
            cout << "] : Closing Square Bracket\n";
        else if (ch == ';')
            cout << "; : Semicolon (Statement Terminator)\n";
        else if (ch == ',')
            cout << ", : Comma (Separator)\n";

        // Invalid Symbol
        else 
        {
            cout << ch << " : Invalid Symbol\n";
        }
    }

    file.close();

    // Symbol Table
    cout << "\n====== SYMBOL TABLE ======\n";
    for (auto id : symbolTable)
        cout << id << endl;

    return 0;
}
