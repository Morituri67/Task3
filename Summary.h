#pragma once

#include <iostream>
#include <fstream>
#include <mutex>


class Summary {
public:
    Summary() :FileCount(0), BlankLineCount(0), CodeLineCount(0), CommentLineCount(0), isMultiCommentLine(false)
    {};

    void CountSingleCommentLines(std::string text);
    void CountMultiCommentLines(std::string text);
    void CountCodeLines(std::string text);
    void CountBlankLines(std::string text);
    Summary& MakeSummary(std::string filepath);

    Summary& operator+=(Summary& obj);
    friend std::ostream& operator<<(std::ostream& out, Summary& obj);


private:
    int FileCount;
    int BlankLineCount;
    int CodeLineCount;
    int CommentLineCount;
    bool isMultiCommentLine;

    std::mutex mtx;
};


