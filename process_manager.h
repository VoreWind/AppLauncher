#ifndef PROCESS_MANAGER_H
#define PROCESS_MANAGER_H

#include <QObject>

class QProcess;

class ProcessManager : public QObject {
  Q_OBJECT
public:
  explicit ProcessManager(QObject *parent = 0);
  int LaunchTestCase(const QString &test_path);
  QProcess *LaunchTestedProgram(const QString &program_path);
signals:

public slots:
private:
  static const QString kSikuliPath;
  static const QString kSikuliCasesPath;
  QProcess *test_process_;
};

#endif // PROCESS_MANAGER_H
