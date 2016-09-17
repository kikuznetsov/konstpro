#include "loadproc.h"
#include <iostream>
#include <boost/tokenizer.hpp>
#include <Wt/WStandardItemModel>

using namespace Wt;
using namespace Wt::Chart;

LoadProc::LoadProc(WContainerWidget* parent):WContainerWidget(parent){
    std::cout<<"wwe\n";
    //WStandardItemModel *model = new WStandardItemModel();
    Wt::WStandardItemModel *model = new Wt::WStandardItemModel();
    std::ifstream logLoadCpu("logProc.txt");

    if (logLoadCpu.fail())
        return;
    readFromCsv(logLoadCpu,model);
    if (!model)
        return;
    logLoadCpu.close();

    /*
     * Parses the first column as dates and times, to be able to use a time scale
     */
    for (int row = 0; row < model->rowCount(); ++row) {
        Wt::WString s = Wt::asString(model->data(row, 0));
        std::cout<<s<<"\n";
        Wt::WDateTime timeD = Wt::WDateTime::fromString(s, "yyyy/MM/dd hh:mm:ss");

        model->setData(row, 0, timeD);
    }

    /*
     * Creates the scatter plot.
     */
    chart_ = new Wt::Chart::WCartesianChart(this);
    chart_->setBackground(Wt::WColor(250,250,250));
    chart_->setModel(model);
    chart_->setXSeriesColumn(0);
    //chart_->setLegendEnabled(true);
    chart_->setType(Wt::Chart::ScatterPlot);
    chart_->axis(Wt::Chart::XAxis).setScale(Wt::Chart::DateTimeScale);
    chart_->axis(Wt::Chart::YAxis).setMaximum(100);
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
    for (int i = 2; i < 3; ++i) {
        Wt::Chart::WDataSeries *s = new Wt::Chart::WDataSeries(i, Wt::Chart::CurveSeries);
        s->setFillRange(Wt::Chart::FillRangeType::MinimumValueFill);
        //s->setShadow(Wt::WShadow(3, 3, Wt::WColor(0, 0, 0, 127), 3));
        chart_->addSeries(s);
    }

    chart_->resize(350, 200);
    chart_->setTitle("CPU Load, %");
    chart_->setMargin(Wt::WLength::Auto, Wt::Left | Wt::Right);

}

void LoadProc::readFromCsv(std::istream& f, Wt::WAbstractItemModel *model,
         int numRows, bool firstLineIsHeaders)
{
    int csvRow = 0;

    while (f) {
        std::string line;
        getline(f, line);

        if (f) {
            typedef boost::tokenizer<boost::char_separator<char> >  CsvTokenizer;
            boost::char_separator<char> sep("-;");
            CsvTokenizer tok(line,sep);

            int col = 0;
            for (CsvTokenizer::iterator i = tok.begin();i != tok.end(); ++i, ++col) {
                if (col >= model->columnCount())
                    model->insertColumns(model->columnCount(),col + 1 - model->columnCount());

                if (firstLineIsHeaders && csvRow == 0)
                    model->setHeaderData(col, boost::any(Wt::WString::fromUTF8(*i)));
                else {
                    int dataRow = firstLineIsHeaders ? csvRow - 1 : csvRow;

                    if (numRows != -1 && dataRow >= numRows)
                        return;

                    if (dataRow >= model->rowCount())
                        model->insertRows(model->rowCount(),dataRow + 1 - model->rowCount());

                    boost::any data;
                    std::string s = *i;
                    char *endptr;

                    if (s.empty())
                        data = boost::any();
                    else {
                        double d = strtod(s.c_str(), &endptr);
                        if (*endptr == 0)
                            data = boost::any(d);
                        else
                            data = boost::any(Wt::WString::fromUTF8(s));
                    }

                    model->setData(dataRow, col, data);
                }
            }
        }
        ++csvRow;
    }
}
