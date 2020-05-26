#include <iostream>

using namespace std;

template<typename type>//создаем шаблон, в шаблоне будут использоваться встроенные типы данных 
class List { //создаем общий класс для списка
private:
	template<typename type>
	class Node {
	public:
		type data;
		Node* next;
		Node* prev;

		Node(type data, Node* next = nullptr, Node* prev = nullptr) //обнуляем указатели
		{
			this->data = data;
			this->next = next;
			this->prev = prev;
		}
	};

	size_t size; //размер списка
	Node<type>* head; //голова списка
	Node<type>* tail; //хвост списка

public:
	List(); //конструктор
	~List(); //деконструктор

	void Add(type data); //добавление
	void AddHead(type data); //добавление головы
	type& operator[](const int index); //перегрузка оператора индексации
	size_t GetSize(); //функция определения размеров списка
	void Put(type data, int index); //Вставить элемент на позицию index
	type Peek();//извлекает следующий символ из потока, фактически не потребляя его.
	void Delete(int index); //функция удаления из списка элемента с заданным индексом
	void Clear(); //очистка всего списка
};

template<typename type>
List<type>::List()
{
	size = 0;
	head = nullptr;
	tail = nullptr;
}

template<typename type>
List<type>::~List()
{}

template<typename type>
void List<type>::Add(type data)
{
	if (head == nullptr) //если список пустой
	{
		head = tail = new Node<type>(data);
	}
	else  //если в списке уже есть элементы
	{
		Node<type>* current = new Node<type>(data, nullptr, tail);
		tail->next = current;
		tail = current;
	}

	size++;
}

template<typename type>
void List<type>::AddHead(type data)
{
	if (head == nullptr)
	{
		head = tail = new Node<type>(data);;
	}
	else
	{
		Node<type>* current = new Node<type>(data, head);
		head = current;
	}

	size++;
}

template<typename type>
type& List<type>::operator[](const int index) //перегрузка оператора индексации.
{
	Node<type>* current;
	int iterator; //счётчик итераций

	if (index <= size / 2)
	{
		current = head;
		iterator = 0;
		while (1)
		{
			if (iterator == index)
			{
				return current->data;
			}
			else
			{
				current = current->next;
				iterator++;
			}
		}
	}
	else
	{
		current = tail;
		iterator = size - 1;
		while (1)
		{
			if (iterator == index)
			{
				return current->data;
			}
			else
			{
				current = current->prev;
				iterator--;
			}
		}
	}
}

template<typename type>
size_t List<type>::GetSize()
{
	return size;
}

template<typename type>
void List<type>::Put(type data, int index)
{
	if (index == 0)
	{
		AddHead(data);
	}
	else if (index == size)
	{
		Add(data);
	}
	else
	{
		Node<type>* previous; //предыдущий
		Node<type>* current; //текущий

		if (index <= size / 2) //если в первой половине
		{
			previous = head;

			for (int i = 0; i < index - 1; i++)
			{
				previous = previous->next;
			}

			current = new Node<type>(data, previous->next, previous);
			previous->next->prev = current;
			previous->next = current;
		}
		else //если во второй половине
		{
			previous = tail;

			for (int i = size - 1; i > index; i--)
			{
				previous = previous->prev;
			}

			current = new Node<type>(data, previous, previous->prev);
			previous->prev->next = current;
			previous->prev = current;
		}
	}

	size++;
}

template<typename type>
type List<type>::Peek() //возврат данных о конце списка
{
	return tail->data;
}

template<typename type>
void List<type>::Delete(int index)
{
	if (index == 0)
	{
		Node<type>* temp = head;
		head = head->next;
		delete temp;
	}
	else if (index == size - 1)
	{
		Node<type>* temp = tail;
		tail = tail->prev;
		delete temp;
	}
	else
	{
		Node<type>* previous;
		Node<type>* toDelete;

		if (index <= size / 2)
		{
			previous = head;

			for (int i = 0; i < index - 1; i++)
			{
				previous = previous->next;
			}

			toDelete = previous->next;
			previous->next = toDelete->next;
			toDelete->next->prev = previous;
		}
		else
		{
			previous = tail;

			for (int i = size - 1; i > index + 1; i--)
			{
				previous = previous->prev;
			}

			toDelete = previous->prev;
			previous->prev = toDelete->prev;
			toDelete->prev->next = previous;
		}

		delete toDelete;
	}
	size--;
}

template<typename type>
void List<type>::Clear()
{
	while (size > 0)
	{
		Node<type>* temp = head;
		head = head->next;
		delete temp;
		size--;
	}
}

int main()
{
	List<int> list;

	for (int i = 0; i < 10; i++) //заполним список 
		list.Add(i * 7);

	cout << "List:" << endl;

	for (int i = 0; i < list.GetSize(); i++)
		cout << list[i] << endl;

	list.Put(228, 3);		//вставим на 8 позицию число 228

	cout << "List (update after Put)" << endl;

	for (int i = 0; i < list.GetSize(); i++)
		cout << list[i] << endl;

	list.Delete(10);	//удаляем из списка 10 позицию

	cout << "List (Update after Delete)" << endl;

	for (int i = 0; i < list.GetSize(); i++)
		cout << list[i] << endl;

	list.AddHead(147); //В начало списка добавляется 147

	cout << "The list with added fisrt value:" << endl;

	for (int i = 0; i < list.GetSize(); i++)
		cout << list[i] << endl;

	list.Clear();		//очистим список

	return 0;
	system("pause");
}
