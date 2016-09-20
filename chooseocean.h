#ifndef CHOOSEOCEAN_H
#define CHOOSEOCEAN_H

#include <Wt/WTable>
#include <Wt/WSlider>
#include <Wt/WText>
#include <Wt/WComboBox>
#include <vector>
#include <string>
//#include <Wt/Dbo/SqlConnection>
#include "structdb.h"

using namespace Wt;

typedef dbo::collection<dbo::ptr<Passport>> PtrExps;
typedef dbo::collection<dbo::ptr<Place>>    PtrPlaces;

class ChooseOcean:public WTable{
public:

    ChooseOcean(WContainerWidget* parent=0);

private:

    //WComboBox* bxTypeData_;

    WComboBox* bxPlace1_;
    WComboBox* bxPlace2_;
    WComboBox* bxPlace3_;
    std::vector<WComboBox*> bxPlace;

    WText* txtFromTime_;
    WText* txtToTime_;

    WSlider* sldFromTime_;
    WSlider* sldToTime_;

    dbo::backend::Sqlite3 sqlCon_;
    dbo::Session session;

    PtrPlaces places_; //posible to assign only ONE time (DBO-library fault)
    PtrExps exps_;     //posible to assign only ONE time (DBO-library fault)
                       //need to change to std::vector, and save all history of querys is this vector

    WDateTime begTimeSample_; //time which comes from database
    WDateTime endTimeSample_;

    WDateTime begTimeUser_; //time whitch was defined by user
    WDateTime endTimeUser_;

    WText* lblFromBegTime_;
    WText* lblFromEndTime_;

    WText* lblToBegTime_;
    WText* lblToEndTime_;



    WTable* listResults_;
//    std::vector<WComboBox*> lstComboboxRes_;
//    std::vector<string> lstNumGauges_;
//    std::vector<string> lstPlaces_;
//    std::vector<string> lstFromTime_;
//    std::vector<string> lstToTime_;

//    WPushButton* btnGetData_;

    void createUI();

    void typeDataChanged();
    void bxPlace1Changed();
    void bxPlace2Changed();

    void sldFromChanged();
    void sldToChanged();

};


#endif // CHOOSEOCEAN_H
