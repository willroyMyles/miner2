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
//	configureStyleSheet();
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
	topLayout->addWidget(stack);

    buttonLayout->addWidget(dashBtn);
    buttonLayout->addWidget(settingsBtn);
    buttonLayout->addWidget(blogBtn);
    buttonLayout->addWidget(aboutBtn);
    buttonLayout->addStretch();
    buttonLayout->setSpacing(0);
    buttonLayout->setContentsMargins(0,0,0,0);
    buttonHolder->setLayout(buttonLayout);
    leftLayout->addWidget(buttonHolder);

   // rightLayout->addWidget(stack);

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

	mainLayout->addWidget(startBtn);
    mainLayout->addWidget(gripHolder);

    mainLayout->setContentsMargins(1,1,1,1);

    configureDash();
	configureSettings();

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
        auto settingsLaout = new QVBoxLayout;
        settingsLaout->setSpacing(10);
       
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

		settingsPage->setLayout(settingsLaout);

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

void MinerUI::configureStyleSheet() {
	

	setStyleSheet("*{color:rgba(255,255,255); background:rgba(33,33,33,1);}"
		"QGroupBox, #settingsWidget{ background: rgba(33,33,33,1); margin:0px; padding : 0px; border: 0px solid black; }"
		"QScrollArea, #cardHolder{ border: 1px solid rgba(130,130,130,0); background: rgba(17,17,17,0); border-radius:1px; }"
		"#cardHolder, #grip {background: rgba(17,17,17,0); padding: 0px; margin: 0px; }"
		"QLabel{ color: rgba(255,255,255,.9); }"
		"QLabel#label{ padding-left: 10px; background:rgba(10,10,10,0); }"
		"QToolButton, #back {border-radius: 1px; background: rgba(20,20,20, 0); color: rgba(250,250,250, 1); border : 0px solid rgba(20,20,20, 1); padding: 4px 6px 4px 6px ; margin-right:3px;}"
		//     "QToolButton:hover{background: rgba(48,48,48, 1);}"
		"QScrollBar::handle {background: rgba(40,128, 185,.9); border-radius: 4px; right: 1px; width: 8px;}"
		"QScrollBar{border : 0px solid black; background-color: rgba(32,32,32,.1); width: 8px;padding: 1px;}"
		"QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {background: rgba(200,200,200,0);}"
		"QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical { background: rgba(0,0,0,0); border: 0px solid white;}"
		"QScrollBar::sub-line, QScrollBar::add-line {background: rgba(10,0,0,.1);}"
		"QPushButton{ background: rgba(20,20,20,1); border: 1px solid rgba(10,10,10,1); border-radius: 1px;  color: rgba(255,255,255,.9); padding : 3px 9px 3px 9px; }"
		""
		"#startBtn{ padding: 9px 19px 9px 19px; background:rgba(23,23,23,.7); border:1px solid rgba(0,0,0,0);}"
		"#startBtn:hover, QToolButton:hover, #back:hover { background : rgba(40,128, 185,.9); }"
		//   "QScrollArea{background: rgba(23,23,23,1); border: 0px solid black; }"
		"#toolBar{ background: rgba(40,128, 185,0); border: 1px solid rgba(10,0,0,0); }"
		//"#back{ background: rgba(40,128, 185,0); border: 0px solid rgba(40,40,40,0.3); }"
		"#bottomBtn{border: 1px solid rgba(40,40,40,0.3); padding: 10px; }"
		"#bottomBtn:hover{background: rgba(40,128, 185,0.5);}"
		"#edit { background: rgba(17,17,17,1); margin-left :10; margin-right : 10px; border : 0px; border-bottom : 1px solid black; }"
		"#currencyBox, #currencyBox:drop-down {background-color: rgba(33,33,33,1); border :0px; border-bottom: 1px solid black; padding-left: 10px; margin-left : 5px; }"
		"#currencyBox QAbstractItemView {background-color: rgba(33,33,33,1); border :0px; border-bottom: 1px solid black; padding-left: 10px; margin-left : 5px; selection-background-color: rgba(40,128, 185,0); }"
		"#currencyBox QAbstractItemView::item:hover {background-color: rgba(40,128,185,1); border :0px;  }"
		"QMessageBox{background:rgba(33,33,33,1);}"
		"QPushButton{background:rgba(33,33,33,0); border: 1px solid rgba(33,33,33,.5); height: 2em; Text-align:left; }"
		"QPushButton:checked{background:rgba(33,83,233,0);}"
		"QPushButton:hover{background:rgba(10,50,200);}"
		"");
}

void MinerUI::configureFontIcons()
{
	QVariantMap options;
	options.insert("color", QColor(52, 152, 219));
	options.insert("color-active", QColor(52, 152, 219));

	dashBtn->setIcon(fontIcon->icon(fa::play, options));
	dashBtn->setText(tr("DashBoard"));
	

	settingsBtn->setIcon(fontIcon->icon(fa::cog, options));
	settingsBtn->setText(tr("Miner Settings"));
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

bool MinerUI::shouldAutoMine() {
	return autoStart;
}
