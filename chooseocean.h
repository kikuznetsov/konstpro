#ifndef CHOOSEOCEAN_H
#define CHOOSEOCEAN_H

#include <Wt/WTable>
#include <Wt/WSlider>
#include <Wt/WLineEdit>
#include <Wt/WComboBox>
#include <vector>
#include <string>

using namespace Wt;


class ChooseOcean:public WTable{
public:

    ChooseOcean(WContainerWidget* parent=0);

private:

    WComboBox* bxTypeData_;

    WComboBox* bxPlace1_;
    WComboBox* bxPlace2_;
    WComboBox* bxPlace3_;

    WSlider* sldFromTime_;
    WSlider* sldToTime_;

    WTable* listResults_;
//    std::vector<WComboBox*> lstComboboxRes_;
//    std::vector<string> lstNumGauges_;
//    std::vector<string> lstPlaces_;
//    std::vector<string> lstFromTime_;
//    std::vector<string> lstToTime_;

//    WPushButton* btnGetData_;

    void createUI();

    void typeDataChanged();
    void bxPlaceChanged();
    void sldChanged();

};


#endif // CHOOSEOCEAN_H
