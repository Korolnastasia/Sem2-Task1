#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include "buffer.h"
typedef char value_type;

CircularBuffer::CircularBuffer() {
	this->len = 0;
	this->totallen = 0;
	this->tail = 0;
	this->head = 0;
	this->buffer = new value_type[0];
}
CircularBuffer::~CircularBuffer() {
	delete[] buffer;
}
CircularBuffer::CircularBuffer(const CircularBuffer& cb) :
	CircularBuffer(cb.totallen) {
	for (int i = 0; i < cb.len; i++) {
		buffer[i] = cb.buffer[i];
	}
	len = cb.len;
}

CircularBuffer::CircularBuffer(int capacity) {
	this->buffer = new value_type[capacity];
	this->len = 0;
	this->totallen = capacity;
	this->tail = 0;
	this->head = 0;
}

//������������ ����� �������� �������, ������� ��������� ��� ��������� elem.
CircularBuffer::CircularBuffer(int capacity, const value_type& elem) {
	buffer = new value_type[capacity];
	this->totallen = capacity;
	this->len = capacity;
	for (int i = 0; i < capacity; i++) {
		buffer[i] = elem;
	}
	this->tail = 0;
	this->head = 0;
}

int CircularBuffer::get_length() const { return this->totallen; }
int CircularBuffer::get_current_length() const{ return this->len; }
int CircularBuffer::get_head() const { return this->head; }
int CircularBuffer::get_tail() const { return this->tail; }
value_type* CircularBuffer::get_buffer() const { return this->buffer; }

//������ �� �������. �� ��������� ������������ �������.
value_type& CircularBuffer::operator[](int i) {
	return buffer[(head + i) % totallen];
}
const value_type& CircularBuffer::operator[](int i) const {
	return buffer[(head + i) % totallen];
}

//������ �� �������. ������ ������� ���������� � ������ ��������� �������.
value_type& CircularBuffer::at(int i) {
	try
	{
		if (i >= 0 && i < len && ((tail == head) || (tail > head && head + i < tail) || (tail < head && (head + i < totallen || head + i - totallen < tail))))
			return buffer[(head + i) % totallen];
		throw "Invalid index";
	}
	catch (const char* error_message)
	{
		std::cout << error_message << std::endl;
	}
}

const value_type& CircularBuffer::at(int i) const {
	try
	{
		if (i >= 0 && i < len && ((tail == head) || (tail > head && head + i < tail) || (tail < head && (head + i < totallen || head + i - totallen < tail))))
			return buffer[(head + i) % totallen];
		throw "Invalid index";
	}
	catch (const char* error_message)
	{
		std::cout << error_message << std::endl;
	}
}

value_type& CircularBuffer::front() { return buffer[head]; } //������ �� ������ �������.
value_type& CircularBuffer::back() { return buffer[(tail + totallen - 1) % totallen]; }  //������ �� ��������� �������.
const value_type& CircularBuffer::front() const { return buffer[head]; }
const value_type& CircularBuffer::back() const { return buffer[(tail + totallen - 1) % totallen]; }

//������������ - �������� ��������� ����� ���, ��� ��� ������ �������
//������������ � ������ �������������� ������. ���������� ��������� 
//�� ������ �������.
value_type* CircularBuffer::linearize() {
	value_type* new_buffer = new value_type[totallen];
	std::copy_n(buffer, totallen, new_buffer);
	for (int i = 0; i < len; i++) buffer[i] = new_buffer[(head + i) % totallen];
	head = 0;
	tail = len % totallen;
	delete new_buffer;
	return buffer;
}
//���������, �������� �� ����� ���������������.
bool CircularBuffer::is_linearized() const { return head == 0; }
//�������� ����� ���, ��� �� �������� ������� �������� ������� 
//� �������� new_begin.
void CircularBuffer::rotate(int new_begin) {
	value_type* new_buffer = new value_type[totallen];
	std::copy_n(buffer, totallen, new_buffer);
	for (int i = 0; i < len; i++) buffer[(i + new_begin) % totallen] = new_buffer[(head + i) % totallen];
	head = new_begin;
	tail = (new_begin + len) % totallen;
	delete new_buffer;
}
//���������� ���������, ���������� � ������.
int CircularBuffer::size() const { return len; }
bool CircularBuffer::empty() const { return totallen == 0; }
//true, ���� size() == capacity().
bool CircularBuffer::full() const { return len == totallen; }
//���������� ��������� ����� � ������.
int CircularBuffer::reserve() const { return totallen - len; }
//������� ������
int CircularBuffer::capacity() const { return totallen; }

void CircularBuffer::set_capacity(int new_capacity) {
	linearize();
	totallen = new_capacity;
	value_type* new_buffer = new value_type[totallen];
	std::copy_n(buffer, totallen, new_buffer);
	buffer = new_buffer;
}
//�������� ������ ������.
//� ������ ����������, ����� �������� ����������� ��������� item.
void CircularBuffer::resize(int new_size, const value_type& item) {
	if (new_size < 0) {
		throw std::invalid_argument("New size cannot be negative");
	}
	if (new_size > totallen) set_capacity(new_size);
	tail = (head + new_size) % totallen;
	for (int i = head + len; i < head + new_size; i++) buffer[i % totallen] = item;
	len = new_size;
}

//�������� ������������.
CircularBuffer& CircularBuffer::operator=(const CircularBuffer& cb) {
	if (this != &cb) {
		CircularBuffer temp(cb);
		swap(temp);
	}
	return *this;
}
	////���������� ���������� ������ � ������� cb.
	void CircularBuffer::swap(CircularBuffer& cb) {
		std::swap(buffer, cb.buffer);
		std::swap(totallen, cb.totallen);
		std::swap(len, cb.len);
		std::swap(head, cb.head);
	}

	////��������� ������� � ����� ������. 
	////���� ������� ������ ������ ����� ��� �������, �� ��������������
	////������ ������� ������ (�.�., ����� �����������). 
	void CircularBuffer::push_back(const value_type& item) {
		buffer[tail] = item; 
		if (len < totallen) 
			len++;
		else 
			head = (head + 1) % totallen;
		tail = (tail + 1) % totallen;
	}
	////��������� ����� ������� ����� ������ ��������� ������. 
	////���������� push_back, ����� ���������� ��������� ������� ������.
	void CircularBuffer::push_front(const value_type& item) {
		head = (head - 1 + totallen) % totallen;
		buffer[head] = item;
		if (len < totallen) 
			len++;
		else 
			tail = (tail - 1 + totallen) % totallen;
	}
	////������� ��������� ������� ������.
	void CircularBuffer::pop_back() {
		if (len > 0) {
		    tail = (tail - 1) % totallen;
		    len -= 1;
		}
	}
	////������� ������ ������� ������.
	void CircularBuffer::pop_front() {
		if (len > 0) {
			head = (head + 1) % totallen;
			len -= 1;
		}
	}

	////��������� ������� item �� ������� pos. ������� ������ �������� ����������.
	void CircularBuffer::insert(int pos, const value_type& item) {
		if (pos < 0 || pos > len) {
			throw std::out_of_range("Invalid position");
		}
		if (len < totallen) {
			int insert_index = (head + pos) % totallen;
			for (int i = len; i > pos; i--) {
				buffer[(head + i) % totallen] = buffer[(head + i - 1) % totallen];
			}
			buffer[insert_index] = item;
			len++;
		}
		else {
			push_back();
			for (int i = len - 1; i > pos; i--) {
				buffer[(head + i) % totallen] = buffer[(head + i - 1) % totallen];
			}
			buffer[(head + pos) % totallen] = item;
		}
	}
	////������� �������� �� ������ � ��������� [first, last).
	void CircularBuffer::erase(int first, int last) {
		if (first < 0 || last > len || first >= last) {
			throw std::out_of_range("Invalid range");
		}
		int erase_count = last - first;
		for (int i = first; i < len - erase_count; i++) {
			buffer[(head + i) % totallen] = buffer[(head + i + erase_count) % totallen];
		}
		len -= erase_count;
	}
	////������� �����.
	void CircularBuffer::clear() { len = 0; }

	bool operator==(const CircularBuffer& a, const CircularBuffer& b)  {
		if (a.size() != b.size()) {
		return false;
	}
	for (int i = 0; i < a.size(); i++) {
		if (a[i] != b[i]) {
			return false;
		}
	}
	return true;
}
	bool operator!=(const CircularBuffer& a, const CircularBuffer& b) {
		return !(a == b);
	}
