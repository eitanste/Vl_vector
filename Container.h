template<class T>
class Container {
  T *data = nullptr;
  size_t length = 0;
 public:
  Container(size_t length, const T &value): length(length) {
	data = new T[length];
	std::fill(data, data + length, value);

  }
  Container(const T *first, const T *last) {
    length = last-first;
	data = new T[length];
	std::copy(first, last, data);
  }
  ~Container(){
    if (length > 0){
      delete [] data;
    }
  }
  class Iterator {
	T *m_ptr;
   public:
	typedef std::input_iterator_tag iterator_category;
	typedef size_t difference_type;
	typedef T *pointer;
	typedef T &reference;
	typedef T value_type;

	Iterator(T
	*ptr):
	m_ptr(ptr){}
	const T &operator*() { return *m_ptr; }
	const T *operator->() { return m_ptr; }
	Iterator &operator++() {
	  m_ptr++;
	  return *this;
	}
	Iterator operator++(int) {
	  Iterator tmp = *this;
	  m_ptr++;
	  return tmp;
	}
	friend bool operator==(const Iterator &a, const Iterator &b) {
	  return a
		  .m_ptr == b.m_ptr;
	}
	friend bool operator!=(const Iterator &a, const Iterator &b) {
	  return a
		  .m_ptr != b.m_ptr;
	}
  };

  class ConstIterator{
    T *m_ptr;
   public:
    typedef std::input_iterator_tag iterator_category;
    typedef size_t difference_type;
    typedef const T *pointer;
    typedef const T &reference;
    typedef T value_type;

    ConstIterator(T *ptr):m_ptr(ptr){}
    const T &operator*() { return *m_ptr; }
    const T *operator->() { return m_ptr; }
    ConstIterator &operator++() {
      m_ptr++;
      return *this;
    }
    ConstIterator operator++(int) {
      ConstIterator tmp = *this;
      m_ptr++;
      return tmp;
    }
    friend bool operator==(const ConstIterator &a, const ConstIterator &b) {
      return a
      .m_ptr == b.m_ptr;
    }
    friend bool operator!=(const ConstIterator &a, const ConstIterator &b) {
      return a
      .m_ptr != b.m_ptr;
    }
  };

  typedef Iterator iterator;
  typedef ConstIterator const_iterator;
  iterator begin(){return iterator(data);}
  iterator end(){return iterator(data+length);}
  const_iterator begin() const {return const_iterator(data);}
  const_iterator end() const {return const_iterator(data+length);}
  const_iterator cbegin() const { return const_iterator (data);}
  const_iterator cend() const { return const_iterator (data+length);}

  const T & at(size_t index){
    if (index >= length){
      throw std::out_of_range("Out of range in Container");
    }
    return data[index];
  }
};