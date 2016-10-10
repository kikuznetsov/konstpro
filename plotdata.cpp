#include "plotdata.h"

Plotdata::Plotdata(dbo::SqlConnectionPool& sqlConn, Wt::WContainerWidget *parent):
    Wt::WContainerWidget(parent),
    session_(sqlConn)   //setup connection
{
    chooseData = new ChooseOcean(sqlConn, parent);

    plotButton = new Wt::WPushButton("Plot data", parent);
    plotButton->setStyleClass("btn-primary");
    plotButton->clicked().connect(this, &Plotdata::plotFunc);

    exportButton = new Wt::WPushButton("Export data", parent);
    exportButton->setStyleClass("btn-success");
    exportButton->clicked().connect(this, &Plotdata::exportFunc);
}
void Plotdata::plotFunc(){

}
void Plotdata::exportFunc(){

}
