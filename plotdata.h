#ifndef PLOTDATA_H
#define PLOTDATA_H

#include <Wt/WContainerWidget>
#include <Wt/WPushButton>
#include "chooseocean.h"

class Plotdata:public Wt::WContainerWidget{
public:
    Plotdata(Wt::WContainerWidget* parent=0);
private:
    //connection to database
    dbo::backend::Sqlite3 sqlCon_;
    dbo::Session session;

    ChooseOcean* chooseData;
    WPushButton* plotButton;
    WPushButton* exportButton;

    void plotFunc();
    void exportFunc();
};
#endif // PLOTDATA_H
