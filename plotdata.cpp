#include "plotdata.h"

#include <Wt/WEnvironment>
#include <Wt/WLabel>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WRegExpValidator>
#include <Wt/WText>
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

    /*
     * Dialog's preparation
     *
     * */
    dialog = new Wt::WDialog("Go to cell");
    dialog->contents()->addStyleClass("form-group");
    dialog->rejectWhenEscapePressed();

    Wt::WPushButton *ok = new Wt::WPushButton("OK", dialog->footer());
    ok->setDefault(true);

    Wt::WPushButton *cancel = new Wt::WPushButton("Cancel", dialog->footer());

    ok->clicked().connect(std::bind([=] () {
        dialog->accept();
    }));

    cancel->clicked().connect(dialog, &Wt::WDialog::reject);

    dialog->finished().connect(std::bind([=] () {
        delete this->dialog;
    }));
    dialog->show();
}
void Plotdata::exportFunc(){

}
