#ifndef OCEANDATA_H
#define OCEANDATA_H

#include <Wt/WContainerWidget>
#include <Wt/WMenu>
#include <Wt/WText>
#include "plotdata.h"
#include "mapocean.h"
#include "oceansession.h"

using namespace Wt;

class OceanData:public Wt::WContainerWidget{
public:
    OceanData(WContainerWidget* parent=0);
private:

    WMenu* menu_;
    WText* textOverview_;

    dbo::SqlConnectionPool* db_; //pool of all connections to db
    Plotdata* plotdata_;
    MapOcean* mapOcean_;


};
#endif // OCEANDATA_H
