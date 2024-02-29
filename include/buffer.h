#pragma once
typedef char value_type;

class CircularBuffer {
  value_type *buffer;
  int head, tail, len, totallen;
public:
	int get_length() const;
	int get_current_length() const;
	int get_head() const;
	int get_tail() const;
	value_type* get_buffer() const;
	// Default constructor
	CircularBuffer();

	// Destructor
	~CircularBuffer();

	// Copy constructor
	CircularBuffer(const CircularBuffer& cb);

	// Constructor with specified capacity
	explicit CircularBuffer(int capacity);

	// Constructor with specified capacity, completely filled with elem
	CircularBuffer(int capacity, const value_type& elem);

	// Index access operators (non-const and const versions)
	value_type& operator[](int i);
	const value_type& operator[](int i) const;

	// Safe index access operators that throw an exception on invalid index
	value_type& at(int i);
	const value_type& at(int i) const;

	// Return a reference to the first element
	value_type& front();
	const value_type& front() const;

	// Return a reference to the last element
	value_type& back();
	const value_type& back() const;

	// Linearizes the buffer, moving the first element to the beginning of the allocated memory
	// Returns a pointer to the first element
	value_type* linearize();

	// Checks if the buffer is linearized
	bool is_linearized() const;

	// Rotates the buffer so that the element at index new_begin will be at index 0
	void rotate(int new_begin);

	// Returns the number of elements stored in the buffer
	int size() const;

	// Checks if the buffer is empty
	bool empty() const;

	// Checks if the buffer is full (size equals capacity)
	bool full() const;

	// Returns the number of free slots in the buffer
	int reserve() const;

	// Returns the capacity of the buffer
	int capacity() const;

	// Sets the capacity of the buffer
	void set_capacity(int new_capacity);

	// Changes the size of the buffer
	// If the new size is larger, the new elements are filled with the item value
	void resize(int new_size, const value_type& item = value_type());

	// Assignment operator
	CircularBuffer& operator=(const CircularBuffer& cb);

	// Swaps the content of the buffer with the content of cb
	void swap(CircularBuffer& cb);

	// Adds an element to the end of the buffer
	// If the current size of the buffer is equal to its capacity, the first element is overwritten (buffer is circular)
	void push_back(const value_type& item = value_type());

	// Adds a new element before the first element of the buffer
	// Similar to push_back, may overwrite the last element of the buffer
	void push_front(const value_type& item = value_type());

	// Removes the last element of the buffer
	void pop_back();

	// Removes the first element of the buffer
	void pop_front();

	// Inserts an element at the specified position
	void insert(int pos, const value_type& item = value_type());

	// Removes elements from the buffer in the range [first, last)
	void erase(int first, int last);

	// Clears the buffer
	void clear();
};

// Equality operator
bool operator==(const CircularBuffer & a, const CircularBuffer & b);
// Inequality operator
bool operator!=(const CircularBuffer & a, const CircularBuffer & b);
