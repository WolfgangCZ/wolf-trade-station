#include "FileManager.hpp"

void FileManager::ReplaceChar(std::string &str, char erased, char inserted)
{
    for(size_t i = 0; i < str.length(); i++)
    {
        if(str.at(i) == erased)
            str[i] = inserted;
    }
}
std::string FileManager::ExtractWord(std::string line, size_t pos, char separator)
{
    std::string searched_word = "";
    searched_word.reserve(100);
    size_t word_count = 1;

    for(size_t i = 0; i < line.size(); i++)
    {
        if(word_count == pos)
        {
            if(line[i] == separator)
            {
                break;
            }
            searched_word.push_back(line[i]);
        }
        else if(line[i] == separator)
            word_count++;

        if(word_count > pos)
            break;

        if(searched_word.empty() && i == (line.size() - 1))
        {
            std::cout << "seems like there is only " << word_count <<  " words, try again using less collumns" << std::endl;
            break;
        }
    }
    searched_word.shrink_to_fit();
    return searched_word;
}

bool FileManager::FileCheckOpen(std::string fileName)
{
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cout << "Failed to open the file: " << fileName << std::endl;
        return false;
    }
    else
    {
        file.close();
        return true;
    } 
}
//First column = 1, first line = 1
//this is too slow DONT USE ON BIG FILES or in combination with other functions
std::string FileManager::FileGetString(std::string fileName, size_t col, size_t row, char separator)
{
    if(!FileCheckOpen(fileName)) return "";
    std::ifstream readFile{fileName};
    //td::cout << "opening file: " << fileName << " reading line " << row << " column " << col << std::endl;
    size_t lineNumber = 1;
    std::string line;

    while(true)
    {
        if (!std::getline(readFile, line))
        {
            std::cout << "end of file reached, seems like this document " << fileName << " does have only " << lineNumber << " lines" << std::endl;
            readFile.close();
            return "";
        }
        if(lineNumber == row)
        {
            break;
        }
        lineNumber++;
    }
    std::string searched_string = ExtractWord(line, col, separator);
    readFile.close();
    return searched_string;
}
size_t FileManager::FileCountLines(std::string fileName)
{
    if(!FileCheckOpen(fileName)) return 0;
    std::ifstream readFile{fileName};
    //std::cout << "opening file: " << fileName << " reading line " << row << " column " << col << std::endl;
    size_t lineNumber = 0;
    std::string line;

    while(true)
    {
        if (!std::getline(readFile, line))
        {
            std::cout << "end of file reached, seems like this document does have " << lineNumber << std::endl;
            readFile.close();
            return lineNumber;
        }
        lineNumber++;
    }
    return 0;
}
void FileManager::FileGetRowAsVector()
{

}
void FileManager::FileWriteFromVector(const std::vector<std::string> &vector, std::string input_file_name)
{
    std::ofstream file{input_file_name, std::ios::trunc};
    for(size_t i = 0; i < vector.size(); i++)
    {
        file << vector[i] << std::endl;
    } 
    file.close();
}
// TODO add overloads for full file and start-end_line and start_line-end of document
bool FileManager::FileGetColumnAsVector(std::string fileName, std::vector<std::string> &vector, size_t col,  size_t start_line, size_t end_line, char col_separator)
{
    if(!FileCheckOpen(fileName)) return false;
    vector.clear();
    size_t lines_count = FileCountLines(fileName);
    vector.reserve(lines_count);
    std::ifstream readFile{fileName};
    std::string line;
    
    if(start_line > lines_count)
    {
        std::cout << "Error, desired line is out of scope of this document. File: " << fileName << std::endl;
        return false;
    }
    if(lines_count < end_line)
    {
        end_line = lines_count;
    }
    std::cout << "filling up vector" << std::endl;
    for(size_t i = 1; i < lines_count + 1; i++)
    {
        std::getline(readFile, line);
        if(i >= start_line && i <= end_line)
        {
            vector.push_back(line);
        }
    }    
    vector.shrink_to_fit();
    std::cout << "vector filled, vector has " << vector.size() << " lines" << std::endl;
    std::cout << "now slicing lines in vector " << std::endl;
    
    for(size_t i = 0; i < vector.size(); i++)
    {
        vector[i] = ExtractWord(vector[i], col, col_separator);
    }
    return true;
}
std::string FileManager::FileGetLine(std::string fileName, size_t row_pos)
{
    if(!FileCheckOpen(fileName)) return "";
    std::ifstream readFile{fileName};
    //td::cout << "opening file: " << fileName << " reading line " << row << " column " << col << std::endl;
    size_t lineNumber = 1;
    std::string line;

    while(true)
    {
        if (!std::getline(readFile, line))
        {
            std::cout << "end of file reached, seems like this document does have only " << lineNumber << " lines" << std::endl;
            readFile.close();
        }
        if(lineNumber == row_pos)
        {
            readFile.close();
            return line;
        }
        lineNumber++;
    }
    readFile.close();
    return "";
}