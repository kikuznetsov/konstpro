#ifndef CVPAGE_H
#define CVPAGE_H

#include <Wt/WContainerWidget>
#include <Wt/WPushButton>
#include "content.h"

class CvPage: public Wt::WContainerWidget{

public:

    CvPage(Wt::WContainerWidget* parent = 0);

private:

    Wt::WPushButton* downloadCv;
    Content* briefCv;

};
#endif // CVPAGE_H
