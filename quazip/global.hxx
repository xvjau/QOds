
#ifndef QUAZIP_GLOBAL_HXX_
#define QUAZIP_GLOBAL_HXX_

#include <QtCore/QtGlobal>

#ifdef QUAZIP_BUILDING
	#define QUAZIP_API Q_DECL_EXPORT
#else
	#define QUAZIP_API Q_DECL_IMPORT
#endif

#endif