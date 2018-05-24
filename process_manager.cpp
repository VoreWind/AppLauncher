#include "process_manager.h"

#include <QDebug>
#include <QProcess>

const QString ProcessManager::kSikuliPath = "/home/sergef/Downloads/sikuli/";
const QString ProcessManager::kSikuliCasesPath = "/home/sergef/SikUlicases/";

ProcessManager::ProcessManager(QObject *parent) : QObject(parent) {
  test_process_ = new QProcess(this);
}

int ProcessManager::LaunchTestCase(const QString &test_path) {
  const QString sikuli_exe_path = kSikuliPath + "runsikulix";
  const QString init_arms_test_case_path = test_path;

  QStringList init_arms_test_arguments = {"-r", init_arms_test_case_path};

  test_process_->start(sikuli_exe_path, init_arms_test_arguments);

  test_process_->waitForFinished(-1);
  QByteArray output = test_process_->readAllStandardOutput();
  qDebug() << output;

  if (output.contains("stopped with error in line")) {
    return 1;
  }
  return 0;
}

QProcess *ProcessManager::LaunchTestedProgram(const QString &program_path) {
  QProcess *tested_program = new QProcess(this);

  connect(test_process_, SIGNAL(finished(int, QProcess::ExitStatus)),
          tested_program, SLOT(kill()));
  tested_program->start(program_path);
  tested_program->waitForStarted();
  return tested_program;
}
