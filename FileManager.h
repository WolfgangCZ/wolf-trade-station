#ifndef FILE_MANAGER_HPP
#define FILE_MANAGER_HPP

#include <iostream>
#include <iomanip>
#include <fstream>
#include <ostream>
#include <istream>
#include <vector>

#include "raylib.h"

class FileManager
{
    private:

    public:
        bool FileCheckOpen(std::string fileName);
        bool FileGetColumnAsVector(std::string fileName, std::vector<std::string> &vector, size_t col,  size_t start_line, size_t end_line, char col_separator);
        void ReplaceChar(std::string &str, char erased, char inserted);
        size_t FileCountLines(std::string fileName);
        void FileWriteFromVector(const std::vector<std::string> &vector, std::string input_file_name);
        std::string ExtractWord(std::string line, size_t pos, char separator);
        std::string FileGetString(std::string fileName, size_t col, size_t row, char separator);
        std::string FileGetLine(std::string fileName, size_t row_pos);

        //NOT IMPLEMENTED YET
        void FileGetRowAsVector();
};





#endif //FILE_MANAGER_HPP