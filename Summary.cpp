#include "Summary.h"

void Summary::CountSingleCommentLines(std::string text) {
    if (text.find("//") != std::string::npos && isMultiCommentLine == false) {
        CommentLineCount++;
    }
}

void Summary::CountBlankLines(std::string text) {

    if (text.empty() && isMultiCommentLine == false) {
        BlankLineCount++;
    }
}

void Summary::CountMultiCommentLines(std::string text) {
    if (text.find("/*") != std::string::npos && isMultiCommentLine == false) {
        CommentLineCount++;
        isMultiCommentLine = true;
    }
    
    if (isMultiCommentLine == true && text.find("*/") != std::string::npos) {
        CommentLineCount++;
        isMultiCommentLine = false;
    }

    if (isMultiCommentLine == true && text.find("*/") == std::string::npos) {
        CommentLineCount++;
    }
    

    

}

void Summary::CountCodeLines(std::string text) {
    std::string FirstTwoSym = text.substr(0, 2);
    if (FirstTwoSym.find("//") == std::string::npos && FirstTwoSym.find("/*") == std::string::npos && !isMultiCommentLine && !text.empty()) {
        CodeLineCount++;
    }
}

Summary& Summary::MakeSummary(std::string filepath) {
    
    std::ifstream fin;
    
    char buffer[200];

    fin.open(filepath);
    if (!fin.is_open()) {
        std::cout << "File opening error" << std::endl;
        
        
        return *this;
        
    }
    else {
//        std::cout << "\nFile "<<filepath<<" is opened" << std::endl;
        FileCount++;
        while (fin.getline(buffer, 200)) {
            std::string strbuffer(buffer);
            
            CountSingleCommentLines(strbuffer);
            CountBlankLines(strbuffer);
            CountCodeLines(strbuffer);
            CountMultiCommentLines(strbuffer);
        }
        this->isMultiCommentLine = false;
//        std::cout << *this;
        fin.close();
        
        return *this;
        
    }
}

std::ostream& operator<<(std::ostream& out, Summary& obj) {
    out << "\nThere was -> " << obj.FileCount << " files scanned";
    out << "\nThere are -> " << obj.CodeLineCount << " lines with code";
    out << "\nThere are -> " << obj.CommentLineCount << " lines with comments";
    out << "\nThere are -> " << obj.BlankLineCount << " blank lines\n";
    return out;
}

Summary& Summary::operator+=(Summary& obj) {
    this->BlankLineCount += obj.BlankLineCount;
    this->CodeLineCount += obj.CodeLineCount;
    this->CommentLineCount += obj.CommentLineCount;
    this->FileCount += obj.FileCount;
    this->isMultiCommentLine = false;
    return *this;
}