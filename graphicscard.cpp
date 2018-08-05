#include "graphicscard.h"
#include <QDebug>
#include <QGraphicsDropShadowEffect>

GraphicsCard::GraphicsCard(QWidget *parent) : QWidget(parent)
{
    configureUI();
	configureStyleSheet();
}

void GraphicsCard::configureUI()
{
    setObjectName(QStringLiteral("card"));

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    setMinimumWidth(500);
    setMinimumHeight(200);

    mainLayout = new QVBoxLayout;
    infoLayout = new QHBoxLayout;
    statusLayout = new QVBoxLayout;
    cardName = new QLabel("card name");
    graphHolder = new MinerChart;
    statusLabel = new QLabel("Inactive");
    poolLabel = new QLabel("pool : ");
    speedLabel = new QLabel("speed: ");
    box = new QCheckBox("Start Mining");
    nameHolder = new QWidget;
    nameHolderlayout = new QVBoxLayout;
	infoHolder = new QWidget;
    auto widget = new QWidget;
    widget->setLayout(mainLayout);
    widget->setObjectName("widget");

    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
    effect->setBlurRadius(20);
    effect->setXOffset(0);
    effect->setYOffset(0);
    effect->setColor(QColor(0, 0, 0, 200));
    widget->setGraphicsEffect(effect);

    nameHolder->setLayout(nameHolderlayout);
    nameHolderlayout->addWidget(cardName);
    nameHolderlayout->setContentsMargins(0,0,0,0);
    nameHolderlayout->setSizeConstraint(QLayout::SetFixedSize);

    graphHolder->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    nameHolder->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

    statusLayout->addWidget(statusLabel);
    statusLayout->addWidget(speedLabel);
    statusLayout->addWidget(poolLabel);
    statusLayout->addWidget(box);

    infoLayout->addWidget(graphHolder);
    infoLayout->addLayout(statusLayout);
	infoHolder->setLayout(infoLayout);

    mainLayout->addWidget(nameHolder);
	mainLayout->addWidget(infoHolder);

    auto layout = new QVBoxLayout;
    layout->addWidget(widget);
    setLayout(layout);
}

void GraphicsCard::configureStyleSheet()
{
    this->setStyleSheet("QLabel{color:rgba(200,200,200,1); border: none; border-radius: 2px;}"
                        "#widget{background:rgba(33,33,33,.3); }"
                        "");

}
