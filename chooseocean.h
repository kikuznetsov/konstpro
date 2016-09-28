#ifndef CHOOSEOCEAN_H
#define CHOOSEOCEAN_H

#include <Wt/WContainerWidget>
#include <Wt/WStackedWidget>
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

class ChooseOcean:public WContainerWidget{
public:

    ChooseOcean(const dbo::Session& sessionKey, WContainerWidget* parent=0);
    //~ChooseOcean();

    WString getPlace1();
    WString getPlace2();

    WDateTime getBegTime();
    WDateTime getEndTime();

private:

    dbo::Session session;

    //UI: form for specify PlaceId ans Time
    WTable* uiPlaceTime;
    std::vector<WComboBox*> bxPlace;

    WText* txtFromTime_;
    WText* txtToTime_;

    WSlider* sldFromTime_;
    WSlider* sldToTime_;

    WText* lblFromBegTime_;
    WText* lblFromEndTime_;

    WText* lblToBegTime_;
    WText* lblToEndTime_;

    //UI: form for specify expId
    WTable* listResults_;
    std::vector<WComboBox*> lstComboboxRes_;
    std::vector<WString>    lstNumGauges_;
    std::vector<WString>    lstPlaces_;
    std::vector<WString>    lstFromTime_;
    std::vector<WString>    lstToTime_;
    std::vector<double>     lstDepth_;
    std::vector<int>        lstFilt_;

    //WPushButton* btnGetData_;

    WDateTime begTimeSample_; //time which comes from database
    WDateTime endTimeSample_;

    //result of user actions
    WString place1IdUser_;
    WString place2IdUser_;
    WDateTime begTimeUser_; //time whitch was defined by user
    WDateTime endTimeUser_;
    //std::vector<Passport> passportUser_;
    //results.............


    void createUI(WContainerWidget* parent);

    void typeDataChanged();
    void bxPlace1Changed();
    void bxPlace2Changed();

    void sldFromChanged();
    void sldToChanged();

    void createResults();
    void setUserTime();

};


#endif // CHOOSEOCEAN_H
