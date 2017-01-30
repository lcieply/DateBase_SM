#ifndef SMSYSTEM_H_INCLUDE_
#define SMSYSTEM_H_INCLUDE_

#include <iostream>
#include <exception>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <boost/interprocess/interprocess_fwd.hpp>
#include <boost/interprocess/streams/vectorstream.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
using namespace boost::archive;
using namespace boost::interprocess;

namespace sm {
    typedef allocator<char, managed_shared_memory::segment_manager> CharAllocator;
    typedef basic_string<char, std::char_traits<char>, CharAllocator> SMString;

    class WrongTypeException: public std::exception
    {
    public:
        virtual const char* what() const throw()
        {
            return "Wrong object type";
        }
    };

    class SMSystemException: public std::exception
    {
    public:
        virtual const char* what() const throw()
        {
            return "Shared memory operation not allowed!";
        }
    };

    class NotFoundException: public std::exception
    {
    public:
        virtual const char* what() const throw()
        {
            return "Object not found";
        }
    };

    class SMObject {
    public:
        virtual std::stringstream getSerializedData() = 0;
        virtual ~SMObject();
    };

    class SMContainer {
    public:
        SMString data;
        SMString type;

        SMContainer(SMObject* obj, CharAllocator);

        template<class T>
        void getObject(T& obj) {
            if(strcmp((type).c_str(), typeid(obj).name()) != 0) {
                throw WrongTypeException();
            }
            std::stringstream ss;
            ss << data.c_str();
            text_iarchive ia(ss);
            ia >> obj;

        }
    };

    class SMSystem {
    private:
        managed_shared_memory memory;
        interprocess_mutex* mtx;
        CharAllocator dataAllocator;

    public:
        SMSystem();
        ~SMSystem();
        void remove(const char* key);
        bool contains(const char* key);

        template<class T> void fetch(const char* key, T& object) {
            if(std::is_base_of<SMObject, T>::value) {
                mtx->lock();
                std::pair<SMContainer*, managed_shared_memory::size_type> res;
                try {
                    res = memory.find<SMContainer>(key);
                } catch (interprocess_exception e) {
                    mtx->unlock();
                    throw SMSystemException();
                }
                if(res.first == 0) {
                    mtx->unlock();
                    throw NotFoundException();
                }
                try {
                    res.first->getObject(object);
                } catch (WrongTypeException e) {
                    mtx->unlock();
                    throw e;
                }
                mtx->unlock();
            } else {
                throw WrongTypeException();
            }
        }

        template<class T> void insert(const char* key, T* object) {
            if(std::is_base_of<SMObject, T>::value) {
                mtx->lock();
                try {
                    memory.construct<SMContainer>(key)(object, dataAllocator);
                } catch (interprocess_exception e) {
                    mtx->unlock();
                    throw SMSystemException();
                }
                mtx->unlock();
            } else {
                throw WrongTypeException();
            }
        }

        template<class T> void update(const char* key, T* object) {
            if(std::is_base_of<SMObject, T>::value) {
                mtx->lock();
                try {
                    memory.destroy<SMContainer>(key);
                    memory.construct<SMContainer>(key)(object, dataAllocator);
                } catch (interprocess_exception e) {
                    mtx->unlock();
                    throw SMSystemException();
                }
                mtx->unlock();
            } else {
                throw WrongTypeException();
            }
        }
    };

    template <typename T> class SMType : public SMObject {
    public:
        T val;

        SMType(){}
        SMType(T value) : val(value) {}

        std::stringstream getSerializedData() override {
            std::stringstream data;
            text_oarchive oa(data);
            oa << *this;
            return data;
        }

    private:
        friend class boost::serialization::access;
        template <typename Archive>
        void serialize(Archive &ar, const unsigned int version)
        {
            ar & val;
        }
    };
}

#endif
