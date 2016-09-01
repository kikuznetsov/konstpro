#ifndef TEXTWRAP_H
#define TEXTWRAP_H

#include <string>
#include <Wt/WText>
#include <Wt/WContainerWidget>

using namespace Wt;
class Content : public Wt::WText
{
public:
    Content();
    Content(const char* fileName, WContainerWidget *parent=0);

    //const Wt::WText* getText();
    //int setText(const std::string &text);

};


#endif // TEXTWRAP_H
