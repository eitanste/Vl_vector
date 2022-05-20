#include <iostream>
#include <algorithm>
#include <stdexcept>

#ifndef VL_VECTOR
#define VL_VECTOR

#define INDEX_ERROR "index is out of range"

#define STATIC_CAPACITY 16
#define INCREASE_FACTOR 1.5


template<class T, size_t StaticCapacity = STATIC_CAPACITY>
class VLVector {
protected:
    size_t _count;
    size_t _capacity;
    size_t _static_threshold;
    T _sdata[StaticCapacity];  // Static Data
    T *_ddata;  // Dynamic Data

    /**
     * used for calculating the new capacity according to the add elements
     * @param additional
     * @return size_t representing the new capacity
     */
    size_t capacity_calc(size_t additional) const{
        double new_size = _count + additional;
        if (new_size <= _static_threshold) {  // no need tho change
            return _static_threshold;
        } else {
            return ((size_t) (INCREASE_FACTOR * new_size));
        }
    }

    /**
     * this method is in charge of manage the the transfer
     * from the static memory to dynamic allocated if needed.
     * it expends the allocated array according to amount of item that inserted
     * @param new_item_count
     * @return a pointer to the correct array with enough free space,
     * for the inserting method to work with
     */
    T *expend_data(size_t new_item_count) {
        size_t new_size = _count + new_item_count;
        size_t new_capacity;
        T *temp;
        T *new_data;

        if (new_size <= _capacity) { // stays the same
            if (_capacity <= _static_threshold) {
                return _sdata;
            } else {
                return _ddata;
            }
        } else {
            new_capacity = capacity_calc(new_item_count);
            _capacity = new_capacity;
            new_data = new T[new_capacity];
            //defines where to copy the data from
            if (_count > _static_threshold) {
                std::copy(_ddata, _ddata + _count,
                          new_data);
                temp = _ddata;
                _ddata = new_data;
                delete[] temp;
            } else {
                std::copy(_sdata, _sdata + _count, new_data);
                _ddata = new_data;
            }
            return _ddata;
        }
    }


    /**
     * reduces the data array according to the elements that were removed.
     * handles the transfer from dynamically allocated array to a static one.
     * @param new_count
     */
    void reduce_data(size_t new_count) {
        if (_count > _static_threshold && new_count <= _static_threshold) {
            std::copy(_ddata, _ddata + new_count, _sdata);
            delete[] _ddata;
            _ddata = nullptr;
            _capacity = _static_threshold;
        }
        _count = new_count;
    }


public:

//******************iterators****************//

    typedef T *iterator;
    typedef const T *const_iterator;

    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;


    // begin & end methods

    iterator begin() {
        if (_count <= _static_threshold) {
            return _sdata;
        } else {
            return _ddata;
        }
    }

    iterator end() {
        if (_count <= _static_threshold) {
            return _sdata + _count;
        } else {
            return _ddata + _count;
        }
    }

    // const begin & end methods
    const_iterator begin() const {
        if (_count <= _static_threshold) {
            return _sdata;
        } else {
            return _ddata;
        }
    }

    const_iterator end() const {
        if (_count <= _static_threshold) {
            return _sdata + _count;
        } else {
            return _ddata + _count;
        }
    }

    const_iterator cbegin() const {
        if (_count <= _static_threshold) {
            return _sdata;
        } else {
            return _ddata;
        }
    }

    const_iterator cend() const {
        if (_count <= _static_threshold) {
            return _sdata + _count;
        } else {
            return _ddata + _count;
        }
    }

    // rbegin & rend methods

    reverse_iterator rend() {
        if (_count <= _static_threshold) {
            return reverse_iterator(_sdata);
        } else {
            return reverse_iterator(_ddata);
        }
    }

    reverse_iterator rbegin() {
        if (_count <= _static_threshold) {
            return reverse_iterator(_sdata + _count);
        } else {
            return reverse_iterator(_ddata + _count);
        }
    }

    // const rbegin & rend methods
    const_reverse_iterator rend() const {
        if (_count <= _static_threshold) {
            return const_reverse_iterator(_sdata);
        } else {
            return const_reverse_iterator(_ddata);
        }
    }

    const_reverse_iterator rbegin() const {
        if (_count <= _static_threshold) {
            return const_reverse_iterator(_sdata + _count);
        } else {
            return const_reverse_iterator(_ddata + _count);
        }
    }

    const_reverse_iterator crend() const {
        if (_count <= _static_threshold) {
            return const_reverse_iterator(_sdata);
        } else {
            return const_reverse_iterator(_ddata);
        }
    }

    const_reverse_iterator crbegin() const {
        if (_count <= _static_threshold) {
            return const_reverse_iterator(_sdata + _count);
        } else {
            return const_reverse_iterator(_ddata + _count);
        }
    }


//******************methods******************//


    /**
     * default ctor
     */
    VLVector() : _count(0), _capacity(StaticCapacity),
                 _static_threshold(StaticCapacity),
                 _ddata(NULL) {
    }

    /**
     * copy ctor
     * @param rhs
     */
    VLVector(const VLVector &rhs) : _count(rhs._count),
                                    _capacity(rhs._capacity),
                                    _static_threshold(StaticCapacity) {

        if (_count <= _static_threshold) {
            _ddata = nullptr;
            std::copy(rhs._sdata, rhs._sdata + rhs._count, _sdata);
        } else {
            _ddata = new T[_capacity];
            if (rhs._count <= rhs._static_threshold) {
                std::copy(rhs._sdata, rhs._sdata + rhs._count, _ddata);
            } else {
                std::copy(rhs._ddata, rhs._ddata + rhs._count, _ddata);
            }
        }
    }

    /**
     * Sequence based Constructor
     * @tparam InputIterator
     * @param first
     * @param last
     */
    template<class InputIterator>
    VLVector(InputIterator first, InputIterator last): VLVector() {
        this->insert(this->begin(), first, last);
    }

    /**
     * single-value ctor
     * @param _count
     * @param v
     */
    VLVector(size_t count, T value) : _static_threshold(StaticCapacity) {
        _capacity = _static_threshold;
        _ddata = nullptr;
        _count = 0;
        T *data;

        if ((count) <= _static_threshold && count >= 0) {
            for (size_t i = 0; i < count; ++i) {
                _sdata[i] = value;
            }
        } else {
            data = expend_data(count);
            for (size_t j = 0; j < count; ++j) {
                data[j] = value;
            }
        }
        _count = count;
    }

    /**
     * assignment operator
     * @param rhs
     * @return *this
     */
    VLVector &operator=(const VLVector &rhs) {
        if (this == &rhs) {
            return *this;
        }

        delete[]_ddata;
        _ddata = nullptr;

        _count = rhs._count;
        _capacity = rhs.capacity();

        if (_count > _static_threshold) {
            _ddata = new T[_capacity];
            for (size_t i = 0; i < _count; ++i) {
                _ddata[i] = rhs.data()[i];
            }
        } else {
            for (size_t i = 0; i < _static_threshold; ++i) {
                _sdata[i] = rhs.data()[i];
            }
        }
        return *this;
    }

    /**
     * d'ctor
     */
    virtual ~VLVector() {
        delete[] _ddata;
    }

    /**
     * @return the amount of elements in the vec
     */
    virtual size_t size() const { return _count; }

    /**
     * @return the capacity of the vec's memory at a given instance
     */
    size_t capacity() const { return _capacity; }

    /**
     * @return true if empty, else - false.
     */
    bool empty() const { return  !(bool)_count; }

    /**
     * checks the validity of the idx.
     * @param idx
     * @return reference of the value at the index
     */
    T &at(size_t idx) {
        if (idx < 0 || idx >= _count) {
            throw std::out_of_range(INDEX_ERROR);
        }
        if (_count > _static_threshold) {
            return _ddata[idx];
        } else {
            return _sdata[idx];
        }
    }

    /**
     * checks the validity of the idx.
     * @param idx
     * @return const reference of the value at the index
     */
    const T &at(size_t idx) const{
        if (idx < 0 || idx >= _count) {
            throw std::out_of_range(INDEX_ERROR);
        }
        if (_count > _static_threshold) {
            return _ddata[idx];
        } else {
            return _sdata[idx];
        }
    }

    /**
     * appends an item to the end of the vec
     * @param item
     */
    virtual void push_back(T item) {
        T *data = expend_data(1);
        data[_count++] = item;
    }

    /**
     * removes the last element of the array
     */
    virtual void pop_back() {
        if (_count > 0) {
            reduce_data(_count - 1);
        }
    }

    /**
     * resets the vec for a default ctor position
     */
    virtual void clear() {
        delete [] _ddata;
        _ddata = nullptr;
        _count = 0;
        _capacity = _static_threshold;
    }

    /**
     * @return a pointer to the vec's data
     */
    T *data() {
        if (_count <= _static_threshold) {
            return _sdata;
        } else {
            return _ddata;
        }
    }

    /**
     * @return a const pointer to the vec's data
     */
    const T *data() const{
        if (_count <= _static_threshold) {
            return _sdata;
        } else {
            return _ddata;
        }
    }

    /**
     * checks if the value is in the vec
     * @param value
     * @return true if it is in the vec, false otherwise
     */
    bool contains(T value) {
        T *data = _sdata;
        if (_count > _static_threshold) {  // figures out were to search
            data = _ddata;
        }
        for (size_t i = 0; i < _count; ++i) {
            if (value == data[i]) {
                return true;
            }
        }
        return false;
    }

    /**
     * insert a certain value to a given location
     * @tparam InputIterator
     * @param position
     * @param value
     * @return an iterator for the position left of the inserted element
     */
    template<class InputIterator>
    InputIterator insert(InputIterator position, T value) {
        T *data;
        size_t insert_idx = std::distance(this->begin(), position);
        
        data = expend_data(1);
        T *ptr = data + _count;
        int transfer_range = _count - insert_idx;
        for (int i = 0; i < transfer_range; ++i) {
            *(ptr) = *(ptr - 1);
            ptr--;
        }
        _count++;
        *ptr = value;

        return data + insert_idx;
    }


    /**
     * insert a certain range of values to a given location
     * @tparam InputIterator
     * @tparam SourceIterator
     * @param position
     * @param first
     * @param last
     * @return an iterator for the position left of the inserted position
     */
    template<class InputIterator, class SourceIterator>
    InputIterator insert(InputIterator position, SourceIterator first,
                         SourceIterator last) {
        T* data;
        size_t transfer_range;
        T* insert_location;
        size_t distance;

        size_t insert_idx = std::distance(this->begin(), position);
        if (insert_idx > _count){
            throw std::out_of_range(INDEX_ERROR);
        }

        int distance_to_check = std::distance(first, last);
        if (distance_to_check < 0) { // checks if the source iterator are valid
            throw std::out_of_range(INDEX_ERROR);
        }
        distance = distance_to_check;

        T *backup = new T[distance];
        for (size_t i = 0; i < distance; ++i) {
            backup[i] = *(first++);
        }

        data = expend_data(distance);
        transfer_range = _count - insert_idx;

        for (size_t i = 0; i < transfer_range; ++i) {
            T tmp = data[_count - i - 1];
            T &tmp2 = data[_count + distance - i - 1];

            tmp2 = tmp;
        }

        insert_location= data + insert_idx;

        for (size_t i = 0; i < distance; ++i) {
             *insert_location++ = backup[i];
        }
        delete []backup;

        _count += distance;
        return iterator(&data[insert_idx]);
    }

    /**
     * erase a given element from the vec
     * @tparam InputIterator
     * @param position
     * @return an iterator for the position left of the removed element
     */
    template<class InputIterator>
    InputIterator erase(InputIterator position) {
//        if()
        InputIterator end = this->end();
        T *ptr = position + 1;
        InputIterator ptr2 = position;

        if (position == end) {
            return position;
        }

        while (ptr != end) {
            *(ptr2++) = *(ptr++);
        }

        reduce_data(_count - 1);
        return position;
    }

    /**
     * erase a given range of elements from the vec
     * @tparam InputIterator
     * @param first
     * @param last
     * @return an iterator for the position left of the
     * removed range of elements
     */
    template<class InputIterator>
    InputIterator erase(InputIterator first, InputIterator last) {
        size_t del_count = std::distance(first,last);

        T *start = first;
        T *next = last;
        InputIterator end = this->end();
        size_t new_count = _count - del_count;

        while (next != end) {
            *(start++) = *(next++);
        }

        reduce_data(new_count);

        return first;
    }

    /**
     * @param idx
     * @return reference of the value of a given index
     */
    T &operator[](size_t idx) {
        return this->data()[idx];
    }

    /**
     * @param idx
     * @return const reference of the value of a given index
     */
    const T &operator[](size_t idx) const {
        return this->data()[idx];
    }

    /**
     *
     * @param rhs
     * @return
     */
    bool operator==(const VLVector &rhs) const {
        const T *this_ptr = this->cbegin();
        const T *rhs_ptr = rhs.begin();

        if (_count != rhs.size()) {
            return false;
        }
        for (size_t i = 0; i < _count; ++i) {
            const T &v1 = *(this_ptr++);
            const T &v2 = *(rhs_ptr++);
            if (!(v1 == v2)) {
                return false;
            }
        }
        return true;
    }

    /**
     *
     * @param rhs
     * @return
     */
    bool operator!=(const VLVector &rhs) const {
        return !(*this == rhs);
    }
};

#endif
