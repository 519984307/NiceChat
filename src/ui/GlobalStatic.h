#pragma execution_character_set("utf-8")
#ifndef GLOBALSTATIC_H
#define GLOBALSTATIC_H

#include "QUIHelper.h"
#include "QLogHelper.h"

Q_GLOBAL_STATIC(QUIHelper, uiHelper)
#define UIHelper uiHelper()

Q_GLOBAL_STATIC(QLogHelper, logHelper)
#define LogHelper logHelper()

#define LOGD(data) DLOG(INFO)<<data
#define LOGI(data) LOG(INFO)<<data
#define LOGW(data) LOG(WARNING)<<data
#define LOGE(data) LOG(ERROR)<<data

#endif // GLOBALSTATIC_H
