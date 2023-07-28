#include <iostream>
#include <iomanip>
#include <fstream>
#include <ostream>
#include <istream>
#include <vector>

#include "raylib.h"
#include "src/test.h"
#include "WindowResizer.h"

template <typename T>
void PrintVector(std::vector<T> vector)
{
    for(size_t i = 0; i < vector.size(); i++)
    {
        std::cout << vector[i] << std::endl;
    }
}
template <typename T>
void PrintVector(std::vector<T> vector, size_t element_skip)
{
    for(size_t i = 0; i < vector.size(); i++)
    {
        if(i%element_skip == 0)
            std::cout << vector[i] << std::endl;
    }
}

void GetDoubleVecFromStringVec(const std::vector<std::string> &vec_str, std::vector<double> &vec_d)
{
    vec_d.clear();
    vec_d.reserve(vec_str.size());
    for(size_t i = 0; i < vec_str.size(); i++)
    {
        vec_d.push_back(std::stod(vec_str[i]));
    }
    vec_d.shrink_to_fit();
}

template <typename T>
T FindMax(std::vector<T> vec)
{
    if(vec.empty()) return 0;
    T max = vec[0];
    for(size_t i = 0; i < vec.size() - 1; i++)
    {
        if(max < vec[i]) max = vec[i]; 
    }
    return max;
}
template <typename T>
T FindMin(std::vector<T> vec)
{
    if(vec.empty()) return 0;
    T min = vec[0];
    for(size_t i = 0; i < vec.size() - 1; i++)
    {
        if(min > vec[i]) min = vec[i]; 
    }
    return min;
}

void PrintVector2Param(const Vector2 &vec)
{
    std::cout << std::setprecision(3) << "x: " << vec.x << " y: " << vec.y << std::endl;
}
void PrintRectangleParam(const Rectangle &rec)
{
    std::cout << std::setprecision(3) << "x: " << rec.x << " y: " << rec.y << std::endl;
    std::cout << std::setprecision(3) << "width: " << rec.width << " height: " << rec.height << std::endl;
}

void EraseChar(std::string &str, char letter)
{
    for(size_t i = 0; i < str.length(); i++)
    {
        if(str.at(i) == letter)
            str.erase(i, 1);
    }
}
std::string ExtractWord(std::string line, size_t pos, char separator)
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
void ReplaceChar(std::string &str, char erased, char inserted)
{
    for(size_t i = 0; i < str.length(); i++)
    {
        if(str.at(i) == erased)
            str[i] = inserted;
    }
}
bool FileCheckOpen(std::string fileName)
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
std::string FileGetString(std::string fileName, size_t col, size_t row, char separator)
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
size_t FileCountLines(std::string fileName)
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
void FileGetRowAsVector()
{

}
void FileWriteFromVector(const std::vector<std::string> &vector, std::string input_file_name)
{
    std::ofstream file{input_file_name, std::ios::trunc};
    for(size_t i = 0; i < vector.size(); i++)
    {
        file << vector[i] << std::endl;
    } 
    file.close();
}
// TODO add overloads for full file and start-end_line and start_line-end of document
bool FileGetColumnAsVector(std::string fileName, std::vector<std::string> &vector, size_t col,  size_t start_line, size_t end_line, char col_separator)
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
std::string FileGetLine(std::string fileName, size_t row_pos)
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


int Tester()
{
    /*
    size_t col = 3;
    size_t row = 10000000;
    std::string word = FileGetString(col,row,' ',"EURUSD_PERIOD_H1_pricedata_edit.txt");
    std::cout << "tadaaaa the word in col: " << col << " and row: " << row <<  " is: " << word << std::endl;
    */
    /*
    std::cout << "opening / creating file" << std::endl;
    std::string outFileName = "EURUSD_PERIOD_H1_pricedata.csv";
    std::string inFileName = "EURUSD_PERIOD_H1_pricedata_edit.txt";

    std::ofstream writeFile{inFileName, writeFile.trunc};
    std::ifstream readFile {outFileName, readFile.in};
    std::cout << "starting to read the file " << outFileName << std::endl;
    size_t lineCount = 0;

    while(true)
    {
        std::string line;
        if (!std::getline(readFile, line))
        {
            std::cout << "end of file reached" << std::endl;
            break;
        }
        lineCount++;
        ReplaceChar(line, ';', ' ');
        writeFile << line << std::endl;
    }
    readFile.close();
    writeFile.close();
*/

/*
    for(size_t i = 0; i < buffer.size(); i++)
    {
        if(buffer.size() < amount)
        {
            std::cout << "buffer too small, whats going on?" << std::endl;
            break;
        }
        std::cout << buffer[i] << std::endl;
    }
*/
    //std::cout << "Finish, " << lineCount << " lines were inserted in new document named: " << outFileName << std::endl;

    /*
    for(size_t i = 1; i < 101; i++)
    {
        std::string value = FileGetString(2, i, ' ', "EURUSD_PERIOD_H1_pricedata_edit.txt");
        std::cout << i << " line: " << value << std::endl;
    }
    */
   int windowWidth = 800;
   int windowHeight = 600;
   Color windowColor = {BLACK};

    InitWindow(windowWidth, windowHeight,"test");  // Initialize window and OpenGL context
    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(windowColor);
        EndDrawing();
    }                               // Check if KEY_ESCAPE pressed or Close icon pressed
    CloseWindow();



    return 0;
}