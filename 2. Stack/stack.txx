//
// Assignment 2 : Simple calculator using Stack
//
// Array-based stack data structure
//


template<class type>
Stack<type>::~Stack()
{
	// ToDo
	delete[] array;
}

template<class type>
type& Stack<type>::Top()
{
	// ToDo
	return array[top];
}

template<class type>
void Stack<type>::Push(const type& item)
{
	// ToDo
	// is Full
	array[++top] = item;
}

template<class type>
void Stack<type>::Pop()
{
	// ToDo
	top--;
}

template<class type>
bool Stack<type>::IsEmpty() const
{
	// ToDo	
	if (top == -1)
		return true;
	else
		return false;
}

