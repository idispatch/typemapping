#ifndef INCLUDED_OBJECTBUFFER_H
#define INCLUDED_OBJECTBUFFER_H

template<typename T>
class ObjectBuffer {
    char d_buffer[sizeof(T)];
public:
    void reset() {
        T * address = reinterpret_cast<T*>(&d_buffer[0]);
        new (address) T();
    }
    void reset(const T& other) {
        T * address = reinterpret_cast<T*>(&d_buffer[0]);
        new (address) T(other);
    }
    void setNull() {
        T * address = reinterpret_cast<T*>(&d_buffer[0]);
        address->~T();
    }

    T& value() {
        return *reinterpret_cast<T*>(d_buffer);
    }
    const T& value() const {
        return *reinterpret_cast<const T*>(d_buffer);
    }
};

#endif
