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
    sldFromTime_->changed().connect(this, &ChooseOcean::sldChanged);


    //set up view of "from time"
    //sldFromTime_->setEnabled(false);
    sldFromTime_->setToolTip("Move slider to specify START time of records");
    sldFromTime_->setWidth(200);
    WHBoxLayout* hBoxFromTime = new WHBoxLayout();
    WText* d= new WText("01.01.1987");
    WText* d1= new WText("01.01.1987");
    hBoxFromTime->addWidget(d);
    hBoxFromTime->addWidget(sldFromTime_);
    hBoxFromTime->addWidget(d1);
    elementAt(row,1)->setLayout(hBoxFromTime);

    // To Time
    ++row;
    txtToTime_ = new WText("01/01/1987 00:00:00", elementAt(row, 1));
    label = new WLabel("<b>To time</b>", elementAt(row, 0));
    ++row;
    sldToTime_ = new WSlider();
    sldToTime_->changed().connect(this, &ChooseOcean::sldChanged);

    //set up view of "to time"
    sldToTime_->setWidth(200);
    sldToTime_->setValue(100);
    sldToTime_->setToolTip("Move slider to specify FINISH time of records");
    WHBoxLayout* hBoxToTime = new WHBoxLayout();
    d= new WText("01.01.1987");
    d1= new WText("01.01.1987");
    hBoxToTime->addWidget(d);
    hBoxToTime->addWidget(sldToTime_);
    hBoxToTime->addWidget(d1);
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
        //exps_.
        //PtrPlaces places2 = session.find<Place>().where("fullname = ?").bind("IZM");
        PtrExps exps1 = session.find<Passport>();//.where("place_id = ?").bind(bxPlace[0]->currentText());
        if(exps_.empty())
            exps_ = exps1;
        //tr.commit();
    }
    std::cout<<"sddsf"<<std::endl;
}
void ChooseOcean::typeDataChanged(){

}
void ChooseOcean::sldChanged(){

}
