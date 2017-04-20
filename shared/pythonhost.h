#ifndef PYTHONHOST_H
#define PYTHONHOST_H

#include <Python.h>

#include <QObject>
#include <QString>
#include <QDir>

#include "PythonQt.h"
#include "PythonQt_QtAll.h"

#include "pythonqt/pythonqtpytson.h"
#include "pythonqt/eventfilterobject.h"

#include <QDebug>

#if defined(Q_OS_WIN)
  #define INTERPRETER "python.exe"
#else
  //mac + linux
  #define INTERPRETER "python"
#endif

class PythonHost {
  public:
    typedef struct {
      const char* name;
      PyObject* (*initfunc)(void);
    } pythoninittab;

    PythonHost();
    ~PythonHost();

    virtual bool init(const QDir& basedir, QString& error);
    virtual void shutdown();
  protected:
    bool setupDirectories(QString& error);
    bool isReady();

    bool setModuleSearchpath(QString& error);

    bool setSysPath(QString& error);
    QString formatError(const QString& fallback);

    void initPythonQt();

    QList<pythoninittab> m_inittabs;
  private:
    QDir m_scriptsdir;
    QDir m_includedir;
    QDir m_libdir;
    QDir m_dynloaddir;
    QDir m_sitepackdir;
    QDir m_base;
    wchar_t* m_interpreter;
    /*PyObject* m_pluginmod;
    PyObject* m_pmod;
    PyObject* m_pyhost;
    PyObject* m_callmeth;*/
    PyObject* m_trace;
    bool m_inited;
};

#endif // PYTHONHOST_H
