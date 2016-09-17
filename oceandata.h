#ifndef OCEANDATA_H
#define OCEANDATA_H

#include <Wt/WContainerWidget>
#include <Wt/WMenu>
#include <Wt/WText>

using namespace Wt;

class OceanData:public Wt::WContainerWidget{
public:
    OceanData(WContainerWidget* parent=0);
private:

    WMenu* menu_;
    WText* textOverview_;
    WText* textChoose_;

};
#endif // OCEANDATA_H
