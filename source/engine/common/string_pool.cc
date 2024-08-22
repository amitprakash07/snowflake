#include "hashed_string.h"
#include "string_pool.h"

using namespace engine;

SharedPointer<StringPool> StringPool::mStringPool;

SharedPointer<StringPool> StringPool::getStringPool() {
  if (mStringPool.isNull()) {
    /*mStringPool = EngineController::GameEngine::isEngineInitialized() ?
            new
       (EngineController::GameEngine::getMemoryManager()->__alloc(sizeof(StringPool)))
       StringPool() :
    */
    SharedPointer<StringPool> tempPool(new StringPool(), "StringPool");
    mStringPool = tempPool;
  }
  return mStringPool;
}  // getStringPool

StringPool::~StringPool() {
  while (mStringList.size() != 0) {
    delete (mStringList.at(0).mString);
    mStringList.at(0).mString = nullptr;
    mStringList.erase(mStringList.begin());
  }
}

StringPool::StringPool() { mStringList.reserve(200); }

char* StringPool::findString(char* i_string) {
  if (i_string != nullptr) {
    size_t tempStringLength = strlen(i_string);
    bool isFound = false;

    for (size_t i = 0; i < mStringList.size(); i++) {
      if (utils::StringHash(mStringList[i].getAsChar()) ==
          utils::StringHash(i_string))
        return mStringList[i].getAsChar();
    }
    return (addString(i_string));
  }
  return nullptr;
}  // end find function

char* StringPool::addString(char* i_String) {
  typedefs::String tempString = typedefs::String(i_String);
  mStringList.push_back(tempString);
  return tempString.mString;
}
