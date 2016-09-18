#include "cvpage.h"
#include <Wt/WHBoxLayout>
#include <Wt/WVBoxLayout>
#include <Wt/WGroupBox>

CvPage::CvPage(WContainerWidget *parent):WContainerWidget(parent){

    downloadCv_ = new WPushButton("Download full CV");
    //downloadCv_->setMinimumSize(100,35);
    //downloadCv_->setMaximumSize(200,35);
    downloadCv_->setStyleClass("btn-primary");
    downloadCv_->setLink(Wt::WLink("pdfs/kkuznetsov_cv_faculty.pdf"));

    briefCv_  = new Content("briefCv.xhtml",parent);
    briefCv_ -> setMinimumSize(100,300);

    ava_ = new WImage(WLink("images/konst.png"));
    //ava_->setMaximumSize(200,200);
    ava_->setMinimumSize(200,200);

    WHBoxLayout* hBox = new WHBoxLayout();
    WGroupBox* grBox = new WGroupBox();
    grBox->setMaximumSize(350,350);
    grBox->setMinimumSize(200,250);
    WVBoxLayout* vBox = new WVBoxLayout();
        vBox->addWidget(ava_);
        vBox->addWidget(downloadCv_);
        vBox->addWidget(new WText("e-mail:kost.kuznetsov@gmail.com"));
    //vBox->setResizable(0,false,35);
    //vBox->setResizable(1,false,200);

    grBox->setLayout(vBox);
    //grBox->setWidth(200);
    //grBox->setHeight(250);
    hBox->setContentsMargins(10,10,10,10);


    hBox->addWidget(grBox);
    hBox->addWidget(briefCv_);


    this->setLayout(hBox);

}
