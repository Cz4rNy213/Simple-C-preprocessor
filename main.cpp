#include <iostream>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <stdexcept>
#include <string>


class Preprocessor {
    public:
        Preprocessor(): define_token_map(), result(), text_strings(), text_stream(){} //initializing with default empty values

        void readFile(const char*);
        void processTokens();
    private:
        bool handleInclude(std::string&, std::string&);
        bool handleDefine(const std::string&, std::string&, int&);
        int convertStringToInt(std::string& value_string);
        bool validDefName(std::string);
        void writeResultToFile(const std::ostringstream& text);

        std::unordered_map<std::string, int> define_token_map;
        std::ostringstream result;
        std::string text_strings;
        std::ostringstream text_stream;
};

void Preprocessor::readFile(const char* file_name){
    std::ifstream file(file_name);
    if (!file){
        throw std::runtime_error("Can not open file in readFile function");
    }
    text_stream << file.rdbuf();
    text_strings = text_stream.str(); //reading file and saving it as string
}

void Preprocessor::processTokens(){
    std::istringstream text(text_strings); //text to iterate through
    bool include_line = true; //include line or not, necessary for #JeśliZdefiniowane #JeśliNie #Zakończ
    bool include_else = false; //as above
    std::string line;
    while (getline(text, line)){ //iterating through each line
            std::istringstream line_stream(line);
            std::string token;
        while(line_stream >> token){ //iterating through each string in line
            if (token == "#inkluduj"){
            std::string header_file;
            line_stream >> header_file;
            if(!handleInclude(token, header_file)){ //check if header file for #inkluduj is correct
                std::cerr << "Error in handling #inkluduj. Exiting...\n";
                std::exit(EXIT_FAILURE);
            }
            result << token + ' '; 
            result << header_file + ' '; 
        }
        else if (token == "#definiuj"){
            std::string def_name;
            std::string value_string;
            int value;
            line_stream >> def_name; //get name for #definiuj
            line_stream >> value_string; //get value
            if(!handleDefine(def_name, value_string, value)){ //check if name and value for #definiuj is correct
                std::cerr << "Error in handling #definiuj. Exiting...\n";
                std::exit(EXIT_FAILURE);
            }
            define_token_map[def_name] = value; //adding name and value to map so i can then change definied names with their values
        }
        else if (token == "#JeśliZdefiniowane"){ //#ifdef
            std::string def_name;
            line_stream >> def_name;
            auto it = define_token_map.find(def_name);
            if (!(it != define_token_map.end())){ //check if name was defined
                include_line = false;
                include_else = true;
            }
        }
        else if (token == "#JeśliNie"){ //#else
            include_line = include_else;
            include_else = false;
        }
        else if (token == "#Zakończ"){ //#endif
            include_line = true;
            include_else = false;
        }
        else{
            if (include_line){
                auto it = define_token_map.find(token); 
                if (it != define_token_map.end()){ //if token in map then change it with corresponding value
                    result << it->second << ' ';
                }
                else{
                    result << token + ' ';
                }
            }
        }
        } 
        if (include_line){
            result << "\n"; //endline after reading each line
        }
    }
    writeResultToFile(result);
}

bool Preprocessor::handleInclude(std::string& token, std::string& header_file){
    if (header_file[0] != '<' && header_file[header_file.size()] - 1 != '>'){ //check if #inkluduj header file contains "< ... >"
        throw std::runtime_error("Incorrect header file: " + header_file);
        return false;
    }
    else if (header_file.size() <= 2){ //if header file contains only "<>" then return error
        throw std::runtime_error("Incorrect header file: " + header_file);
        return false;
    }
    token = "#include"; //change token name to #include so result file can include libraries correctly
    return true;
}

bool Preprocessor::handleDefine(const std::string& def_name, std::string& value_string, int& value){
    if (!validDefName(def_name)){
        throw std::runtime_error("Incorrect #definiuj name: " + def_name);
        return false;
    }
    value = convertStringToInt(value_string);
    return true;
}

int Preprocessor::convertStringToInt(std::string& value_string){ //converting string value from #zdefiniuj to int so i can add it to map
    try {
        return std::stoi(value_string);
    }
    catch (const std::invalid_argument&){
        throw std::invalid_argument("Error: invalid argument. #definiuj value is not int!" + value_string);
        std::exit(EXIT_FAILURE);
    }
    catch (const std::out_of_range&){
        throw std::out_of_range("Error: out of range. #definiuj value is out of range of int");
        std::exit(EXIT_FAILURE);
    }
}

bool Preprocessor::validDefName(std::string def_name){
    for (int i = 0; i < def_name.size(); i++){
        if (!((def_name[i] >= 'A' && def_name[i] <= 'Z') || def_name[i] == '_')){ // check if #zdefiniuj name contains only upper case letters or "_"
            return false;
        }
    }
    return true;
}

void Preprocessor::writeResultToFile(const std::ostringstream& result){ 
    std::ofstream outfile("result.cpp"); //you can type any name you want, just remember to add .cpp at the end, programm will create file for you
    outfile << result.str();
}

int main(){
    Preprocessor preprocessor;
    preprocessor.readFile("input.cpp"); //type here input file you want to compile
    preprocessor.processTokens();
    return 0;
}