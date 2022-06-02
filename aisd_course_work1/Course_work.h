#pragma once
#include <fstream>
#include <stdexcept>
#include <iostream>

using namespace std;

long INF = 100000;

template <class T>
class Node {
private:
	Node* next;
	T data;

public:
	Node() {
		next = nullptr;
	}
	explicit Node(const T value) {
		next = nullptr;
		data = value;
	}
	~Node() {
		next = nullptr;
	}
	void set_next(Node* const next_el) {
		next = next_el;
	};
	void set_data(T new_data) {
		data = new_data;
	};
	Node* get_next() {
		return next;
	};
	T get_data() {
		return data;
	};
	void clear_next() {
		delete this;
		next = nullptr;
	};
};

template <class T>
class Queue {
private:
	Node<T>* temp;
	Node<T>* back;
	Node<T>* front;
	size_t queue_size;

public:
	Queue() {
		temp = nullptr;
		back = nullptr;
		front = nullptr;
		queue_size = 0;
	}
	~Queue() {
		while (queue_size != 0) {
			this->takeTop();
		}
		temp = nullptr;
		back = nullptr;
		front = nullptr;
		queue_size = 0;
	}
	Node<T>* get_front() {
		return front;
	}
	Node<T>* get_back() {
		return back;
	}
	void push(T data) {
		temp = new Node<T>(data);
		if (queue_size == 0) {
			front = temp;
			back = temp;
			temp = nullptr;
			queue_size++;

			return;
		}
		back->set_next(temp);
		back = back->get_next();

		temp = nullptr;
		queue_size++;
	}
	T takeTop() {
		if (queue_size == 0) {
			throw std::out_of_range("Error! The queue is empty!");
		}
		T front_data;
		front_data = front->get_data();
		if (queue_size == 1) {
			temp = nullptr;
			back = nullptr;
			front = nullptr;
			queue_size = 0;
			return front_data;
		}
		temp = front;
		front = front->get_next();
		temp->clear_next();

		temp = nullptr;
		queue_size--;

		return front_data;
	};
	T getTop() {
		if (queue_size == 0) {
			throw  std::out_of_range("Error! The queue is empty!");
		}

		return front->get_data();
	}
	size_t get_size() {
		return queue_size;
	}
};

template<class T>
class List
{
private:
	class Node
	{
	private:
		Node* next, * prev;
		T data;

	public:
		Node() : next(nullptr), prev(nullptr) {};
		Node(T data) {
			this->data = data;
			next = nullptr;
			prev = nullptr;
		}
		~Node() {
			next = nullptr;
			prev = nullptr;
		}
		void set_data(T data) {
			this->data = data;
		}
		T get_data() {
			return data;
		}
		Node* get_next() {
			return next;
		}
		Node* get_prev() {
			return prev;
		}
		void set_next(Node* pointer) {
			next = pointer;
		}
		void set_prev(Node* pointer) {
			prev = pointer;
		}
	};

	Node* head, * tail;
	Node* get_pointer(size_t index)
	{
		if (isEmpty() || (index > get_size() - 1))
		{
			throw out_of_range("Error! Invalid argument!");
		}
		else if (index == get_size() - 1)
			return tail;
		else if (index == 0)
			return head;
		else
		{
			Node* temp = head;
			while ((temp) && (index--))
			{
				temp = temp->get_next();
			}

			return temp;
		}
	}

public:
	List() : head(nullptr), tail(nullptr) {}
	List(int size, int value) {
		while (size--) {
			push_back(value);
		}
	}
	List(const List<T>& list) {
		head = nullptr;
		tail = nullptr;
		Node* temp = list.head;
		while (temp) {
			push_back(temp->get_data());
			temp = temp->get_next();
		}
	}
	~List()
	{
		while (head)
		{
			tail = head->get_next();
			delete head;
			head = tail;
		}
		head = nullptr;
	}
	void push_back(T data)
	{
		Node* temp = new Node;
		temp->set_data(data);
		if (head)
		{
			temp->set_prev(tail);
			tail->set_next(temp);
			tail = temp;
		}
		else
		{
			head = temp;
			tail = head;
		}
	}
	void push_front(T data)
	{
		Node* temp = new Node;
		temp->set_data(data);
		if (head)
		{
			temp->set_next(head);
			head->set_prev(temp);
			head = temp;
		}
		else
		{
			head = temp;
			tail = head;
		}
	}
	void push_back(List<bool> ls2)
	{
		Node* temp = ls2.head;
		size_t n = ls2.get_size();
		while ((temp) && (n--))
		{
			push_back(temp->get_data());
			temp = temp->get_next();
		}
	}
	void push_front(List& ls2)
	{
		Node* temp = ls2.tail;
		size_t n = ls2.get_size();
		while ((temp) && (n--))
		{
			push_front(temp->get_data());
			temp = temp->get_prev();
		}
	}
	void pop_back()
	{
		if (head != tail)
		{
			Node* temp = tail;
			tail = tail->get_prev();
			tail->set_next(nullptr);
			delete temp;
		}
		else if (!isEmpty())
		{
			Node* temp = tail;
			tail = head = nullptr;
			delete temp;
		}
		else
			throw out_of_range("Error! The list is empty!");
	}
	void pop_front()
	{
		if (head != tail)
		{
			Node* temp = head;
			head = head->get_next();
			head->set_prev(nullptr);
			delete temp;
		}
		else if (!isEmpty())
		{
			Node* temp = head;
			head = tail = nullptr;
			delete temp;
		}
		else
			throw out_of_range("Error! The list is empty!");
	}
	void insert(size_t index, T data)
	{
		Node* temp;
		temp = get_pointer(index);
		if (temp == head)
			push_front(data);
		else
		{
			Node* newElem = new Node;
			newElem->set_data(data);
			temp->get_prev()->set_next(newElem);
			newElem->set_prev(temp->get_prev());
			newElem->set_next(temp);
			temp->set_prev(newElem);
		}
	}
	T at(size_t index)
	{
		Node* temp;
		temp = get_pointer(index);

		return temp->get_data();
	}
	void remove(size_t index)
	{
		Node* temp;
		temp = get_pointer(index);
		if (temp == head)
			pop_front();
		else if (temp == tail)
			pop_back();
		else
		{
			temp->get_prev()->set_next(temp->get_next());
			temp->get_next()->set_prev(temp->get_prev());
			delete temp;
		}
	}
	void remove(T data) {
		Node* temp = head;
		while (temp && temp->get_data() != data)
			temp = temp->get_next();
		if (!temp)
			throw out_of_range("Error! Invalid argument!");
		if (temp == head)
			pop_front();
		else if (temp == tail)
			pop_back();
		else
		{
			temp->get_prev()->set_next(temp->get_next());
			temp->get_next()->set_prev(temp->get_prev());
			delete temp;
		}
	}
	bool contains(T symb) {
		Node* temp = head;
		while (temp) {
			if (temp->get_data() == symb)
				return true;
			temp = temp->get_next();
		}

		return false;
	}
	size_t get_size()
	{
		Node* temp = head;
		size_t length = 0;
		while (temp)
		{
			length++;
			temp = temp->get_next();
		}

		return length;
	}
	void print()
	{
		Node* temp = head;
		while (temp)
		{
			cout << temp->get_data();
			temp = temp->get_next();
		}
	}
	void clear()
	{
		while (head)
		{
			tail = head->get_next();
			delete head;
			head = tail;
		}
	}
	size_t get_index(T symb) {
		Node* temp = head;
		size_t index = 0;
		while (temp) {
			if (temp->get_data() == symb)
				break;
			temp = temp->get_next();
			index++;
		}

		return index;
	}
	void set(size_t index, T data)
	{
		Node* temp;
		temp = get_pointer(index);
		temp->set_data(data);
	}
	bool isEmpty()
	{
		if (!head)
			return true;
		else
			return false;
	}
	bool compare(List<T> list) {
		if (get_size() != list.get_size())
			return false;
		for (int i = 0; i < get_size(); i++) {
			if (at(i) != list.at(i))
				return false;
		}

		return true;
	}
	bool contains(List<char>& list) {
		Node* temp = head;
		while (temp) {
			if (temp->get_data().compare(list))
				return true;
			temp = temp->get_next();
		}

		return false;
	}
	void reset() {
		head = nullptr;
		tail = nullptr;
	}
	void reverse() {
		Node* temp1 = head, * temp2 = tail;
		T value;
		for (size_t i = 0; i < get_size() / 2; i++) {
			value = temp1->get_data();
			temp1->set_data(temp2->get_data());
			temp2->set_data(value);
			temp1 = temp1->get_next();
			temp2 = temp2->get_prev();
		}
	}
	int get_price(size_t vertex1, size_t vertex2) {
		Node* temp = head;
		while (temp) {
			if (temp->get_data().first_vertex == vertex1 && temp->get_data().scnd_vertex == vertex2)
				return temp->get_data().price;
			temp = temp->get_next();
		}
	}
};

template<class T>
class Matrix {
	class Node {
	private:
		List<T> data;
		Node* next, * prev;

	public:
		Node(List<T> data) {
			this->data = data;
			next = nullptr;
			prev = nullptr;
		}
		~Node() {
			next = nullptr;
			prev = nullptr;
		}
		Node() : next(nullptr), prev(nullptr) {};
		void set_data(List<T>& data) {
			this->data = data;
		}
		List<T>& get_data() {
			return data;
		}
		Node* get_next() {
			return next;
		}
		Node* get_prev() {
			return prev;
		}
		void set_next(Node* temp) {
			next = temp;
		}
		void set_prev(Node* temp) {
			prev = temp;
		}
	};

	Node* head, * tail;
	Node* get_node(size_t index)
	{
		if (isEmpty() || (index > get_size() - 1))
		{
			throw out_of_range("Error! Invalid argument!");
		}
		else if (index == get_size() - 1)
			return tail;
		else if (index == 0)
			return head;
		else
		{
			Node* temp = head;
			while ((temp) && (index--))
			{
				temp = temp->get_next();
			}

			return temp;
		}
	}

public:
	Matrix() : head(nullptr), tail(nullptr) {}
	Matrix(const Matrix<T>& list) {
		head = nullptr;
		tail = nullptr;
		Node* temp = list.head;
		while (temp) {
			push_back(temp->get_data());
			temp = temp->get_next();
		}
	}
	~Matrix()
	{
		while (head)
		{
			tail = head->get_next();
			delete head;
			head = tail;
		}
		head = nullptr;
	}
	void set(size_t index, List<T> data)
	{
		Node* temp;
		temp = get_node(index);
		temp->set_data(data);
	}
	void push_back(List<T>& data)
	{
		Node* temp = new Node;
		temp->set_data(data);

		if (head)
		{
			temp->set_prev(tail);
			tail->set_next(temp);
			tail = temp;
		}
		else
		{
			head = temp;
			tail = head;
		}
	}
	void push_front(List<T> data)
	{
		Node* temp = new Node;
		temp->set_data(data);
		if (head)
		{
			temp->set_next(head);
			head->set_prev(temp);
			head = temp;
		}
		else
		{
			head = temp;
			tail = head;
		}
	}
	void push_back(Matrix<bool> scnd_list)
	{
		Node* temp = scnd_list.head;
		size_t size = scnd_list.get_size();
		while ((temp) && (size--))
		{
			push_back(temp->get_data());
			temp = temp->get_next();
		}
	}
	void push_front(Matrix& scnd_list)
	{
		Node* temp = scnd_list.tail;
		size_t n = scnd_list.get_size();
		while ((temp) && (n--))
		{
			push_front(temp->get_data());
			temp = temp->get_prev();
		}
	}
	void insert(size_t index, List<T> data)
	{
		Node* temp;
		temp = get_node(index);
		if (temp == head)
			push_front(data);
		else
		{
			Node* newel = new Node;
			newel->set_data(data);
			temp->get_prev()->set_next(newel);
			newel->set_prev(temp->get_prev());
			newel->set_next(temp);
			temp->set_prev(newel);
		}
	}
	void pop_back()
	{
		if (head != tail)
		{
			Node* temp = tail;
			tail = tail->get_prev();
			tail->set_next(nullptr);
			delete temp;
		}

		else if (!isEmpty())
		{
			Node* temp = tail;
			tail = head = nullptr;
			delete temp;
		}
		else
			throw out_of_range("Error! The list is empty!");
	}
	void pop_front()
	{
		if (head != tail)
		{
			Node* temp = head;
			head = head->get_next();
			head->set_prev(nullptr);
			delete temp;
		}
		else if (!isEmpty())
		{
			Node* temp = head;
			head = tail = nullptr;
			delete temp;
		}
		else
			throw out_of_range("Error! The list is empty!");
	}
	void remove(List<T> data) {
		Node* temp = head;
		while (temp && temp->get_data() != data)
			temp = temp->get_next();
		if (!temp)
			throw out_of_range("Error! Invalid argument!");
		if (temp == head)
			pop_front();
		else if (temp == tail)
			pop_back();
		else
		{
			temp->get_prev()->set_next(temp->get_next());
			temp->get_next()->set_prev(temp->get_prev());
			delete temp;
		}
	}
	List<T>& at(size_t index) {
		Node* temp;
		temp = get_node(index);

		return temp->get_data();
	}
	void remove(size_t index) {
		Node* temp;
		temp = get_node(index);
		if (temp == head)
			pop_front();
		else if (temp == tail)
			pop_back();
		else
		{
			temp->get_prev()->set_next(temp->get_next());
			temp->get_next()->set_prev(temp->get_prev());
			delete temp;
		}
	}
	size_t get_size() {
		Node* temp = head;
		size_t length = 0;
		while (temp)
		{
			length++;
			temp = temp->get_next();
		}

		return length;
	}
	void print() {
		Node* temp = head;
		while (temp) {
			temp->get_data().print();
			temp = temp->get_next();
		}
		std::cout << std::endl;
	}
	void clear() {
		while (head)
		{
			tail = head->get_next();
			delete head;
			head = tail;
		}
	}
	bool isEmpty() {
		if (!head)
			return true;
		else
			return false;
	}
};

int bfs(int s, int t, Matrix<int>& M, Matrix<int>& adj, List<int>& temp_list) {
	for (int i = 0; i < temp_list.get_size(); i++)
		temp_list.set(i, -1);
	temp_list.set(s, -2);

	struct pair {
		long first;
		long second;
	};

	Queue <pair> queue;
	queue.push({ s, INF });
	while (queue.get_size() != 0) {
		int curr = queue.getTop().first;
		int flow = queue.getTop().second;
		queue.takeTop();

		for (int next = 0; next < adj.at(curr).get_size(); next++) {
			if (temp_list.at(next) == -1 && M.at(curr).at(next)) {
				temp_list.set(next, curr);
				int new_flow;
				if (M.at(curr).at(next) < flow)
					new_flow = M.at(curr).at(next);
				else
					new_flow = flow;
				if (next == t)
					return new_flow;
				queue.push({ next, new_flow });
			}
		}
	}

	return 0;
}

int maxflow(List<char>& V, Matrix<int>& M, Matrix<int>& adj) {
	if (V.isEmpty())
		throw invalid_argument("Error! Graph is empty!");
	int max_flow = 0;
	List<int> parent(M.get_size(), 0);
	int new_flow;
	if (bfs(0, V.get_size() - 1, M, adj, parent) == 0)
		throw invalid_argument("Sorry! No path S->T");

	while (new_flow = bfs(0, V.get_size() - 1, M, adj, parent)) {
		max_flow += new_flow;
		int cur = V.get_size() - 1;
		while (cur != 0) {
			int prev = parent.at(cur);
			M.at(prev).set(cur, M.at(prev).at(cur) - new_flow);
			M.at(cur).set(prev, M.at(cur).at(prev) + new_flow);
			cur = prev;
		}
	}

	return max_flow;
}
