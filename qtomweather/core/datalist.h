#ifndef DATALIST_H
#define DATALIST_H
////////////////////////////////////////////////////////////////////////////////
#include <vector>
#include "data.h"
////////////////////////////////////////////////////////////////////////////////
namespace Core{
    class DataList {
        std::vector <Data> *data_array;
        public:
            DataList();
            void AddData(Data data);
            virtual ~DataList();
    };
} // namespace Core
////////////////////////////////////////////////////////////////////////////////
#endif // DATALIST_H

