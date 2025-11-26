#ifndef MYLOGGER_GLOBAL_H
#define MYLOGGER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MYLOGGER_LIBRARY)
#define MYLOGGER_EXPORT Q_DECL_EXPORT
#else
#define MYLOGGER_EXPORT Q_DECL_IMPORT
#endif

#endif // MYLOGGER_GLOBAL_H
