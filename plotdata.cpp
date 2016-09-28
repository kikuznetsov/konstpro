#include "plotdata.h"

Plotdata::Plotdata(Wt::WContainerWidget *parent):
    Wt::WContainerWidget(parent),
    sqlCon_("test.db") //create connection
{
    //set up connection
    session.setConnection(sqlCon_);
    //associate classes and tables
    session.mapClass<Passport>("passport");
    session.mapClass<Rec>("exp");
    session.mapClass<Place>("place");

    chooseData = new ChooseOcean(session, parent);

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
