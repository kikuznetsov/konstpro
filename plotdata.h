#ifndef PLOTDATA_H
#define PLOTDATA_H

#include <Wt/WContainerWidget>
#include <Wt/WPushButton>
#include "oceansession.h"
#include "chooseocean.h"

class Plotdata:public Wt::WContainerWidget{
public:
    Plotdata(dbo::SqlConnectionPool& sqlConn, Wt::WContainerWidget* parent=0);
private:

    OceanSession session_;

    ChooseOcean* chooseData;
    Wt::WPushButton* plotButton;
    Wt::WPushButton* exportButton;

    void plotFunc();
    void exportFunc();
};
#endif // PLOTDATA_H
