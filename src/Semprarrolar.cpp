#include <stdio>
#include <fstream>
#include <string>

int main (){

    std::ifstream fileInputStream;
    std::ofstream fileOutputStream;

    std::vector<Line> lines; //lines is empty
    std::string lineString;

    fileInputStream.open("../linhas.txt"); //for linux
    //fileInputStream.open("..//linhas.txt"); //for Windows

    if (!fileInputStream.isopen()){
        std::cerr << "Input file opening failed.\n";
        exit(1);
    }

    Line line;
    while (getline(fileInputStream, lineString)!= EOF){
        line.readLine(lineString);
        lines.push_back (line);
    }

    fileInputStream.close()

    return 0;
}
