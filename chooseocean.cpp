#include "chooseocean.h"
#include <Wt/WText>
#include <Wt/WLabel>
#include <Wt/WPushButton>


ChooseOcean::ChooseOcean(WContainerWidget *parent)
  : WTable(parent)
{
  createUI();
}
void ChooseOcean::createUI(){
    WLabel *label;
    int row = 0;

    // Title
    elementAt(row, 0)->setColumnSpan(3);
    elementAt(row, 0)->setContentAlignment(AlignTop | AlignCenter);
    elementAt(row, 0)->setPadding(10);
    WText *title = new WText("list of results", elementAt(row, 0));

    // Type of data
    ++row;
    bxTypeData_ = new WComboBox(elementAt(row, 2));
    bxTypeData_->addItem("Init press");
    bxTypeData_->addItem("Filtered press");
    bxTypeData_->addItem("Temperature");
    bxTypeData_->addItem("Meteo");
    label = new WLabel("Type of data", elementAt(row, 0));
    label->setBuddy(bxTypeData_);
    bxTypeData_->setValidator(new WValidator(true));
    bxTypeData_->changed().connect(this, &ChooseOcean::typeDataChanged);

    // Place
    ++row;
    bxPlace1_ = new WComboBox(elementAt(row, 2));
    bxPlace1_->addItem("");
    label = new WLabel("Places", elementAt(row,0));
    label->setBuddy(bxPlace1_);
    bxPlace1_->setValidator(new WValidator(true));
    bxPlace1_->changed().connect(this, &ChooseOcean::bxPlaceChanged);

    bxPlace2_ = new WComboBox(elementAt(row, 2));
    bxPlace2_->addItem("");
    label = new WLabel("and", elementAt(row,2));
    label->setBuddy(bxPlace2_);
    bxPlace2_->changed().connect(this, &ChooseOcean::bxPlaceChanged);

    bxPlace3_ = new WComboBox(elementAt(row, 2));
    bxPlace3_->addItem("");
    label = new WLabel("and", elementAt(row,2));
    label->setBuddy(bxPlace3_);
    bxPlace3_->changed().connect(this, &ChooseOcean::bxPlaceChanged);

    // From Time
    ++row;
    sldFromTime_ = new WSlider(elementAt(row, 2));
    label = new WLabel("From time", elementAt(row, 0));
    label->setBuddy(sldFromTime_);
    sldFromTime_->changed().connect(this, &ChooseOcean::sldChanged);

    // To Time
    ++row;
    sldToTime_ = new WSlider(elementAt(row, 2));
    label = new WLabel("To time", elementAt(row, 0));
    label->setBuddy(sldToTime_);
    sldToTime_->changed().connect(this, &ChooseOcean::sldChanged);

    //Result
    ++row;
    listResults_ = new WTable(elementAt(row,0));

    // Submit
    ++row;
    WPushButton *submit = new WPushButton(tr("submit"),
                      elementAt(row, 0));
    //submit->clicked().connect(this, &Form::submit);
    submit->setMargin(15, Top);
    elementAt(row, 0)->setColumnSpan(3);
    elementAt(row, 0)->setContentAlignment(AlignTop | AlignCenter);

    // Set column widths for label and validation icon
    elementAt(2, 0)->resize(WLength(30, WLength::FontEx), WLength::Auto);
    elementAt(2, 1)->resize(20, WLength::Auto);
}
void ChooseOcean::typeDataChanged(){

}
void ChooseOcean::bxPlaceChanged(){

}
void ChooseOcean::sldChanged(){

}
