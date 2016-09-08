#ifndef CVPAGE_H
#define CVPAGE_H

#include <Wt/WContainerWidget>
#include <Wt/WPushButton>
#include <Wt/WImage>
#include "content.h"

class CvPage: public Wt::WContainerWidget{

public:

    CvPage(Wt::WContainerWidget* parent = 0);

private:

    Wt::WImage* ava_;
    Wt::WPushButton* downloadCv_;
    Content* briefCv_;

};
#endif // CVPAGE_H
