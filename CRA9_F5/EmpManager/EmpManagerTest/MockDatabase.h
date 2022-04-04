#pragma once
#include "../EmpManager/DatabaseInterface.h"

class MockDatabase : public DatabaseInterface {
public:
    MOCK_METHOD(bool, insertItem, (Employ employee), (override));
    MOCK_METHOD(vector<Employ>, selectItems, (enumOptionList option, DatabaseSearchItem item), (override));
    MOCK_METHOD(vector<Employ>, updateItems, (enumOptionList option, DatabaseSearchItem origin, DatabaseSearchItem update), (override));
    MOCK_METHOD(vector<Employ>, deleteItems, (enumOptionList option, DatabaseSearchItem item), (override));
};