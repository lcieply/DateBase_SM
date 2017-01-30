#include "SMSystem.h"
using namespace sm;

//==========SMSystem===========

SMSystem::SMSystem() : memory(open_only,"SMSystem"), dataAllocator(memory.get_segment_manager()) {
    mtx = memory.find<interprocess_mutex>("mtx").first;
}

SMSystem::~SMSystem() {
}

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

SMObject::~SMObject() {

}

//========SMContainer==========

SMContainer::SMContainer(SMObject *obj, CharAllocator dataAllocator) :
        data(dataAllocator), type(typeid(*obj).name(), dataAllocator)  {
    data.insert(0, obj->getSerializedData().str().c_str());
}
