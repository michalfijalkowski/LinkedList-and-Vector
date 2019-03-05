#ifndef AISDI_LINEAR_VECTOR_H
#define AISDI_LINEAR_VECTOR_H
 
#include <cstddef>
#include <initializer_list>
#include <stdexcept>

namespace aisdi
{
 
 
    template <typename Type>
    class Vector
    {
	
	
	public:
        using difference_type = std::ptrdiff_t;
        using size_type = std::size_t;
        using value_type = Type;
        using pointer = Type*;
        using reference = Type&;
        using const_pointer = const Type*;
        using const_reference = const Type&;
 
        class ConstIterator;
        class Iterator;
        using iterator = Iterator;
        using const_iterator = ConstIterator;
        
	private:
        Type *tab;
		size_type first_to_add;
        size_type capacity;
        
	public:
 
        Vector()
        {
            first_to_add=0;
            capacity=0;
            tab=nullptr;
 
        }
 
        Vector(std::initializer_list<Type> l)
        {
 
            first_to_add=0;
            capacity=l.size();
            tab=new Type[capacity];
 
            auto iterator_vector=l.begin();
            while(iterator_vector!= l.end())
            {
                this->append(*iterator_vector);
                ++iterator_vector;
            }
 
 
        }
 
        Vector(const Vector& other) 
        {
            first_to_add = 0;
            capacity = other.getSize();
            tab = new Type[capacity];
 
            auto iterator_vector=other.begin();
            while(iterator_vector!= other.end())
            {
                this->append(*iterator_vector);
                ++iterator_vector;
            }
 
        }
        
        Vector(Vector&& other) 
        {
 
            tab = other.tab;
            capacity = other.getSize();
            first_to_add = other.first_to_add;
 
			other.tab = nullptr;
            other.capacity = 0;
            other.first_to_add = 0;
            
		}
 
        ~Vector()
        {
            delete[] tab;
        }
 
        Vector& operator=(const Vector& other)
        {	
			
			if(tab==other.tab) return *this;
			
            delete[] tab;
            first_to_add=0;
            capacity = other.capacity;
            tab = new Type[capacity];
 
            auto iterator_vector=other.begin();
            while(iterator_vector!= other.end())
            {
                this->append(*iterator_vector);
                ++iterator_vector;
            }
          
            
            return *this;
        }
 
        Vector& operator=(Vector&& other)
        {	
            delete[] tab;
            
            tab=other.tab;
            other.tab=nullptr;
            first_to_add=other.first_to_add;
            capacity = other.capacity;
            
            other.first_to_add=0;
            other.capacity=0;
            return *this;
        }
 
        bool isEmpty() const
        {
            return (first_to_add==0);
        }
 
        size_type getSize() const
        {
            return first_to_add;
        }
 
 
        void append(const Type& item)
        {
            if(capacity==first_to_add)
                realloc();
            tab[first_to_add]=item;
            first_to_add++;
 
        }
 
        void prepend(const Type& item)
        {
            if(capacity==first_to_add)
                realloc();
            int i = first_to_add;
            while(i>0)
            {
                tab[i]=tab[i-1];
                i--;
            }
            tab[i] = item;
            first_to_add++;
        }
 
        void insert(const const_iterator& insertPosition, const Type& item)
        {
            if(insertPosition.index>first_to_add)
                throw std::logic_error("Logic: Can't insert element not in vector");
            if (capacity==first_to_add) realloc();
            if (insertPosition == cend()) {
                append(item);
                return;
            }
            if (insertPosition == cbegin()) {
                prepend(item);
                return;
            }
 
            int whereInsert = insertPosition.index;
            int i=first_to_add;
            while(i>whereInsert)
            {
                tab[i]=tab[i-1];
                i--;
            }
            tab[whereInsert] = item;
            first_to_add++;
 
        }
 
        Type popFirst()
        {
            if(this->isEmpty())
                throw std::out_of_range("Range: Can't pop from empty vector");
            Type temp = tab[0];
 
            for(int i=0;i<(int)first_to_add-1;i++)
                tab[i]=tab[i+1];
            first_to_add--;
 
            return temp;
        }
 
 
        void realloc()
        {
            Type *newtab;
            capacity = capacity+10;
            newtab = new Type[capacity];
            for (int i = 0; i < (int)first_to_add; i++)
                newtab[i] = tab[i];
            delete [] tab;
            tab=newtab;
        }
 
        Type popLast()
        {
            if(this->isEmpty())
                throw std::out_of_range("Range: Can't pop from empty vector");
            Type temp = tab[first_to_add-1];
            first_to_add--;
            return temp;
        }
 
        void erase(const const_iterator& possition)
        {
 
            if(this->isEmpty() || possition.index>=first_to_add)
                throw std::out_of_range("Range: Iterator position is not proper");
 
            int ToEraseIndex=possition.index;
 
            for(int i=ToEraseIndex;i<(int)first_to_add;i++)
                tab[i]=tab[i+1];
            --first_to_add;
        }
 
 
        void erase(const const_iterator& firstIncluded, const const_iterator& lastExcluded) 
        {	
			const_iterator it = cbegin();
			
			unsigned int distance, first_ind = 0, last_ind=0;
			for(unsigned int i=0; it !=cend();++i,++it)
			{
				if(it == firstIncluded) first_ind = i;
				if(it == lastExcluded)
				{
					last_ind =i;
					break;
				}
			}
			if(lastExcluded == cend()) first_to_add = first_ind;
			else
			{
				distance = first_to_add - last_ind;
				first_to_add-= last_ind - first_ind;
				
				for(unsigned int i=0; i<distance;++i) tab[first_ind +i] = tab[last_ind +i];
			}
			
        }
 
        iterator begin()
        {
 
            return iterator(cbegin());
 
        }
 
        iterator end()
        {
            return iterator(cend());
        }
 
 
        const_iterator cbegin() const
        {
            ConstIterator iterator_vector(this,&(tab[0]),0);
            return iterator_vector;
        }
 
        const_iterator cend() const
        {
            if(this->isEmpty())
            {
                ConstIterator iterator_vector(this,&(tab[0]),0);
                return iterator_vector;
            }
            ConstIterator iterator_vector(this,&(tab[first_to_add]),first_to_add);
            return iterator_vector;
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
    class Vector<Type>::ConstIterator
    {
 
 
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = typename Vector::value_type;
        using difference_type = typename Vector::difference_type;
        using pointer = typename Vector::const_pointer;
        using reference = typename Vector::const_reference;
 
 
 
        explicit ConstIterator()
        {
            ptr= nullptr;
        }
        ConstIterator(const Vector<Type> *Cont2,Type* actual,int index2):index(index2),Cont(Cont2),ptr(actual)
        {
 
        }
 
        reference operator*() const
        {
            if(Cont->getSize()<=index)
                throw std::out_of_range("Range: Iterator is not on element of vector");
            return *ptr;
        }
 
        ConstIterator& operator++() //pre
        {
            if(Cont->getSize()<=index)
                throw std::out_of_range("Range: Out of range ");
            ptr++;
            index++;
            return *this;
        }
 
        ConstIterator operator++(int) //post
        {
            if(Cont->getSize()<=index)
                throw std::out_of_range("Range: Out of range");
            ConstIterator temp= *this;
            
            ptr++;
            index++;
            return temp;
 
        }
 
        ConstIterator& operator--() // pre
        {
            if(index==0)
                throw std::out_of_range("Range: Out of range");
            ptr--;
            index--;
            return *this;
 
        }
 
        ConstIterator operator--(int) // post
        {
            if(index==0)
                throw std::out_of_range("Range: Out of range");
            ConstIterator temp= *this;
            ptr--;
            index--;
            return temp;
        }
 
        ConstIterator operator+(difference_type d) const
        {
            int n = static_cast<int>(d);
            if((index+n)>(Cont->first_to_add))
                throw std::out_of_range("Range: Out of range");
            else
                return ConstIterator(Cont,&(Cont->tab[index+n]) , index+n);
        }
 
        ConstIterator operator-(difference_type d) const
        {
            int n = static_cast<int>(d);
            if((int)(index-n)<0)
                throw std::out_of_range("Range: Out of range");
            else
                return ConstIterator(Cont,&(Cont->tab[index-n]) , index-n);
        }
 
        bool operator==(const ConstIterator& other) const
        {
            if(ptr==other.ptr) return true;
            else return false;
        }
 
        bool operator!=(const ConstIterator& other) const
        {
            if(ptr!=other.ptr) return true;
            else return false;
        }
 
        size_type index;
    
    private:
        const Vector<Type> *Cont;
        Type *ptr;
 
 
 
    };
 
    template <typename Type>
    class Vector<Type>::Iterator : public Vector<Type>::ConstIterator
    {
    public:
        using pointer = typename Vector::pointer;
        using reference = typename Vector::reference;
 
 
        explicit Iterator() {
        }
 
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
 
#endif // AISDI_LINEAR_VECTOR_H
