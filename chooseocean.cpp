#include "chooseocean.h"
#include <Wt/WText>
#include <Wt/WLabel>
#include <Wt/WPushButton>
#include <Wt/WHBoxLayout>
#include <istream>


ChooseOcean::ChooseOcean(WContainerWidget *parent)
  : WTable(parent),
    sqlCon_("test.db") //create connection
{
    //set up connection

    session.setConnection(sqlCon_);

    //associate classes and tables
    session.mapClass<Passport>("passport");
    session.mapClass<Rec>("exp");
    session.mapClass<Place>("place");
    createUI();


}
void ChooseOcean::createUI(){
    WLabel *label;
    int row = 0;



    // Title
//    elementAt(row, 0)->setColumnSpan(3);
//    elementAt(row, 0)->setContentAlignment(AlignTop | AlignCenter);
//    elementAt(row, 0)->setPadding(10);
    //WText *title = new WText("list of results", elementAt(row, 0));

    // Type of data
    //++row;
//    bxTypeData_ = new WComboBox(elementAt(row, 1));
//    bxTypeData_->addItem("Init press");
//    bxTypeData_->addItem("Filtered press");
//    bxTypeData_->addItem("Temperature");
//    bxTypeData_->addItem("Meteo");
//    label = new WLabel("Type of data", elementAt(row, 0));
//    label->setBuddy(bxTypeData_);
//    bxTypeData_->setValidator(new WValidator(true));
//    bxTypeData_->changed().connect(this, &ChooseOcean::typeDataChanged);

//    // Place
    bxPlace.push_back(new WComboBox(elementAt(row, 1)));
    bxPlace[0]->addItem("All");

    {
        dbo::Transaction transaction(session);
        places_=session.find<Place>();
        for(PtrPlaces::const_iterator i = places_.begin();i!=places_.end();i++){
            bxPlace[0]->addItem((*i)->fullName);
        }
        transaction.commit();
    }

    label = new WLabel("Places", elementAt(row,0));
    label->setBuddy(bxPlace[0]);
    bxPlace[0]->setMargin(5);
    bxPlace[0]->setValidator(new WValidator(true));
    bxPlace[0]->changed().connect(this, &ChooseOcean::bxPlace1Changed);

    // From Time
    ++row;
    txtFromTime_ = new WText("01.01.1987 00:00:00", elementAt(row, 1));
    label = new WLabel("<b>From time</b>", elementAt(row, 0));
    ++row;
    sldFromTime_ = new WSlider();
    sldFromTime_->valueChanged().connect(this, &ChooseOcean::sldFromChanged);


    //set up view of "from time"
    //sldFromTime_->setEnabled(false);
    sldFromTime_->setToolTip("Move slider to specify START time of records");
    sldFromTime_->setWidth(200);
    WHBoxLayout* hBoxFromTime = new WHBoxLayout();
    lblFromBegTime_ = new WText("01.01.1987");
    lblFromEndTime_ = new WText("01.01.1987");
    hBoxFromTime->addWidget(lblFromBegTime_);
    hBoxFromTime->addWidget(sldFromTime_);
    hBoxFromTime->addWidget(lblFromEndTime_);
    elementAt(row,1)->setLayout(hBoxFromTime);

    // To Time
    ++row;
    txtToTime_ = new WText("01/01/1987 00:00:00", elementAt(row, 1));
    label = new WLabel("<b>To time</b>", elementAt(row, 0));
    ++row;
    sldToTime_ = new WSlider();
    sldToTime_->valueChanged().connect(this, &ChooseOcean::sldToChanged);

    //set up view of "to time"
    sldToTime_->setWidth(200);
    sldToTime_->setValue(100);
    sldToTime_->setToolTip("Move slider to specify FINISH time of records");
    WHBoxLayout* hBoxToTime = new WHBoxLayout();
    lblToBegTime_= new WText("01.01.1987");
    lblToEndTime_= new WText("01.01.1987");
    hBoxToTime->addWidget(lblToBegTime_);
    hBoxToTime->addWidget(sldToTime_);
    hBoxToTime->addWidget(lblToEndTime_);
    elementAt(row,1)->setLayout(hBoxToTime);


    //Result
    ++row;
    listResults_ = new WTable(elementAt(row,0));

    // Submit
    ++row;
    WPushButton *submit = new WPushButton("Export",
                      elementAt(row, 0));
    //submit->clicked().connect(this, &Form::submit);
    submit->setMargin(15, Top);

    // Set column widths for label and validation icon
    elementAt(2, 0)->resize(WLength(30, WLength::FontEx), WLength::Auto);
    elementAt(2, 1)->resize(10, WLength::Auto);

    //set up view
    //bxTypeData_->setMargin(5);
    //bxPlace1_->setMargin(5);
//    bxPlace2_->setMargin(5);
//    bxPlace3_->setMargin(5);
    sldFromTime_->setMargin(5);
    sldToTime_->setMargin(5);
    txtFromTime_->setMargin(5);
    txtToTime_->setMargin(5);


    for(int i=0;i<row;i++){
        elementAt(i, 0)->setContentAlignment(AlignRight);
        elementAt(i, 1)->setContentAlignment(AlignLeft);
        //elementAt(i, 2)->resize(100, WLength::Auto);
        elementAt(i,1)->setWidth(300);
        //elementAt(i,1)->setMargin(5);
        //elementAt(i,0)->setContentAlignment();
    }
}

void ChooseOcean::bxPlace1Changed(){
    if(bxPlace.size()<2){
        this->insertRow(1);
        bxPlace.push_back(new WComboBox(elementAt(1,1)));
        bxPlace[1]->setMargin(5);

    }
    bxPlace[1]->clear();
    bxPlace[1]->addItem(" ");
    {
        dbo::Transaction transaction(session);
        WString t = bxPlace[0]->currentText();

        PtrPlaces places1=session.find<Place>().where("fullname <> ?").bind(t);
        for(PtrPlaces::const_iterator i = places1.begin();i!=places1.end();i++){
            bxPlace[1]->addItem((*i)->fullName);
        }
    }

    bxPlace[1]->changed().connect(this, &ChooseOcean::bxPlace2Changed);
    //bxPlace[1]->clicked().connect(this, &ChooseOcean::bxPlace2Changed);

}
void ChooseOcean::bxPlace2Changed(){
    //elementAt(bxPlace.size()+1,1)->setDisabled(false);
    {
        dbo::Transaction transaction(session);
        PtrExps exps1;
        if(bxPlace[0]->currentText()=="All"){
            exps1 = session.find<Passport>();
        }
        else{
            if(bxPlace[1]->currentText()!=" "){
                exps1 = session.find<Passport>().where("place_id = ? or place_id = ?")
                                                    .bind(bxPlace[0]->currentText())
                                                    .bind(bxPlace[1]->currentText());
            }
            else{
                exps1 = session.find<Passport>().where("place_id = ?")
                                                    .bind(bxPlace[0]->currentText());
            }
        }
//        if(exps_.empty())
//            exps_ = exps1;

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
void ChooseOcean::typeDataChanged(){

}
void ChooseOcean::sldFromChanged(){
    std::time_t delta = endTimeUser_.toTime_t() - begTimeSample_.toTime_t();
    delta = delta*sldFromTime_->value()/100;
    WDateTime curr;
    curr.setTime_t(begTimeSample_.toTime_t()+delta);
    begTimeUser_ = curr;
    txtFromTime_ ->setText(curr.toString("dd.MM.yyyy hh:mm:ss"));
    lblToBegTime_->setText(curr.toString("dd.MM.yyyy hh:mm:ss"));
}
void ChooseOcean::sldToChanged(){
    std::time_t delta = endTimeSample_.toTime_t() - begTimeUser_.toTime_t();
    delta = delta*sldToTime_->value()/100;
    WDateTime curr;
    curr.setTime_t(begTimeUser_.toTime_t()+delta);
    endTimeUser_ = curr;
    txtToTime_ ->setText(curr.toString("dd.MM.yyyy hh:mm:ss"));
    lblFromEndTime_->setText(curr.toString("dd.MM.yyyy hh:mm:ss"));
}
