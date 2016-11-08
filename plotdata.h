#ifndef PLOTDATA_H
#define PLOTDATA_H

#include <Wt/WContainerWidget>
#include <Wt/WPushButton>
#include <Wt/WDialog>
#include <boost/thread.hpp>
#include "oceansession.h"
#include "chooseocean.h"

class Plotdata:public Wt::WContainerWidget{
public:
    Plotdata(dbo::SqlConnectionPool& sqlConn, Wt::WContainerWidget* parent=0);
    virtual ~Plotdata(){
        exportThread.join();
    }
private:

    OceanSession session_;

    Wt::Chart::WCartesianChart *chart_;
    Wt::WDialog *dialog;

    //export data vars
    Wt::WText* info;
    Wt::WProgressBar* prBar;
    Wt::WAnchor* link;
    //export data vars end


    ChooseOcean* chooseData;
    Wt::WPushButton* plotButton;
    Wt::WPushButton* exportButton;
    //std::vector<Result> resData;

    boost::thread exportThread;

    void plotFunc();
    void exportFunc();
    void doExportFunc(Wt::WApplication* app); //function perform calculation

    void resToModel(std::vector<Result>& resData, Wt::WAbstractItemModel *model);
};
#endif // PLOTDATA_H
