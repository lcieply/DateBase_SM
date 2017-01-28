#include "SMSystem.h"

//==========SMSystem===========

SMSystem::SMSystem() {
    memory = managed_shared_memory(open_only,"SMSystem");
    mtx = memory.find<interprocess_mutex>("mtx").first;
}

SMSystem::~SMSystem() {}

void SMSystem::remove(const char *key) {
    mtx->lock();
    try {
        memory.destroy<SMContainer>(key);
    } catch (interprocess_exception e) {
        mtx->unlock();
        throw SMSystemException();
    }
    mtx->unlock();
}

bool SMSystem::contains(const char *key) {
    mtx->lock();
    std::pair<SMContainer*, managed_shared_memory::size_type> res;
    try {
        res = memory.find<SMContainer>(key);
    } catch (interprocess_exception e) {
        mtx->unlock();
        throw SMSystemException();
    }
    mtx->unlock();

    return (res.first != 0);
}

//==========SMObject===========

SMObject::~SMObject() {}

//========SMContainer==========

SMContainer::SMContainer(SMObject *obj) {
    type = typeid(*obj).name();
    data = obj->getSerializedData();
}
