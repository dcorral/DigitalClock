#include <QApplication>
#include <QLabel>
#include <QMainWindow>
#include <QSoundEffect>
#include <QTime>
#include <QTimer>
#include <QVBoxLayout>

const int workCountdownMinutes = 30;
const int restCountdownMinutes = 5;
const int alarmDurationSeconds = 10;

class MainWindow : public QMainWindow {
        Q_OBJECT

    public:
        bool rest = true;
        MainWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
            countdownTime = QTime(0, workCountdownMinutes, 0);
            timerLabel = new QLabel(countdownTime.toString("mm:ss"), this);
            timerLabel->setAlignment(Qt::AlignCenter);
            timerLabel->setStyleSheet("font-size: 150px; color: cyan");

            timerLabel->setMouseTracking(true);
            timerLabel->setAttribute(Qt::WA_Hover);
            connect(timerLabel, &QLabel::linkActivated, this,
                    &MainWindow::resetTimer);

            QVBoxLayout *layout = new QVBoxLayout;
            layout->addWidget(timerLabel);

            QWidget *centralWidget = new QWidget(this);
            centralWidget->setLayout(layout);
            setCentralWidget(centralWidget);

            timer = new QTimer(this);
            connect(timer, &QTimer::timeout, this, &MainWindow::updateTime);
            timer->start(1000);

            alarmSound = new QSoundEffect(this);
            alarmSound->setSource(QUrl("qrc:/alarm.wav"));
            alarmSound->setLoopCount(QSoundEffect::Infinite);
            alarmSound->setVolume(0.25f);

            connect(timerLabel, &QLabel::linkActivated, this,
                    &MainWindow::resetTimer);
            timerLabel->installEventFilter(this);
        }

    protected:
        bool eventFilter(QObject *watched, QEvent *event) override {
            if (watched == timerLabel &&
                event->type() == QEvent::MouseButtonPress) {
                resetTimer();
                this->rest = !this->rest;
                return true;
            }
            return QMainWindow::eventFilter(watched, event);
        }

    private slots:
        void updateTime() {
            if (countdownTime > QTime(0, 0, 0)) {
                countdownTime = countdownTime.addSecs(-1);
                timerLabel->setText(countdownTime.toString("mm:ss"));
            } else {
                if (!alarmPlaying) {
                    alarmSound->play();
                    alarmPlaying = true;
                    QTimer::singleShot(alarmDurationSeconds * 1000, this,
                                       &MainWindow::stopAlarm);
                }
            }
        }

        void resetTimer() {
            int _time =
                (this->rest) ? restCountdownMinutes : workCountdownMinutes;
            countdownTime = QTime(0, _time, 0);
            timerLabel->setText(countdownTime.toString("mm:ss"));
            if (alarmPlaying) {
                stopAlarm();
            }
        }

        void stopAlarm() {
            alarmSound->stop();
            alarmPlaying = false;
        }

    private:
        QLabel *timerLabel;
        QTimer *timer;
        QTime countdownTime;
        QSoundEffect *alarmSound;
        bool alarmPlaying = false;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.setWindowTitle("Digital Clock Countdown");
    mainWindow.resize(400, 300);
    mainWindow.setStyleSheet("background-color: black");
    mainWindow.show();

    return app.exec();
}

#include "main.moc"
