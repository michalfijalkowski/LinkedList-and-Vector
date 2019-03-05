#ifndef AISDI_LINEAR_LINKEDLIST_H
#define AISDI_LINEAR_LINKEDLIST_H

#include <cstddef>
#include <initializer_list>
#include <stdexcept>

namespace aisdi
{



    template <typename Type>
    class LinkedList
    {
	    
    public:
        using difference_type = std::ptrdiff_t;
        using size_type = std::size_t;
        using value_type = Type;
        using pointer = Type*;
        using reference = Type&;
        using const_pointer = const Type*;
        using const_reference = const Type&;

        class Iterator;
        using iterator = Iterator;
        class ConstIterator;
        using const_iterator = ConstIterator;

		struct Node
		{
			Type *data; // wartosc elementu
			Node *prev;
			Node *next;

			~Node()
			{	
				delete data;
				next=nullptr;
				prev=nullptr;
			}

			Node()
			{	
				data=nullptr;
				next=nullptr;
				prev=nullptr;

			}

			Node(const Type &A)
			{	
				data = new Type(A);
				next=nullptr;
				prev=nullptr;
			}

		};
	
	private:
		Node* first;
        Node* last;
		size_type length;
		
	public:

        LinkedList()   
        {	
			length=0;
            first=new Node;
            last=new Node;
            last->next= nullptr;
            first->prev= nullptr;
            first->next=last;
            last->prev=first;

        }

        LinkedList(std::initializer_list<Type> l):LinkedList() 
        {
			
			for(auto iterator_list=l.begin();iterator_list!=(l.end());++iterator_list)
            {
                this->append(*iterator_list);

            }
			length=l.size();
        }

        LinkedList(const LinkedList& other):LinkedList() 
        {

            for(auto iterator_list=other.begin();iterator_list!=(other.end());++iterator_list)
            {
                this->append(*iterator_list);

            }
            length=other.length;
        }

        LinkedList(LinkedList&& other):LinkedList()
        {
			length=other.length;
			other.length=0;
            first->next=other.first->next;
            last->prev=other.last->prev;
            other.first->next->prev=first;
            other.last->prev->next=last;
            other.first->next= other.last;
            other.last->prev= other.first;
            
        }


        ~LinkedList()
        {
            erase(begin(),end());
            delete last;
            delete first;
        }

        LinkedList& operator=(const LinkedList& other) 
        {	
			
			if(first!=other.first)
        {

        while (!isEmpty())
            erase(begin());
        
        for(auto iterator_list=other.begin();iterator_list!=(other.end());++iterator_list)
				{
					this->append(*iterator_list);

				}
        length = other.length;
        }
        return *this;
        }

        LinkedList& operator=(LinkedList&& other) 
        {           
            erase(begin(),end());
			Node* h = first;
			Node* t = last;
			first = other.first;
			last = other.last;
			length = other.length;
			other.first = h;
			other.last = t;
			other.length = 0;


        return *this;

        }

        bool isEmpty() const
        {

            return !length;
        }

        size_type getSize() const
        {	
			return length;       
        }

        void append(const Type& item) 
        {
            Node* newNode= new Node(item);
            Node* CurrentlyLastElement=last->prev;
            last->prev=newNode;
            newNode->next=last;
            newNode->prev=CurrentlyLastElement;
            CurrentlyLastElement->next=newNode;
            ++length;
        }

        void prepend(const Type& item) 
        {
            Node* newNode= new Node(item);
            Node* CurrentlyFirstElement=first->next;
            first->next=newNode;
            newNode->next=CurrentlyFirstElement;
            newNode->prev=first;
            CurrentlyFirstElement->prev=newNode;
            ++length;

        }

        void insert(const const_iterator& insertPosition, const Type& item)
        {

            Node* newNode = new Node(item);
            Node* prevNode = insertPosition.ptr->prev;
            newNode->next=insertPosition.ptr;
            newNode->prev=prevNode;
            prevNode->next=newNode;
            (insertPosition.ptr)->prev=newNode;
            ++length;
        }


        Type popFirst() 
        {
            if(this->isEmpty()) throw std::out_of_range("Range Error: Can't erase element from empty list");
            auto temp=*begin();
            erase(begin());
            return temp;
        }
        Type popLast() 
        {
            if(this->isEmpty()) throw std::out_of_range("Range Error: Can't erase element from empty list");
            auto temp=*(end()-1);
            erase(end()-1);
            return temp;
        }

        void erase(const const_iterator& possition)
        {
            if(possition.ptr->next==nullptr || possition.ptr->prev==nullptr)
            {
                throw std::out_of_range("Range Error: Can't erase guardian");
            }

            possition.ptr->next->prev=possition.ptr->prev;
            possition.ptr->prev->next=possition.ptr->next;
            delete possition.ptr;
            --length;
        }

        void erase(const const_iterator& firstIncluded, const const_iterator& lastExcluded)
        {

            for(auto iterator_list=firstIncluded;iterator_list!=lastExcluded;)
            {
                auto iterator_temp=iterator_list+1;
                this->erase(iterator_list);
                iterator_list=iterator_temp;
            }
        }

        iterator begin()
        {
            return iterator(first->next);
        }

        iterator end()
        {
			return iterator(last);
        }

        const_iterator cbegin() const
        {
            return const_iterator(first->next);
        }

        const_iterator cend() const
        {
            return const_iterator(last);
        }

        const_iterator begin() const
        {
            return cbegin();
        }

        const_iterator end() const
        {
            return cend();
        }
    
    };

    template <typename Type>
    class LinkedList<Type>::ConstIterator
    {
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = typename LinkedList::value_type;
        using difference_type = typename LinkedList::difference_type;
        using pointer = typename LinkedList::const_pointer;
        using reference = typename LinkedList::const_reference;

        explicit ConstIterator()
        {
			ptr= nullptr;
        }

        ConstIterator(Node* actual)
        {
            ptr=actual;
        }


        reference operator*() const
        {
            if(ptr->next!=nullptr && ptr->prev!=nullptr)
                return *(ptr->data);
            else throw std::out_of_range("Range Error: Can't get data from guardian");
        }

        ConstIterator& operator++() 
        {
            if(ptr->next!=nullptr)
            {
                ptr=ptr->next;
                return *this;
            }
            else throw std::out_of_range("Range Error: Can't go further than last guardian");
        }

        ConstIterator operator++(int) 
        {
            if(ptr->next!=nullptr)
            {
                ConstIterator temp= *this;
                ptr=ptr->next;
                return temp;
            }
            else throw std::out_of_range("Range Error: Can't go forward - last guardian");
        }

        ConstIterator& operator--()
        {
            if(ptr->prev->prev!=nullptr )
            {
                ptr=ptr->prev;
                return *this;
            }
            else throw std::out_of_range("Range Error: Can't go backward - first  guardian");
        }

        ConstIterator operator--(int)
        {
            if(ptr->prev->prev!=nullptr)
            {
                ConstIterator temp= *this;
                ptr=ptr->prev;
                return temp;
            }
            else throw std::out_of_range("Range Error: Can't go backward - first  guardian" );
        }

        ConstIterator operator+(difference_type d) const
        {
            ConstIterator temp=*this;
            if(d>=0)
                while(d>0)
                {
                    --d;
                    ++temp;
                    if(temp.ptr == nullptr) throw std::out_of_range("Range Error: Can't go forward - last  guardian" );
                }
            else
                while(d<0)
                {
                    ++d;
                    --temp;
                    if(temp.ptr == nullptr) throw std::out_of_range("Range Error: Can't go backward - first  guardian" );
                }
            return temp;
        }

        ConstIterator operator-(difference_type d) const
        {
            ConstIterator temp=*this;
            if(d<=0)
                while(d<0)
                {
                    ++d;
                    --temp;
                    if(temp.ptr == nullptr) throw std::out_of_range("Range Error: Can't go forward - last  guardian" );
                }
            else
                while(d>0)
                {
                    --d;
                    --temp;
                    if(temp.ptr == nullptr) throw std::out_of_range("Range Error: Can't go backward - first  guardian" );
                }
            return temp;
        }

        bool operator==(const ConstIterator& other) const
        {

            return ptr==other.ptr;
        }

        bool operator!=(const ConstIterator& other) const
        {
            return ptr!=other.ptr;

        }

    private:
        Node* ptr;
        friend void LinkedList <Type>::insert(const const_iterator&, const Type&);
        friend void LinkedList <Type>::erase(const const_iterator&);


    };

    template <typename Type>
    class LinkedList<Type>::Iterator : public LinkedList<Type>::ConstIterator
    {
    public:
        using pointer = typename LinkedList::pointer;
        using reference = typename LinkedList::reference;

        explicit Iterator()
        {}

        Iterator(const ConstIterator& other)
                : ConstIterator(other)
        {}

        Iterator& operator++()
        {
            ConstIterator::operator++();
            return *this;
        }

        Iterator operator++(int)
        {
            auto result = *this;
            ConstIterator::operator++();
            return result;
        }

        Iterator& operator--()
        {
            ConstIterator::operator--();
            return *this;
        }

        Iterator operator--(int)
        {
            auto result = *this;
            ConstIterator::operator--();
            return result;
        }

        Iterator operator+(difference_type d) const
        {
            return ConstIterator::operator+(d);
        }

        Iterator operator-(difference_type d) const
        {
            return ConstIterator::operator-(d);
        }

        reference operator*() const
        {
            // ugly cast, yet reduces code duplication.
            return const_cast<reference>(ConstIterator::operator*());
        }
    };

}

#endif // AISDI_LINEAR_LINKEDLIST_H
