#include <QCommandLineParser>
#include <QCoreApplication>
#include <QDebug>
#include <QProcess>
#include <QString>

#include <process_manager.h>

int main(int argc, char *argv[]) {
  QCoreApplication app(argc, argv);
  QCoreApplication::setApplicationName("SikUli test runner");
  QCoreApplication::setApplicationVersion("1.0");
  QCommandLineParser parser;
  QCommandLineOption test_path(QStringList() << "t"
                                             << "testPath",
                               "Run the test suite by the <path>.", "path");

  QCommandLineOption application_path(
      QStringList() << "a"
                    << "appPath",
      "Run the application for testing. It must have <path>", "path");
  parser.addOptions({test_path, application_path});
  parser.process(app);

  if (parser.values(test_path).isEmpty() ||
      parser.values(application_path).isEmpty()) {
    return 2;
  }

  ProcessManager manager;

  QProcess *app_process =
      manager.LaunchTestedProgram(parser.values(application_path).at(0));

  int result = manager.LaunchTestCase(parser.values(test_path).at(0));

  app_process->waitForFinished(-1);
  qDebug() << result;

  return result;
}
