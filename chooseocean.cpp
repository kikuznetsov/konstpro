#include "chooseocean.h"
#include <Wt/WText>
#include <Wt/WLabel>
#include <Wt/WPushButton>
#include <Wt/WHBoxLayout>
#include <Wt/WCheckBox>
#include <Wt/WPushButton>
#include <iostream>
#include <sstream>

ChooseOcean::ChooseOcean(const dbo::Session& sessionKey, WContainerWidget *parent )
  : WContainerWidget(parent)
{
    session = sessionKey;
    //create UI for user-defined place1,place2, begTime, endTime
    place1IdUser_ = "All";
    place2IdUser_ = " ";
    begTimeUser_ = WDateTime::fromString("01/01/1987","dd/MM/yyyy");
    endTimeUser_ = WDateTime::currentDateTime();
    //std::vector<Passport> passportUser_;
    createUI(parent);

    //create list of results
    listResults_=new WTable(parent);
    listResults_->addStyleClass("table-bordered");
    listResults_->addStyleClass("table-condensed");
    listResults_->addStyleClass("table-striped");
    listResults_->addStyleClass("table-hover");

}

void ChooseOcean::createUI(WContainerWidget* parent){
    uiPlaceTime = new WTable(parent);
    WLabel *label;
    int row = 0;

    //Place
    bxPlace.push_back(new WComboBox(uiPlaceTime->elementAt(row, 1)));

    //add items to comboBox bxPlace
    bxPlace[0]->addItem("All");
    {
        dbo::Transaction transaction(session);
        PtrPlaces places=session.find<Place>();
        for(PtrPlaces::const_iterator i = places.begin();i!=places.end();i++){
            bxPlace[0]->addItem((*i)->fullName);
        }
        transaction.commit();
    }

    label = new WLabel("Places", uiPlaceTime->elementAt(row,0));
    label->setBuddy(bxPlace[0]);
    bxPlace[0]->setMargin(5);
    bxPlace[0]->setValidator(new WValidator(true));
    bxPlace[0]->changed().connect(this, &ChooseOcean::bxPlace1Changed);

    // From Time
    ++row;
    txtFromTime_ = new WText("01.01.1987 00:00:00", uiPlaceTime->elementAt(row, 1));
    uiPlaceTime->elementAt(row, 1)->setToolTip("Move slider to specify START time of records");
    label = new WLabel("<b>From time</b>", uiPlaceTime->elementAt(row, 0));
    ++row;
    sldFromTime_ = new WSlider();
    sldFromTime_->valueChanged().connect(this, &ChooseOcean::sldFromChanged);


    //set up view of "from time"
    //sldFromTime_->setEnabled(false);
    uiPlaceTime->elementAt(row, 1)->setToolTip("Move slider to specify START time of records");
    sldFromTime_->setWidth(200);
    WHBoxLayout* hBoxFromTime = new WHBoxLayout();
    lblFromBegTime_ = new WText("01.01.1987");
    lblFromEndTime_ = new WText("01.01.1987");
    hBoxFromTime->addWidget(lblFromBegTime_);
    hBoxFromTime->addWidget(sldFromTime_);
    hBoxFromTime->addWidget(lblFromEndTime_);
    uiPlaceTime->elementAt(row,1)->setLayout(hBoxFromTime);

    // To Time
    ++row;
    txtToTime_ = new WText("01/01/1987 00:00:00", uiPlaceTime->elementAt(row, 1));
    uiPlaceTime->elementAt(row, 1)->setToolTip("Move slider to specify FINISH time of records");
    label = new WLabel("<b>To time</b>", uiPlaceTime->elementAt(row, 0));
    ++row;
    sldToTime_ = new WSlider();
    sldToTime_->valueChanged().connect(this, &ChooseOcean::sldToChanged);

    //set up view of "to time"
    uiPlaceTime->elementAt(row, 1)->setToolTip("Move slider to specify FINISH time of records");
    sldToTime_->setWidth(200);
    sldToTime_->setValue(100);
    WHBoxLayout* hBoxToTime = new WHBoxLayout();
    lblToBegTime_= new WText("01.01.1987");
    lblToEndTime_= new WText("01.01.1987");
    hBoxToTime->addWidget(lblToBegTime_);
    hBoxToTime->addWidget(sldToTime_);
    hBoxToTime->addWidget(lblToEndTime_);
    uiPlaceTime->elementAt(row,1)->setLayout(hBoxToTime);


    //Result
    ++row;
    listResults_ = new WTable(uiPlaceTime->elementAt(row,0));

//    // Submit
//    ++row;
//    WPushButton *submit = new WPushButton("Export", uiPlaceTime->elementAt(row, 0));
//    //submit->clicked().connect(this, &Form::submit);
//    submit->setMargin(15, Top);

    // Set column widths for label and validation icon
    uiPlaceTime->elementAt(2, 0)->resize(WLength(30, WLength::FontEx), WLength::Auto);
    uiPlaceTime->elementAt(2, 1)->resize(10, WLength::Auto);

    //set up view
    sldFromTime_->setMargin(5);
    sldToTime_->setMargin(5);
    txtFromTime_->setMargin(5);
    txtToTime_->setMargin(5);

    for(int i=0;i<row;i++){
        uiPlaceTime->elementAt(i, 0)->setContentAlignment(AlignRight);
        uiPlaceTime->elementAt(i, 1)->setContentAlignment(AlignLeft);
        //elementAt(i, 2)->resize(100, WLength::Auto);
        uiPlaceTime->elementAt(i,1)->setWidth(300);
        //elementAt(i,1)->setMargin(5);
        //elementAt(i,0)->setContentAlignment();
    }
}

void ChooseOcean::bxPlace1Changed(){
    if(bxPlace.size()<2){
        uiPlaceTime->insertRow(1);
        bxPlace.push_back(new WComboBox(uiPlaceTime->elementAt(1,1)));
        bxPlace[1]->setMargin(5);

    }
    bxPlace[1]->clear();
    bxPlace[1]->addItem(" ");

    {
        dbo::Transaction transaction(session);
        WString t = bxPlace[0]->currentText();
        place1IdUser_ = session.query<WString>("select id from place").where("fullname = ?").bind(t);
        place2IdUser_ = " ";
        PtrPlaces places1=session.find<Place>().where("fullname <> ?").bind(t);
        for(PtrPlaces::const_iterator i = places1.begin();i!=places1.end();i++){
            bxPlace[1]->addItem((*i)->fullName);
        }

    }
    setUserTime();
    createResults();
    bxPlace[1]->changed().connect(this, &ChooseOcean::bxPlace2Changed);

}
void ChooseOcean::setUserTime(){
    {
        dbo::Transaction transaction(session);
        PtrExps exps1;
        if(place1IdUser_=="All"){
            exps1 = session.find<Passport>();
        }
        else{
            if(place2IdUser_!=" "){
                exps1 = session.find<Passport>().where("place_id = ? or place_id = ?")
                                                    .bind(place1IdUser_)
                                                    .bind(place2IdUser_);
            }
            else{
                exps1 = session.find<Passport>().where("place_id = ?")
                                                    .bind(place1IdUser_);
            }
        }

        //calculate start and finish time
        int count = 0;
        for(PtrExps::const_iterator i = exps1.begin();i!=exps1.end();i++){
            if(count==0){
                begTimeSample_ = (*i)->begTime;
                endTimeSample_ = (*i)->endTime;
            }
            count++;
            if((*i)->begTime<=begTimeSample_)
                   begTimeSample_ = (*i)->begTime;
            if((*i)->endTime>=endTimeSample_)
                   endTimeSample_ = (*i)->endTime;
        }

        txtFromTime_->setText(begTimeSample_.toString("dd.MM.yyyy hh:mm:ss"));
        txtToTime_  ->setText(endTimeSample_.toString("dd.MM.yyyy hh:mm:ss"));

        lblFromBegTime_ ->setText(begTimeSample_.toString("dd.MM.yyyy"));
        lblFromEndTime_ ->setText(endTimeSample_.toString("dd.MM.yyyy"));
        lblToBegTime_   ->setText(begTimeSample_.toString("dd.MM.yyyy"));
        lblToEndTime_   ->setText(endTimeSample_.toString("dd.MM.yyyy"));

        begTimeUser_ = begTimeSample_;
        endTimeUser_ = endTimeSample_;
        transaction.commit();
    }
}
void ChooseOcean::bxPlace2Changed(){
    dbo::Transaction transaction(session);
    place2IdUser_ = session.query<WString>("select id from place").where("fullname = ?").bind(bxPlace[1]->currentText());

    setUserTime();
    createResults();
}
void ChooseOcean::typeDataChanged(){

}
void ChooseOcean::sldFromChanged(){
    std::time_t delta = endTimeUser_.toTime_t() - begTimeSample_.toTime_t();
    delta = delta*sldFromTime_->value()/100;
    WDateTime curr;
    curr.setTime_t(begTimeSample_.toTime_t()+delta);
    begTimeUser_ = curr;
    txtFromTime_ ->setText(curr.toString("dd.MM.yyyy hh:mm:ss"));
    lblToBegTime_->setText(curr.toString("dd.MM.yyyy"));

    createResults();
}
void ChooseOcean::sldToChanged(){
    std::time_t delta = endTimeSample_.toTime_t() - begTimeUser_.toTime_t();
    delta = delta*sldToTime_->value()/100;
    WDateTime curr;
    curr.setTime_t(begTimeUser_.toTime_t()+delta);
    endTimeUser_ = curr;
    txtToTime_ ->setText(curr.toString("dd.MM.yyyy hh:mm:ss"));
    lblFromEndTime_->setText(curr.toString("dd.MM.yyyy"));

    createResults();

}
void ChooseOcean::createResults(){
    //for input we use  place1
    listResults_->clear();
    WText* isChecked = new WText("<b></b>", listResults_->elementAt(0,0));
    WText* headNumGauge = new WText("<b>Num of Gauge</b>", listResults_->elementAt(0,1));
    WText* headPlace    = new WText("<b>Place</b>", listResults_->elementAt(0,2));
    WText* headFromTime = new WText("<b>Start time</b>", listResults_->elementAt(0,3));
    WText* headToTime = new WText("<b>Finish time</b>", listResults_->elementAt(0,4));
    WText* depth = new WText("<b>Depth, m</b>", listResults_->elementAt(0,5));
    WText* typeData = new WText("<b>Type of data</b>", listResults_->elementAt(0,6));


    std::vector<WCheckBox*> lstCheckBox;
    std::vector<int> idExps;
    {
        dbo::Transaction transaction(session);
        WString t = bxPlace[0]->currentText();
        PtrExps exps;
        if(place1IdUser_==""){ //all places
             exps = session.find<Passport>().where("begTime <= ? and endTime >= ?")
                    .bind(begTimeUser_)
                    .bind(endTimeUser_);
        }
        else{
            exps = session.find<Passport>().where("place_id=? or place_id=? and begTime <= ? and endTime >= ?")
                                                .bind(place1IdUser_)
                                                .bind(place2IdUser_)
                                                .bind(begTimeUser_)
                                                .bind(endTimeUser_);
        }
        int row=1;
        WLabel* label;
        std::ostringstream strsDepth;
        for(PtrExps::const_iterator i = exps.begin();i!=exps.end();i++){

            lstCheckBox.push_back(new WCheckBox(listResults_->elementAt(row,0)));

            label = new WLabel((*i)->nameGauge, listResults_->elementAt(row,1));
            label = new WLabel((*i)->place->fullName, listResults_->elementAt(row,2));
            label = new WLabel((*i)->begTime.toString("dd.MM.yyyy hh:mm"), listResults_->elementAt(row,3));
            label = new WLabel((*i)->endTime.toString("dd.MM.yyyy hh:mm"), listResults_->elementAt(row,4));
            strsDepth<<(*i)->depth;
            label = new WLabel(strsDepth.str(), listResults_->elementAt(row,5));

            strsDepth.str(""); strsDepth.clear();
            row++;
        }

    }
}
WString ChooseOcean::getPlace1(){
    return this->place1IdUser_;
}

WString ChooseOcean::getPlace2(){
    return this->place2IdUser_;
}

WDateTime ChooseOcean::getBegTime(){
    return this->begTimeUser_;
}

WDateTime ChooseOcean::getEndTime(){
    return this->endTimeUser_;
}
