#ifndef LOADPROC_H
#define LOADPROC_H

#include <Wt/WContainerWidget>
#include <Wt/Chart/WCartesianChart>
#include <Wt/WAbstractItemModel>

class LoadProc:public Wt::WContainerWidget{
public:

    LoadProc(WContainerWidget* parent=0);

private:

    Wt::Chart::WCartesianChart *chart_;


    void readFromCsv(std::istream& f, Wt::WAbstractItemModel *model,
                int numRows = -1, bool firstLineIsHeaders = true);

};
#endif // LOADPROC_H

