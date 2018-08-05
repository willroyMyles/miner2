#include "graphicscard.h"
#include <QDebug>

GraphicsCard::GraphicsCard(QWidget *parent) : QWidget(parent)
{
    configureUI();
	configureStyleSheet();
}

void GraphicsCard::configureUI()
{
    setObjectName(QStringLiteral("card"));
    setStyleSheet("#card{background:rgba(200,200,2,1); border: 1px solid red; border-radius: 2px;}");

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    setMinimumWidth(500);
    setMinimumHeight(200);

    mainLayout = new QVBoxLayout;
    infoLayout = new QHBoxLayout;
    statusLayout = new QVBoxLayout;
    cardName = new QLabel("card name");
    graphHolder = new QWidget;
    statusLabel = new QLabel("Inactive");
    poolLabel = new QLabel("pool : ");
    speedLabel = new QLabel("speed: ");
    box = new QCheckBox("Start Mining");
    nameHolder = new QWidget;
    nameHolderlayout = new QVBoxLayout;
	infoHolder = new QWidget;

    nameHolder->setLayout(nameHolderlayout);
    nameHolderlayout->addWidget(cardName);
    nameHolderlayout->setContentsMargins(0,0,0,0);
    nameHolderlayout->setSizeConstraint(QLayout::SetFixedSize);


    graphHolder->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    nameHolder->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);


    setLayout(mainLayout);
    statusLayout->addWidget(statusLabel);
    statusLayout->addWidget(speedLabel);
    statusLayout->addWidget(poolLabel);
    statusLayout->addWidget(box);


    infoLayout->addWidget(graphHolder);
    infoLayout->addLayout(statusLayout);
	infoHolder->setLayout(infoLayout);

    mainLayout->addWidget(nameHolder);
	mainLayout->addWidget(infoHolder);
   // mainLayout->addLayout(statusLayout);
}

void GraphicsCard::configureStyleSheet()
{
	infoHolder->setStyleSheet("background:rgba(33,33,33,1);");
}
