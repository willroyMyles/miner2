#include "graphicscard.h"
#include <QDebug>
#include <QGraphicsDropShadowEffect>

GraphicsCard::GraphicsCard(QWidget *parent) : QWidget(parent)
{
    configureUI();
    configureStyleSheet();
}

void GraphicsCard::expand()
{

}

void GraphicsCard::contract()
{

}

void GraphicsCard::setSpeed(double rate)
{
    speedLabel->setText("Speed: " + QString::number(rate) + " H/s");
}

void GraphicsCard::setArmed(bool armed)
{
    this->armed = armed;
        if (!armed) {
            process->stopMining();
            setDotColor(MinerConnection::NotConnected);
        }
}

void GraphicsCard::setDotColor(GraphicsCard::MinerConnection con)
{
    setColor(con);
}

void GraphicsCard::setStarted(bool val)
{
    if (armed && val)
        {
            mining = val;
            if (process != nullptr) {
                process->startMining();
            }
        }
        else {
            if (process != nullptr) {
                if (process->isMining()) {
                    process->stopMining();
                }
            }
        }
}

void GraphicsCard::setHighlight(bool val)
{

}

void GraphicsCard::setMinerProcess(MinerProcess *process)
{
    this->process = process;

        if (process != nullptr) {
            connect(process, &MinerProcess::onMinerChartData, [this](MinerChartData data)
            {
                // set last hash to ui
                this->setSpeed(data.hps);

                // if hps is 0 then it must be connecting
                // set pool color to orange
                if (data.connected)
                    this->setDotColor(MinerConnection::Connected);
                else
                    this->setDotColor(MinerConnection::Connecting);

                if (data.hps != 0) {
                    if (this->info->data.size() > 100)
                        this->info->data.removeFirst();
                    this->info->data.append(data);
                    this->info->repaint();
                }
            });

            connect(process, &MinerProcess::minerStatusChanged, [this](MinerStatus status)
            {
                switch (status)
                {
                case MinerStatus::Idle:
                    this->setDotColor(MinerConnection::Inactive);
                    break;
                case MinerStatus::Starting:
                    this->setDotColor(MinerConnection::Connecting);
                    break;
                case MinerStatus::Mining:
                    this->setDotColor(MinerConnection::Connected);
                    break;
                case MinerStatus::Stopping:
                    this->setDotColor(MinerConnection::NotConnected);
                    break;
                }
            });
        }
}

void GraphicsCard::startMining()
{
    if (armed) {
        process->startMining();
        setHighlight(true);
    }
}

void GraphicsCard::stopMining()
{
    process->stopMining();
    setColor(MinerConnection::Inactive);
    setHighlight(false);
}

void GraphicsCard::setColor(MinerConnection status) {
    switch (status) {
    case MinerConnection::Connected:
        color.setRgb(0, 120, 0, 255);
        statusLabel->setText(tr("Connected"));
        break;
    case MinerConnection::Connecting:
        color.setRgb(255, 120, 70, 255);
        statusLabel->setText(tr("Connecting"));
        break;
    case MinerConnection::NotConnected:
        color.setRgb(170, 1, 2, 255);
        statusLabel->setText(tr("NotConnected"));
        break;
    case MinerConnection::Inactive:
        color.setRgb(240, 240, 240, 255);
        statusLabel->setText(tr("Inactive"));
        break;
    }

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

void GraphicsCard::configureConnections()
{
    connect(box,&QCheckBox::stateChanged,[=](int checkBoxState){
        switch(checkBoxState){
        case 1: // unchecked
            state = CardState::Disabled;
            emit cardStatus(CardState::Disabled);
            break;
        case 2: // partially checked
            break;
        case 3: // checked
            state = CardState::Enabled;
            emit cardStatus(CardState::Enabled);
            break;
        }
    });


}

void GraphicsCard::configureStyleSheet()
{
    this->setStyleSheet("QLabel{color:rgba(200,200,200,1); border: none; border-radius: 2px;}"
                        "#widget{background:rgba(33,33,33,.3); }"
                        "");

}
