#include <iostream>
#include "Vector.h"

Vector::Vector(const Value* rawArray, const size_t size, float coef)
:_size(size), _multiplicativeCoef(coef)
{
    reserve(_size);
    for(size_t i = 0; i < _size; i++)
    {
        _data[i] = rawArray[i];
    }
}

Vector::Vector(const Vector& other)
{
    _size = other._size;
    _capacity = other._size;
    _multiplicativeCoef = other._multiplicativeCoef;
    _data = new Value[_capacity];
    for(size_t i = 0; i < _size; i++)
    {
        _data[i] = other._data[i];
    }
}

Vector& Vector::operator=(const Vector& other)
{
    if(this != &other)
    {
        delete[] _data;
        _size = other._size;
        _capacity = other._size;
        _multiplicativeCoef = other._multiplicativeCoef;
        _data = new Value[_capacity];
        for(size_t i = 0; i < _size; i++)
        {
            _data[i] = other._data[i];
        }
    }
    return *this;
}

Vector::Vector(Vector&& other) noexcept
{
    _size = other._size;
    _multiplicativeCoef = other._multiplicativeCoef;
    _capacity = other._size;
    _data = other._data;
    other._data = nullptr;
    other._size = 0;
    other._capacity = 0;
}

Vector& Vector::operator=(Vector&& other) noexcept
{
    if(&other != this)
    {
        delete[] _data;
        _size = other._size;
        _capacity = other._size;
        _multiplicativeCoef = other._multiplicativeCoef;
        _data = other._data;
        other._data = nullptr;
        other._size = 0;
        other._capacity = 0;
        return *this;
    }
    return *this;
}

Vector::~Vector()
{
    delete[] _data;
}

void Vector::_check()
{
    if(_size + 1 > _capacity)
    {
        size_t tmp = _capacity;
        if(tmp == 0)
        {
            tmp = 1 * _multiplicativeCoef;
        }
        while(_size + 1 > tmp)
        {
            tmp *= _multiplicativeCoef;
        }
        reserve (tmp);
    }
}

void Vector::pushBack(const Value& Value)
{
    _check();
    _size++;
    _data[_size - 1] = Value;
}

void Vector::pushFront(const Value& value)
{
    _check();
    _size++;
    for(int i = _size - 1; i > 0; i--)
    {
        _data[i] = _data[i - 1];
    }
    _data[0] = value;
}

void Vector::insert(const Value& value, size_t pos)
{
    insert(&value, 1, pos);
}

void Vector::insert(const Value* values, size_t size, size_t pos)
{
    if(pos >= _size)
    {
        return;
    }
    reserve(_size + size);
    for (size_t i = _size - 1; i >= pos; --i)
    {
        _data[i + size] = _data[i];
    }
    for (size_t i = pos; i < pos + size; i++)
    {
        _data[i] = values[i - pos];
    }
    _size += size;
}

void Vector::insert(const Vector& vector, size_t pos)
{
    insert(vector._data, vector._size, pos);
}

void Vector::popFront()
{
    if (_size > 0){
        for (size_t i = 0; i < _size - 1; i++)
        {
            _data[i] = _data[i + 1];
        }
         _size--;
    }
    else
    {
        throw std::out_of_range("size = 0");
    }
}

void Vector::popBack()
{
    if (_size > 0)
    {
        _size--;
    }
    else
    {
        throw std::out_of_range("size = 0");
    }
}

void Vector::erase(size_t pos, size_t count)
{
    if(pos >= _size)
    {
        throw std::out_of_range("pos >= _size");
        return;
    }
    if((pos + count) > (_size))
    {
        count = _size - pos;
        _size -= count;
        return;
    }
    for(int i = pos; i < _size; i++)
    {
        _data[i] = _data[i + count];
    }
    _size -= count;
}

void Vector::eraseBetween(size_t beginPos, size_t endPos)
{
    if(beginPos >= endPos)
    {
        throw std::out_of_range("beginPos >= endPos");
        return;
    }
    else
    {
        erase(beginPos, endPos - beginPos);
    }
}

size_t Vector::size() const
{
    return _size;
}

size_t Vector::capacity() const
{
    return _capacity;
}

double Vector::loadFactor() const
{
    return double(_size) / double(_capacity);
}

Value& Vector::operator[](size_t idx)
{
    return _data[idx];
}

const Value& Vector::operator[](size_t idx) const
{
    return _data[idx];
}

long long Vector::find(const Value& value) const
{
    for(size_t i = 0; i < _size; i++)
    {
        if(value == _data[i])
        {
            return i;
        }
    }
    return -1;
}

void Vector::reserve(size_t capacity) {
    if (capacity > _capacity)
    {
        Value* tmp = new Value[capacity];
        if (_data != nullptr)
        {
            for (size_t i = 0; i < _size; i++)
            {
                tmp[i] = _data[i];
            }
            delete[] _data;
        }
        _data = tmp;
        _capacity = capacity;
    }
}

void Vector::shrinkToFit()
{
    Value* tmp = new Value[_size];
    if (_data != nullptr)
    {
        for (size_t i = 0; i < _size; ++i)
        {
            tmp[i] = _data[i];
        }
    delete[] _data;
    }
    _data = tmp;
    _capacity = _size;
}

Vector::Iterator Vector::begin() const
{
    return Vector::Iterator(&_data[0]);
}

Vector::Iterator Vector::end() const
{
    return Vector::Iterator(&_data[_size]);
}

Vector::Iterator::Iterator(Value* ptr) : _ptr(ptr)
{
}

Value& Vector::Iterator::operator*()
{
    return *_ptr;
}

const Value& Vector::Iterator::operator*() const
{
    return *_ptr;
}

Value* Vector::Iterator::operator->()
{
    return _ptr;
}

const Value* Vector::Iterator::operator->() const
{
    return _ptr;
}

Vector::Iterator Vector::Iterator:: operator++()
{
    ++_ptr;
    return *this;
}

Vector::Iterator Vector::Iterator::operator++(int)
{
    Vector::Iterator bufIt = *this;
    ++*this;
    return bufIt;
}

bool Vector::Iterator::operator==(const Vector::Iterator& other) const
{
    return _ptr == other._ptr;
}

bool Vector::Iterator::operator!=(const Vector::Iterator& other) const
{
    return !(*this == other);
}