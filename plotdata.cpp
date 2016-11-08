#include "plotdata.h"
#include "loadproc.h"

//#include <Wt/WEnvironment>
#include <Wt/WApplication>
#include <Wt/WLabel>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WRegExpValidator>
#include <Wt/WStandardItemModel>
#include <Wt/WText>
#include <Wt/WProgressBar>
#include <fstream>
#include <cstdlib>

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
void Plotdata::resToModel(std::vector<Result>& resData, Wt::WAbstractItemModel* model){

    Wt::WString queryStr;
    model->insertColumns(0, resData.size());
    int col=0;
    int row=0;
    std::vector<std::pair<Wt::WDateTime, double>> dataPressOrTemp;
    boost::any data;
    for(auto el = resData.begin(); el!=resData.end(); ++el){
        dataPressOrTemp.clear();
        Result tmp = (*el);
        session_.getData(tmp, dataPressOrTemp); //get Results from DB
        model->insertColumn(0);
        row = 0;
        for (int i=0; i<dataPressOrTemp.size(); i=i+600) {
            data = boost::any(dataPressOrTemp[i].second);
            if (row >= model->rowCount())
                model->insertRow(model->rowCount());
            model->setData(row, col, data);
            row++;
        }
        col++;
    }
    model->insertColumn(0);
    row=0;
    for (int i=0; i<dataPressOrTemp.size(); i=i+600) {
        data = boost::any(dataPressOrTemp[i].first);
        model->setData(row, 0, data);
        row++;
    }
}
void Plotdata::plotFunc(){

    /* *
     * Dialog's preparation
     *
     * */
    dialog = new Wt::WDialog("Plot data");
    dialog->contents()->addStyleClass("form-group");
    dialog->rejectWhenEscapePressed();


    Wt::WStandardItemModel *model = new Wt::WStandardItemModel();
    std::vector<Result> res = chooseData->getResult();

    resToModel(res, model);


    /*
     * Creates the scatter plot.
     */
    chart_ = new Wt::Chart::WCartesianChart(dialog->contents());
    chart_->setBackground(Wt::WColor(250,250,250));
    chart_->setModel(model);
    chart_->setXSeriesColumn(0);
    //chart_->setLegendEnabled(true);
    chart_->setType(Wt::Chart::ScatterPlot);
    chart_->axis(Wt::Chart::XAxis).setScale(Wt::Chart::DateTimeScale);
    //chart_->axis(Wt::Chart::YAxis).setMaximum(100);
    double timeMin = Wt::asNumber(model->data(0, 0));
    double timeMax = Wt::asNumber(model->data(model->rowCount() - 1, 0));
    chart_->axis(Wt::Chart::XAxis).setMaximum(timeMax);
    chart_->axis(Wt::Chart::XAxis).setMinimum(timeMin);
    //chart_->title("Server load, %");

    /*
     * Provide ample space for the title, the X and Y axis and the legend.
     */
    //chart_->setPlotAreaPadding(40, Wt::Left | Wt::Top | Wt::Bottom);
    //chart_->setPlotAreaPadding(120, Wt::Right);

    /*
     * Add the second and the third column as line series.
     */
    for (int i = 1; i < 3; ++i) {
        Wt::Chart::WDataSeries *s = new Wt::Chart::WDataSeries(i, Wt::Chart::CurveSeries);
        //s->setFillRange(Wt::Chart::FillRangeType::MinimumValueFill);
        //s->setShadow(Wt::WShadow(3, 3, Wt::WColor(0, 0, 0, 127), 3));
        chart_->addSeries(s);
    }

    chart_->resize(900, 400);
    //chart_->setTitle("CPU Load, %");
    chart_->setMargin(Wt::WLength::Auto, Wt::Left | Wt::Right);

    /////////////////////////////////////////////////////////////





    Wt::WPushButton *save = new Wt::WPushButton("Save as image", dialog->footer());
    save->setDefault(true);

    Wt::WPushButton *cancel = new Wt::WPushButton("Cancel", dialog->footer());

    save->clicked().connect(std::bind([=] () {
        dialog->accept();
    }));

    cancel->clicked().connect(dialog, &Wt::WDialog::reject);

    dialog->finished().connect(std::bind([=] () {
        delete this->dialog;
    }));
    dialog->show();
}
void Plotdata::doExportFunc(Wt::WApplication* app){

    {
        Wt::WApplication::UpdateLock uiLock(app);
        if (uiLock) {
            info->setText("export data from database...");
            prBar->setValue(10);
            app->triggerUpdate();
        }
    }
    std::vector<Result> res = chooseData->getResult();
    Result currRes;
    std::vector<double> press;
    bool r = true;
    WString fileList="";
    WString fName_tmp="";
    std::ofstream fStream;
    for (std::vector<Result>::const_iterator i = res.begin(); i!=res.end(); i++) {
        currRes = (*i);
        r = session_.getDataFast(currRes.getType(), currRes.getId(), currRes.getBegTime(), currRes.getEndTime(), press); //get Results from
        fName_tmp = "Sakh_N"+std::to_string(currRes.getId())+"_"+currRes.getBegTime().toString("yyyy.MM.dd")+".txt";
        fileList+=fName_tmp+" ";
        {
            Wt::WApplication::UpdateLock uiLock(app);
            if (uiLock) {
                info->setText("Write data into file...");
                prBar->setValue(50);
                app->triggerUpdate();
            }
        }
        fStream.open(fName_tmp.toUTF8());
        for(auto j=press.begin();j!=press.end();j++){
            fStream<<(*j)<<std::endl;
        }
        fStream.close();
    }
    WString fNameZip = "Sakh_"+currRes.getBegTime().toString("yyyy.MM.dd")+".zip";
    WString strProg = "zip -1 " + fNameZip + " " + fileList;
    WString strDelTxt = "rm " + fileList;
    WString strDelZip = "rm " + fNameZip;
    system(strDelZip.toUTF8().c_str()); //delete zip-archive with the same name
    {
        Wt::WApplication::UpdateLock uiLock(app);
        if (uiLock) {
            info->setText("Compress data to zip-archive...");
            prBar->setValue(80);
            app->triggerUpdate();
        }
    }
    system(strProg.toUTF8().c_str()); //perform compress using system zip
    system(strDelTxt.toUTF8().c_str()); //delete txt-files
    {
        Wt::WApplication::UpdateLock uiLock(app);
        if (uiLock) {
            info->setText("done!");
            link->setText(fNameZip);
            link->setLink(Wt::WLink(fNameZip.toUTF8()));
            prBar->setValue(100);
            dialog->enable();
            app->triggerUpdate();
            app->enableUpdates(false);
        }
    }


}
//bool zipCompress(std::string& buf, std::string archName)
void Plotdata::exportFunc(){

    dialog = new Wt::WDialog("Download data");
    dialog->contents()->addStyleClass("form-group");
    dialog->rejectWhenEscapePressed();

    info = new Wt::WText("", dialog->contents());
    prBar = new Wt::WProgressBar(dialog->contents());
    prBar->setValue(0);
    link =  new Wt::WAnchor(dialog->contents());


    Wt::WPushButton *cancel = new Wt::WPushButton("Close", dialog->footer());
    cancel->setDefault(true);

    cancel->clicked().connect(dialog, &Wt::WDialog::reject);

    dialog->finished().connect(std::bind([=] () {
        delete this->dialog;
    }));


    Wt::WApplication* app = Wt::WApplication::instance();
    app->enableUpdates(true);

    exportThread = boost::thread(boost::bind(&Plotdata::doExportFunc, this, app));

    dialog->show();
    dialog->disable();

}
