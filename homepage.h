#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <Wt/WStackedWidget>
#include <Wt/WContainerWidget>
#include <Wt/WText>
#include <Wt/WImage>
#include "content.h"

using namespace Wt;

class HomePage:public WContainerWidget{
public:

    HomePage(WContainerWidget *parent=0);

private:

    WImage* ava;
    WText* shortText;
    Content* cnt;


};
#endif // HOMEPAGE_H
