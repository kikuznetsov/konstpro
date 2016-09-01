#include "cvpage.h"
#include <Wt/WHBoxLayout>

CvPage::CvPage(WContainerWidget *parent):WContainerWidget(parent){

    downloadCv = new WPushButton("Download full CV in pdf");
    downloadCv->setMinimumSize(200,35);
    downloadCv->setMaximumSize(200,35);
    downloadCv->setStyleClass("btn-primary");
    downloadCv->setLink(Wt::WLink("/pdf.pdf"));

    briefCv  = new Content("briefCv.xhtml",parent);

    WHBoxLayout* hBox = new WHBoxLayout();
    hBox->addWidget(downloadCv);
    hBox->addWidget(briefCv);

    this->setLayout(hBox);

}
