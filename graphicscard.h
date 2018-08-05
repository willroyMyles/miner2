#ifndef GRAPHICSCARD_H
#define GRAPHICSCARD_H

#include <QCheckBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>

class GraphicsCard : public QWidget
{
    Q_OBJECT

    enum class MinerConnection{
        Connected,
        Connecting,
        NotConnected,
        Inactive,
    };

public:
    explicit GraphicsCard(QWidget *parent = nullptr);

private:
    QVBoxLayout *mainLayout;
    QVBoxLayout *statusLayout, *nameHolderlayout;
    QHBoxLayout *infoLayout;
    QLabel *cardName;
    QWidget *graphHolder, *nameHolder, *infoHolder;
    QLabel *statusLabel, *poolLabel, *speedLabel;
    QCheckBox *box;



    void configureUI();
	void configureStyleSheet();

signals:

public slots:
};

#endif // GRAPHICSCARD_H
