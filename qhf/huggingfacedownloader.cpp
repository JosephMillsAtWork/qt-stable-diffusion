#include "huggingfacedownloader.h"

HuggingFaceDownloader::HuggingFaceDownloader(QObject *parent)  :
    QObject{parent}
{

    // set_threadCount(sd_get_num_physical_cores() - 1);
}
