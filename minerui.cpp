#include "minerui.h"
#include "constants.h"
#include <QLabel>
#include <QSizeGrip>
#include <QDebug>
#include <QStyledItemDelegate>
#include <QComboBox>

MinerUI::MinerUI(QWidget *parent)
    : QWidget(parent)
{
    configureUI();
    configureConnections();
}

MinerUI::~MinerUI()
{

}

bool MinerUI::isMining()
{
 return mining;
}

void MinerUI::configureUI()
{
    setMinimumWidth(800);

    minerMan = new MinerManager();
    minerMan->initialize();

    settingsMan = new SettingsManager("jahminer.ini");
    fontIcon = new QtAwesome;
    fontIcon->initFontAwesome();

    topLayout = new QHBoxLayout;
    leftLayout = new QVBoxLayout;
    mainLayout = new QVBoxLayout;
    rightLayout = new QVBoxLayout;
    stack = new QStackedWidget;
    dashBtn = new QPushButton;
    settingsBtn = new QPushButton;
    blogBtn = new QPushButton;
    aboutBtn = new QPushButton;
    dashPage = new QWidget;
    settingsPage = new QWidget;
    blogPage = new QWidget;
    aboutPage = new QWidget;
    buttonHolder = new QWidget;
    buttonLayout = new QVBoxLayout;
    scrollArea = new QScrollArea;
    scrollContents = new QWidget;
    scrollLayout = new QVBoxLayout;
    scrollareaLayout = new QVBoxLayout;
    startBtn = new QPushButton("start");

    dashBtn->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    blogBtn->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    settingsBtn->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    aboutBtn->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);

    scrollContents->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Expanding);

    buttonHolder->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Expanding);
    buttonHolder->setFixedWidth(150);

    auto card = new GraphicsCard();
    scrollArea->setWidgetResizable(true);
    scrollContents->setLayout(scrollLayout);
    scrollLayout->addWidget(card);
    scrollLayout->addStretch();
    scrollArea->setWidget(scrollContents);

    setLayout(mainLayout);
    mainLayout->addLayout(topLayout);
    topLayout->addLayout(leftLayout);
    topLayout->addLayout(rightLayout);

    buttonLayout->addWidget(dashBtn);
    buttonLayout->addWidget(settingsBtn);
    buttonLayout->addWidget(blogBtn);
    buttonLayout->addWidget(aboutBtn);
    buttonLayout->addStretch();
    buttonLayout->setSpacing(0);
    buttonLayout->setContentsMargins(0,0,0,0);
    buttonHolder->setLayout(buttonLayout);
    leftLayout->addWidget(buttonHolder);

    rightLayout->addWidget(stack);

    stack->addWidget(dashPage);
    stack->addWidget(settingsPage);
    stack->addWidget(blogPage);
    stack->addWidget(aboutPage);


    auto gripHolder = new QWidget;
    auto gripLayout = new QHBoxLayout;
    auto adminLabel = new QLabel("If miner behaves unexpectedly, restart in admin mode");
    gripHolder->setLayout(gripLayout);
    gripLayout->addWidget(adminLabel);
    gripLayout->addWidget(new QSizeGrip(this));

    mainLayout->addWidget(gripHolder);

    mainLayout->setContentsMargins(1,1,1,1);

    configureDash();

}

void MinerUI::configureDash()
{
    dashLayout = new QVBoxLayout;
    dashPage->setLayout(dashLayout);
    dashLayout->addWidget(scrollArea);

    auto hori = new QHBoxLayout;
    auto horiWid = new QWidget;
    horiWid->setLayout(hori);
    dashLayout->addWidget(horiWid);
    hori->addWidget(startBtn);

}

void MinerUI::configureSettings()
{
        auto settingsWidget = new QWidget;
        auto settingsLaout = new QVBoxLayout;
        //settingsLaout->setContentsMargins(10, 6, 10,4 );
        settingsLaout->setSpacing(10);
        settingsWidget->setLayout(settingsLaout);
        settingsWidget->setObjectName(QStringLiteral("settingsWidget"));



        auto settingsLabel = new QLabel("SETTINGS");
    //	settingsLabel->setAlignment(Qt::AlignHCenter);
        QFont font = settingsLabel->font();
        font.setBold(true);
        settingsLabel->setFont(font);

        auto confirm = new QPushButton("Confirm");
        auto CancelBtn = new QPushButton("Cancel");
        confirm->setObjectName(QStringLiteral("bottomBtn"));
        CancelBtn->setObjectName(QStringLiteral("bottomBtn"));

        connect(confirm, &QPushButton::clicked, [=]() {
            this->saveAndApplySettings();
        });
        connect(CancelBtn, &QPushButton::clicked, [=]() {
            this->restoreSettings();
        });


        auto walletLabel = new QLabel("Wallet Id ");
        auto password = new QLabel("Password ");
        auto poolUrl = new QLabel("Pool URL ");
        auto identifier = new QLabel("Identifier ");
        auto currencyLabel = new QLabel("currency");

        walletLabel->setFont(font);
        password->setFont(font);
        poolUrl->setFont(font);
        identifier->setFont(font);
        currencyLabel->setFont(font);

        walletEdit = new QLineEdit();
        passwordEdit = new QLineEdit();
        poolEdit = new QLineEdit();
        identifierEdit = new QLineEdit();

        QStyledItemDelegate *itemDelegate = new QStyledItemDelegate();
        currency = new QComboBox;
        currency->setItemDelegate(itemDelegate);
        currency->setObjectName(QStringLiteral("currencyBox"));
        auto stringList = QStringList() << "Monero7" << "Aeon" << "BBSCoin" << "Croat" << "Edollar" << "Electroneum" << "Graft" << "Haven" << "Intense" << "Karbo" << "Sumokoin" ;
        currency->setCurrentText("Select Currency");
        currency->addItems(stringList);

        auto walletLayout = new QVBoxLayout;
        auto poolLayout = new QVBoxLayout;
        auto passwordLayout = new QVBoxLayout;
        auto identifierLayout = new QVBoxLayout;
        auto currencyLayout = new QHBoxLayout;
        auto buttonLayout = new QHBoxLayout;

        walletEdit->setObjectName(QStringLiteral("edit"));
        poolEdit->setObjectName(QStringLiteral("edit"));
        passwordEdit->setObjectName(QStringLiteral("edit"));
        identifierEdit->setObjectName(QStringLiteral("edit"));

        walletEdit->setPlaceholderText("Enter Wallet ID");
        poolEdit->setPlaceholderText("Enter Pool URL");
        passwordEdit->setPlaceholderText("Enter Password");
        identifierEdit->setPlaceholderText("Enter Identifier");

        walletLayout->addWidget(walletLabel);
        walletLayout->addWidget(walletEdit);
        poolLayout->addWidget(poolUrl);
        poolLayout->addWidget(poolEdit);
        passwordLayout->addWidget(password);
        passwordLayout->addWidget(passwordEdit);
        identifierLayout->addWidget(identifier);
        identifierLayout->addWidget(identifierEdit);
        buttonLayout->addWidget(confirm);
        buttonLayout->addWidget(CancelBtn);
        currencyLayout->addWidget(currencyLabel);
        currencyLayout->addWidget(currency);

        settingsLaout->addLayout(walletLayout);
        settingsLaout->addLayout(poolLayout);
        settingsLaout->addLayout(passwordLayout);
        settingsLaout->addLayout(identifierLayout);
        settingsLaout->addLayout(currencyLayout);
        settingsLaout->addStretch();
        settingsLaout->addLayout(buttonLayout);

     //   stack->addWidget(settingsWidget);
    //1    settingsLaout->addWidget(new QSizeGrip(this), 0, Qt::AlignBottom | Qt::AlignRight);

        // pass application settings to ui
        walletIdText = settingsMan->getValue("wallet_id", Constants::MINER_DEFAULT_WALLET_ID).toString();
        walletEdit->setText(walletIdText);
        poolText = settingsMan->getValue("pool", Constants::MINER_DEFAULT_POOL).toString();
        poolEdit->setText(poolText);
        passwordText = settingsMan->getValue("password", Constants::MINER_DEFAULT_PASSWORD).toString();
        passwordEdit->setText(passwordText);
        identifierText = settingsMan->getValue("identifier", "").toString();
        identifierEdit->setText(identifierText);

        minerMan->walletId = walletIdText;
        minerMan->poolUrl = poolText;
        minerMan->password = passwordText;
        minerMan->identifier = identifierText;

}

void MinerUI::configureBlog()
{

}

void MinerUI::configureAbout()
{

}

void MinerUI::configureConnections()
{
    connect(dashBtn, &QPushButton::clicked, [=](){
        stack->setCurrentIndex(0);
        emit indexChanged(0);
    });
    connect(settingsBtn, &QPushButton::clicked, [=](){
        stack->setCurrentIndex(1);
        emit indexChanged(1);
    });
    connect(blogBtn, &QPushButton::clicked, [=](){
        stack->setCurrentIndex(2);
        emit indexChanged(2);
    });
    connect(aboutBtn, &QPushButton::clicked, [=](){
        stack->setCurrentIndex(3);
        emit indexChanged(3);
    });

}
void MinerUI::saveAndApplySettings()
{
    walletIdText = walletEdit->text();
    settingsMan->setValue("wallet_id", walletIdText);
    poolText = poolEdit->text();
    settingsMan->setValue("pool", poolText);
    passwordText = passwordEdit->text();
    settingsMan->setValue("password", passwordText);
    identifierText = identifierEdit->text();
    settingsMan->setValue("identifier", identifierText);

    minerMan->walletId = walletIdText;
    minerMan->poolUrl = poolText;
    minerMan->password = passwordText;
    minerMan->identifier = identifierText;

    //restart mining
    if (isMining()) {
        restartMining();
    }
}

void MinerUI::restoreSettings()
{
    settingsMan->setValue("wallet_id", walletIdText);
    settingsMan->setValue("pool", poolText);
    settingsMan->setValue("password", passwordText);
    settingsMan->setValue("identifier", identifierText);
}


void MinerUI::restartMining()
{
    this->stopMining();
    this->startMining();
}

void MinerUI::startMining()
{
    //foreach(card, list) card->startMining();

    startBtn->setText("Stop");
    mining = true;
}

void MinerUI::stopMining()
{
   // foreach(card, list) card->stopMining();

    startBtn->setText("Start");
    mining = false;
}

