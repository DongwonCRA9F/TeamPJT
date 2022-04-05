#pragma once
#include "../EmpManager/DatabaseInterface.h"

class MockDatabase {
public:
    static MockDatabase& getInstance() {
        static MockDatabase instance;
        return instance;
    }
    MOCK_METHOD(bool, insertItem, (Employ employee));
    MOCK_METHOD(vector<Employ>, selectItems, (enumOptionList option, DatabaseSearchItem item));
    MOCK_METHOD(vector<Employ>, updateItems, (enumOptionList option, DatabaseSearchItem origin, DatabaseSearchItem update));
    MOCK_METHOD(vector<Employ>, deleteItems, (enumOptionList option, DatabaseSearchItem item));
};