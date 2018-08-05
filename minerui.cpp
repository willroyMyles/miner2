#include "minerui.h"
#include "constants.h"
#include <QLabel>
#include <QSizeGrip>
#include <QDebug>
#include <QStyledItemDelegate>
#include <QComboBox>
#include <QMessageBox>

MinerUI::MinerUI(QWidget *parent)
    : QWidget(parent)
{
    configureUI();
    configureConnections();
    configureStyleSheet();
	configureFontIcons();
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

    startBtn->setObjectName("start");
    dashBtn->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    blogBtn->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    settingsBtn->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    aboutBtn->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);

	dashBtn->setCheckable(true);
	settingsBtn->setCheckable(true);
	blogBtn->setCheckable(true);
	aboutBtn->setCheckable(true);
	dashBtn->setAutoExclusive(true);
	settingsBtn->setAutoExclusive(true);
	blogBtn->setAutoExclusive(true);
	aboutBtn->setAutoExclusive(true);

    scrollContents->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Expanding);

    buttonHolder->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Expanding);
    buttonHolder->setFixedWidth(165);

    auto card = new GraphicsCard();
    scrollArea->setWidgetResizable(true);
    scrollContents->setLayout(scrollLayout);
    scrollLayout->addWidget(card);
    scrollLayout->addWidget(new GraphicsCard());
    scrollLayout->addStretch();
    scrollArea->setWidget(scrollContents);
    scrollContents->setObjectName("cardHolder");

    setLayout(mainLayout);
    mainLayout->addLayout(topLayout);
	topLayout->addLayout(leftLayout);
	topLayout->addWidget(stack);

    auto adminLabel = new QLabel("If miner behaves unexpectedly, restart in admin mode");
    adminLabel->setWordWrap(true);

    buttonLayout->addSpacing(10);
    buttonLayout->addWidget(dashBtn);
    buttonLayout->addWidget(settingsBtn);
    buttonLayout->addWidget(blogBtn);
    buttonLayout->addWidget(aboutBtn);
    buttonLayout->addStretch();
    buttonLayout->addWidget(adminLabel);
    buttonLayout->setSpacing(3);
    buttonLayout->setContentsMargins(15,0,0,5);
    buttonHolder->setLayout(buttonLayout);
    leftLayout->addWidget(buttonHolder);
    buttonHolder->setObjectName("buttonHolder");

    stack->addWidget(dashPage);
    stack->addWidget(settingsPage);
    stack->addWidget(blogPage);
    stack->addWidget(aboutPage);
    stack->setObjectName(QStringLiteral("stack"));
    stack->setContentsMargins(0,0,0,0);

    mainLayout->setContentsMargins(0,0,0,0);
    rightLayout->setContentsMargins(0,0,0,0);
    scrollLayout->setContentsMargins(1,2,1,2);
    topLayout->setContentsMargins(0,0,0,0);
    topLayout->setSpacing(0);

    configureDash();
	configureSettings();
    configureBlog();
    configureAbout();

}

void MinerUI::configureDash()
{
    dashLayout = new QVBoxLayout;
    dashPage->setLayout(dashLayout);
    dashLayout->addWidget(scrollArea);
    dashLayout->setContentsMargins(0,0,0,0);

    auto hori = new QHBoxLayout;
    auto horiWid = new QWidget;
    horiWid->setLayout(hori);
    dashLayout->addWidget(horiWid);
    dashLayout->addSpacing(10);
    hori->addStretch();
    hori->addWidget(startBtn);
    hori->addSpacing(15);
    hori->setContentsMargins(0,0,3,0);
    dashPage->setObjectName(QStringLiteral("page"));
    horiWid->setStyleSheet("background:rgba(1,1,1,0);");

}

void MinerUI::configureSettings()
{
        auto settingsLaout = new QVBoxLayout;
        settingsLaout->setSpacing(10);

        auto settingsLabel = new QLabel("SETTINGS");
    //	settingsLabel->setAlignment(Qt::AlignHCenter);
        QFont font = settingsLabel->font();
        font.setBold(true);
        settingsLabel->setFont(font);

        confirmBtn = new QPushButton("Confirm");
        cancelBtn = new QPushButton("Cancel");
        confirmBtn->setObjectName(QStringLiteral("bottomBtn"));
        cancelBtn->setObjectName(QStringLiteral("bottomBtn"));

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
        buttonLayout->addWidget(confirmBtn);
        buttonLayout->addWidget(cancelBtn);
        currencyLayout->addWidget(currencyLabel);
        currencyLayout->addWidget(currency);

        settingsLaout->addLayout(walletLayout);
        settingsLaout->addLayout(poolLayout);
        settingsLaout->addLayout(passwordLayout);
        settingsLaout->addLayout(identifierLayout);
       // settingsLaout->addLayout(currencyLayout);
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

		settingsPage->setLayout(settingsLaout);
        settingsPage->setObjectName(QStringLiteral("page"));

}

void MinerUI::configureBlog()
{

    blogPage->setObjectName(QStringLiteral("page"));

}

void MinerUI::configureAbout()
{
    aboutPage->setObjectName(QStringLiteral("page"));

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

    connect(this, &MinerUI::indexChanged, [=]( int index)
    {

        switch(index){
        case 0:
            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        }
    });

    connect(confirmBtn, &QPushButton::clicked, [=]() {
        this->saveAndApplySettings();
    });
    connect(cancelBtn, &QPushButton::clicked, [=]() {
        this->resetSettings();
    });

    connect(startBtn, &QPushButton::clicked, [=](){
        if (!mining) {
                    QDir basePath = QDir(QCoreApplication::applicationDirPath());
                    auto xmrPath = QDir::cleanPath(basePath.absolutePath() + QDir::separator() + "xmr-stak/xmr-stak.exe");
                    if (!QFile::exists(xmrPath)) {

        #if defined QT_DEBUG
                        QMessageBox::warning(this, "xmrstak not found!", "xmrstak is missing or hasnt been compiled.");
        #else
                        QMessageBox::warning(this, "xmrstak not found!", "xmrstak is missing");
        #endif
                        return;
                    }
                    startMining();
                }
                else {
                    stopMining();
                }

    });

}

void MinerUI::configureStyleSheet() {
	
    setStyleSheet("*{color:rgba(255,255,255);  }"
                  "#buttonHolder{background:rgba(33,33,33,1); padding: 10px;  }"
        "QScrollArea{ border: 1px solid rgba(130,130,130,1); background: rgba(17,17,17,1); border-radius:1px; }"
		"#cardHolder, #grip {background: rgba(17,17,17,0); padding: 0px; margin: 0px; }"
		"QLabel{ color: rgba(255,255,255,.9); }"
		"QLabel#label{ padding-left: 10px; background:rgba(10,10,10,0); }"
		"QToolButton, #back {border-radius: 1px; background: rgba(20,20,20, 0); color: rgba(250,250,250, 1); border : 0px solid rgba(20,20,20, 1); padding: 4px 6px 4px 6px ; margin-right:3px;}"
		"QScrollBar::handle {background: rgba(40,128, 185,.9); border-radius: 4px; right: 1px; width: 8px;}"
		"QScrollBar{border : 0px solid black; background-color: rgba(32,32,32,.1); width: 8px;padding: 1px;}"
		"QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {background: rgba(200,200,200,0);}"
		"QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical { background: rgba(0,0,0,0); border: 0px solid white;}"
		"QScrollBar::sub-line, QScrollBar::add-line {background: rgba(10,0,0,.1);}"
        "QScrollArea{border:none; background:rgba(0,0,0,0); border-bottom: rgba(0,0,0,.3);}"
        "#start{ padding: 5px 19px 5px 19px; background:rgba(23,23,23,.7); border:1px solid rgba(0,0,0,.1); }"
        "#start:hover{ background : rgba(40,128, 185,.9); }"
        "#bottomBtn{border: 1px solid rgba(40,40,40,0.3); padding: 10px; text-align:center; }"
        "#bottomBtn:hover{background: rgba(20,28, 85,0.5);}"
        "#edit { background: rgba(27,27,27,1); margin-left :2; margin-right : 10px; border : 0px; border-bottom : 1px solid black; }"
		"#currencyBox, #currencyBox:drop-down {background-color: rgba(33,33,33,1); border :0px; border-bottom: 1px solid black; padding-left: 10px; margin-left : 5px; }"
		"#currencyBox QAbstractItemView {background-color: rgba(33,33,33,1); border :0px; border-bottom: 1px solid black; padding-left: 10px; margin-left : 5px; selection-background-color: rgba(40,128, 185,0); }"
		"#currencyBox QAbstractItemView::item:hover {background-color: rgba(40,128,185,1); border :0px;  }"
		"QMessageBox{background:rgba(33,33,33,1);}"
        "QPushButton{background:rgba(38,38,38,0); border: 1px solid rgba(33,33,33,0); height: 2em; text-align:left; }"
        "QPushButton:checked{color:rgba(40,128, 185,0.5); font-size: 4em;}"
        "QPushButton:hover{color:rgba(40,128, 185,0.5);}"
        "#page{background:rgba(53,53,53,1);}"
                  "#cardHolder{background:rgba(53,53,53,1); }");
}

void MinerUI::configureFontIcons()
{
	QVariantMap options;
	options.insert("color", QColor(52, 152, 219));
	options.insert("color-active", QColor(52, 152, 219));
    QFont font;
    font.setBold(true);
    font.setWeight(65);

	//dashBtn->setIcon(fontIcon->icon(fa::play, options));
	dashBtn->setText(tr("DashBoard"));	
    dashBtn->setFont(font);

	//settingsBtn->setIcon(fontIcon->icon(fa::cog, options));
	settingsBtn->setText(tr("Miner Settings"));
    settingsBtn->setFont(font);


    //aboutBtn->setIcon(fontIcon->icon(fa::cog, options));
    aboutBtn->setText(tr("About Us"));
    aboutBtn->setFont(font);

    //blogBtn->setIcon(fontIcon->icon(fa::rss, options));
    blogBtn->setText(tr("Forums"));
    blogBtn->setFont(font);
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

void MinerUI::resetSettings()
{
    walletIdText = settingsMan->getValue("wallet_id", Constants::MINER_DEFAULT_WALLET_ID).toString();
    walletEdit->setText(walletIdText);
    poolText = settingsMan->getValue("pool", Constants::MINER_DEFAULT_POOL).toString();
    poolEdit->setText(poolText);
    passwordText = settingsMan->getValue("password", "").toString();
    passwordEdit->setText(passwordText);
    identifierText = settingsMan->getValue("identifier", "").toString();
    identifierEdit->setText(identifierText);
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

bool MinerUI::shouldAutoMine() {
	return autoStart;
}
