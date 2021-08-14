#include <iostream>
#include <fstream>
#include <vector>
struct Data{
    int FileCount=0;
    int BlankLineCount=0;
    int CodeLineCount=0;
    int CommentLineCount=0;
    bool isMultiCommentLine= false;
} ;

void CountSingleCommentLines(struct Data &obj,std::string text);

void CountSingleCommentLines(struct Data &obj,std::string text){
        if(text.find("//")!=std::string::npos &&obj.isMultiCommentLine==false){
            obj.CommentLineCount++;
        }

}
void CountBlankLines(struct Data &obj,std::string text);

void CountBlankLines(struct Data &obj,std::string text){

    if(text.empty()&&obj.isMultiCommentLine==false){
        obj.BlankLineCount++;
    }
}
void CountMultiCommentLines(struct Data &obj,std::string text);

void CountMultiCommentLines(struct Data &obj,std::string text){
    if(obj.isMultiCommentLine==true && text.find("*/")==std::string::npos){
        obj.CommentLineCount++;
    }
    if(obj.isMultiCommentLine==true && text.find("*/")!=std::string::npos){
        obj.CommentLineCount++;
        obj.isMultiCommentLine=false;
    }

    if(text.find("/*")!=std::string::npos && obj.isMultiCommentLine==false){
        obj.CommentLineCount++;
        obj.isMultiCommentLine=true;
    }

}
void CountCodeLines(struct Data &obj,std::string text);

void CountCodeLines(struct Data &obj,std::string text){
    std::string FirstTwoSym=text.substr(0,2);
    if (FirstTwoSym.find("//")==std::string::npos && FirstTwoSym.find("/*")==std::string::npos &&  !obj.isMultiCommentLine && !text.empty()){
        obj.CodeLineCount++;
    }
}

std::ostream &operator<<(std::ostream &out,struct Data &obj){
    out<<"\nThere are -> "<<obj.CodeLineCount<<" lines with code";
    out<<"\nThere are -> "<<obj.CommentLineCount<<" lines with comments";
    out<<"\nThere are -> "<<obj.BlankLineCount<<" blank lines\n";
}

int main() {
    std::string path="C:\\Users\\Artem\\CLionProjects\\SoftServe\\Task3\\code.txt";
    std::ifstream fin;
    char buffer[50];
    struct Data summary;


    fin.open(path);
    if (!fin.is_open()){
        std::cout<<"File opening error"<<std::endl;
    }
    else{
        std::cout << "File is opened" << std::endl;
        while (fin.getline(buffer,50)){
            std::string strbuffer(buffer);
            std::cout<<std::endl<<strbuffer<<std::endl;
            CountSingleCommentLines(summary,strbuffer);
            CountBlankLines(summary,strbuffer);
            CountCodeLines(summary,strbuffer);
            CountMultiCommentLines(summary,strbuffer);
            std::cout<<summary;
        }
    }


    fin.close();
    return 0;
}
