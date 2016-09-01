#include <iostream>
#include <fstream>
#include <string>
#include "content.h"

using namespace Wt;


Content::Content():WText(){

}

Content::Content(const char *fileName, WContainerWidget *parent):WText("",parent){
    class fileOpenError {};
    std::string str;

    try
    {
        std::ifstream fileContent(fileName);

        if (fileContent.fail())
            throw fileOpenError();
        else
            getline ( fileContent, str, '\0' );

        fileContent.close();
    }
    catch(fileOpenError) {
        str = "Error while opening html-file with content";
    }

    this->setText(WString(str));
    this->setTextFormat(Wt::XHTMLText);
    this->setTextAlignment(Wt::AlignmentFlag::AlignLeft);
}

