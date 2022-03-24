# include <iostream>
# include <fstream>
# include <string>
# include <unordered_map>
# include <sstream>
using namespace std ;
// Used unordered map to count the lexemes.
unordered_map < string , int > ReservedWord ;
unordered_map < string , int > UserDefinedWords ;
unordered_map < string , int > Operators ;
void SyntaxAnalyzer ( ifstream &File  ) {
    int linenumber = 0 ;
    string line ;
    string word ;
    // get the line than tokenize it.
    while ( ! File . eof ( ) ) {
        int paracount = 0 ;
        int barcount = 0 ;
        int semicount = 0 ;
        int opcount = 0 ;
        int andorcount = 0 ;
        getline ( File , line ) ;
        linenumber ++ ;
        stringstream iss ( line ) ;
        iss >> word ; //checks if the first word is if or not
            if ( word == "if" ) { //than checks the later ones
                while ( iss >> word ) {
                    if ( word == "(" )
                        paracount ++ ;
                    if ( word == ")" )
                        paracount -= 1 ;
                    if ( word == "[" )
                        barcount++;
                    if ( word == "]" )
                        barcount -= 1;
                    if ( word == ";" )
                        semicount ++  ;
                    if ( word == "<" || word == ">" || word == "<<" || word == ">>" || word == ">=" || word == "<=" || word == "==" )
                        opcount ++ ;
                    if ( word == "&&" || word == "||" )
                        andorcount ++ ;
                }
                if ( paracount != 0 || barcount != 0 || semicount != 0 ) {
                    cout << "Error at linenumber= " << linenumber << endl;
                }
                else if ( opcount > 1 ) {
                    if ( andorcount == 0 ) 
                        cout << "Error at linenumber= " << linenumber << endl;
                }
            }
            if ( word == "for" ) {
                while ( iss >> word ) {
                    if ( word == "(" )
                        paracount ++ ;
                    if ( word == ")" )
                        paracount -= 1 ;
                    if ( word == "[" )
                        barcount ++ ;
                    if ( word == "]" )
                        barcount -= 1;
                    if ( word == ";" )
                        semicount ++ ;
                    if ( word == "<" || word == ">" || word == "<<" || word == ">>" || word == ">=" || word == "<=" || word == "==" )
                        opcount ++ ;
                    if ( word == "&&" || word == "||" )
                        andorcount ++ ;
                }
                if ( paracount != 0 || barcount != 0 || semicount != 2 ) {
                    cout << "Error at linenumber= " << linenumber << endl ;
                }
                else if (opcount > 1) {
                    if (andorcount == 0)
                        cout << "Error at linenumber= " << linenumber << endl;
                }
            }
            if ( word == "while" ) {
                while ( iss >> word ) {
                    if ( word == "(" )
                        paracount ++ ;
                    if ( word == ")" )
                        paracount -= 1;
                    if ( word == "[" )
                        barcount++;
                    if ( word == "]" )
                        barcount -= 1;
                    if ( word == ";" )
                        semicount ++ ;
                    if ( word == "<" || word == ">" || word == "<<" || word == ">>" || word == ">=" || word == "<=" || word == "==" )
                        opcount ++ ;
                    if ( word == "&&" || word == "||" )
                        andorcount ++ ;
                }
                if ( paracount != 0 || barcount != 0 || semicount != 0 ) {
                    cout << "Error at linenumber= " << linenumber << endl ;
                }
                else if ( opcount > 1 ) {
                    if ( andorcount == 0 )
                        cout << "Error at linenumber= " << linenumber << endl ;
                }
            }
    }
}

int main ( ) {
    ifstream File , File2 ;
    string FilePATH ;
    string word ; // the words we are going to take from the file.
    cout << " Enter the Path of the file: " ;
    cin >> FilePATH ;
    // Taking the file path entered by the user
    /* To count how many times we encontered the stuff. */
    int loadedmodules = 0 ;
    int array = 0 ;
    int Operator = 0 ;
    int reserved = 0 ;
    int others = 0  ;
    int total = 0 ;
    int variable = 0 ;
    int numerical = 0 ;
    int array2 = 0 ;
    /**************************************************/
    string operators [14] = { "+" , "-" , "<" , ">" , "=" , "<<" , ">>" , ">=" , "<=" , "&&" , "||" , "==" , "/" , "*" } ; //  operators.
    string numer = "0123456789" ; // Numericals
    string other = " , ; \ ( ) { } [ ] ' ' : . " ; // Other Operators.
    string ReservedVariables [82] = // Reserved Table
    { "auto" , "break" , "case" , "char" , "const" , "continue" , "default" ,
        "do" , "double" , "else" , "enum" , "extern" , "float" , "for" , "goto" ,
        "if" , "int" , "long" , "register" , "return" , "short" , "signed" ,
        "sizeof" , "static" , "struct" , "switch" , "typedef" , "union" ,
        "unsigned" , "void" , "volatile" , "while" , "empty" , "size" ,
        "max_size" , "count" , "at" , "find" , "contains" ,
        "get_allocator" , "begin" , "cbegin" , "end" , "cend" ,
        "insert" , "clear" , "emplace" , "emplace_hint" , "try_emplace" ,
        "erase" , "swap" , "extract" , "merge" , "reserve" , "rehash" , "key_eq" , "cout" , "cin"
        "erase_if" , "private" , "throw" , "typeid" , "operator" , "first" , "second" ,
        "typename" , "virtual" , "template" , "namespace" , "public" , "gcount" , "rdbuf" ,
        "getloc" , "getline" , "read" , "ignore" , "using" , "open" , "c_str" , "include" , "endl" , "length" , "substr" } ;
    File . open ( FilePATH . c_str ( ) ) ; // Opens the entered path.
    while ( File >> word ) { // Takes word by word from the file.

        /*****Passes the comment lines*****/
        if ( word == " // " ) {
            while ( word != " \n " ) {
                File >> word ;
            }
        }
        else if ( word == " /* " ) {
            while ( word != " */ " )
                File >> word ;
        }
        /*********************************/
        if ( word == "include" ) {
            loadedmodules ++ ; // Counts the librarys
        }
        // when finds the previous found user defined words incremants it.
        for ( auto counter : UserDefinedWords ) {
            if ( counter . first == word )
                UserDefinedWords [ word ] ++ ; // adds the word to the map and increases it's integer value
        }
        /************************************************************/
        /*********************Checks arrays and variables******************************/
        if ( word == "int" || word == "double" || word == "float" || word == "auto" ) { // when any of these are found.
            ReservedWord [ word ] ++ ; // puts them to reserved word map because they are from reserved table.
            total ++ ;
            reserved ++ ;
            File >> word ; // passes to next word.
            if ( word [ 0 ] == '>' ) {
                Operators [ word ] ++ ;
                File >> word;
            }
            if ( word [ word . length ( ) - 1 ] == ']' ) {
                int i ;
                string extracted ;
                for ( i = 0 ; i  < word . length ( ) && word . length ( ) >= 3 ; i ++ ) {
                    if ( word [ i ] == '[' )
                        Operators ["["] ++ ; // when [ is found we copy the chars before [ found to the map.
                    UserDefinedWords [ extracted ] ++;
                        break ;
                }
                extracted = word . substr ( 0 , i ) ;
                array ++ ; // since array is found increase array.
                UserDefinedWords [ extracted ] ++; // adds the word to the map and increases it's integer value
                File >> word ; // next word.
            }
            else {
                UserDefinedWords [ word ] ++ ; // when not an array still a user defined variable.
                variable ++ ; // increases counter.
            }
        }
        // Same with above.
        if ( word == "char" ) {
            ReservedWord [ word ] ++ ;
            total ++ ;
            reserved ++ ;
            File >> word ;
            if ( word[0] == '>' )
                File >> word ;
            if ( word [ word . length ( ) - 1 ] == ']' ) {
                int i ;
                string extracted ;
                for ( i = 0 ; i < word . length ( ) ; i ++ ) {
                    if ( word [ i ] == '[' )
                        break ;
                }
                extracted = word . substr ( 0 , i ) ;
                array ++ ;
                UserDefinedWords [ extracted ] ++ ; // when [ is found we copy the chars before [ found to the map.
                File >> word ;
            }
            else {
                UserDefinedWords [ word ] ++ ;   // when not an array still a user defined variable.
                variable ++ ;
            }
        }
        // Same with above.
        if ( word == "string" ) {
            ReservedWord [ word ] ++ ; // adds the word to the map and increases it's integer value
            reserved ++ ;
            total ++ ;
            File >> word ;
            if ( word [ 0 ] == '>' )
                File >> word ;
            if ( word [ word . length ( ) - 1 ] == ']' ) {
                int i ;
                string extracted ;
                for ( i = 0 ; i < word . length ( ) ; i ++ ) {
                    if ( word [ i ] == '[' )
                        break ;
                }
                extracted = word . substr ( 0 , i ) ;
                array ++ ;
                UserDefinedWords [ extracted ] ++ ; // when [ is found we copy the chars before [ found to the map.
                File >> word ;
            }
            else {
                UserDefinedWords [ word ] ++ ; // when not an array still a user defined variable.
                variable ++ ; // increases counter.
            }
        }
        /*************************************************************************/
        /****************Checks words from the reserved table********************/
        for ( int i = 0 ; i < 82 ; i ++ ) {
            if ( ReservedVariables [ i ] == word ) {
                reserved ++ ;
                ReservedWord [ word ] ++ ; // adds the word to the map and increases it's integer value
                total ++ ;
                break ;
            }
        }
        /*********** Counts the Operators in other string ***********/
        if ( word . length ( ) == 1 ) { // Checks the word size is 1
            for ( int i = 0 ; i < other . length ( ) ; i ++ ) {
                if ( word == ")" || word == "]" || word == "}" ) { // We don't take closes.
                    break ;
                }
                else if ( other [ i ] == word [ 0 ] ) {
                    others ++ ;
                    Operators [ word ] ++ ; // adds the word to the map and increases it's integer value
                    if ( word == "[" ) // [ is  opened for arrays so It equals the time of arrays used.
                        array2++;
                    total ++ ; // increase total of lexemes.
                    break ;
                }
            }
        }
        /**********Counts the Operators in operators string************/
        for ( int i = 0 ; i < 14 ; i ++ ) {
            if ( word == operators [ i ] ) { // when member of operator found
                Operator ++ ; // incereases the operator int
                Operators [ word ] ++ ; // adds the word to the map and increases it's integer value
                total ++ ; // increase total of lexemes.
            }
        }
        /***************************************************************/
        /*****************Counts numericals****************************/
        for ( int i = 0 ; i < 10 ; i ++ ) {
            if ( word [ 0 ] == numer [ i ] ) {
                numerical ++ ;
                total ++ ;
            }
        }
        /*************************************************************/
    }
    //Prints the counters.
    cout << endl << " loaded modules = " << loadedmodules << endl << " variable = " << variable << endl << " Declared arrays = " << array << endl << " Times arrays used = " << array2 << endl
        << " Operator = " << Operator << endl << " reserved = " << reserved << endl << " others = " << others << endl << " numerical = " << numerical << endl ;
    cout << " Reserved Words : " << endl ;
    for ( auto counter : ReservedWord ) // In a loop iterates and prints the members of the map.
        cout << " ' " << counter . first << " ' = " << counter . second << endl ; // Prints the values. First one is the word second one is counter.
    cout << " User Defined Words : " << endl;
    for ( auto counter : UserDefinedWords )
        cout << " ' " << counter . first << " ' = " << counter . second << endl ; // Prints the values. First one is the word second one is counter.
    cout << " Operator Words : " << endl;
    for ( auto counter : Operators )
        cout << " ' " << counter . first << " ' = " << counter . second << endl ; // Prints the values. First one is the word second one is counter.
    // Total lexemes.
    cout << endl << " Total : " << total << endl ;
    
//    syntax analysis
    
    // Closes the file.
    File . close ( ) ;
    File . open ( FilePATH . c_str ( ) ) ; // Opens the entered path.
    SyntaxAnalyzer ( File ) ;
    File . close ( ) ;

    return 0 ;
}