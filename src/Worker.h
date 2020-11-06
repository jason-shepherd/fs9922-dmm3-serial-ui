class Worker : public QObject {
    Q_OBJECT
    public slots:
        void doWork();
    signals:
        void dataReady(const std::vector<std::string> &data);
};

class Controller : public QObject {
    Q_OBJECT
    QThread workerThread;
    public:
        Controller() {
            Worker *worker = new Worker;
            worker->moveToThread(&workerThread);
            connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
            connect(this, &Controller::operate, worker, &Worker::doWork);
            connect(worker, &Worker::dataReady, this, &Controller::handleResults);
            workerThread.start();
        }
        ~Controller() {
            workerThread.quit();
            workerThread.wait();
        }
    public slots:
        void handleData(const std::vector<std::string> &);
    signals:
        void operate(const std::vector<std::string> &);
};
