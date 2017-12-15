#ifndef AISDI_LINEAR_VECTOR_H
#define AISDI_LINEAR_VECTOR_H

#include <cstddef>
#include <initializer_list>
#include <stdexcept>

namespace aisdi
{

    template<typename Type>
    class Vector
    {
    public:
        class ConstIterator;
        class Iterator;

        using difference_type = std::ptrdiff_t;
        using size_type = std::size_t;
        using value_type = Type;
        using pointer = Type *;
        using reference = Type &;
        using const_pointer = const Type *;
        using const_reference = const Type &;
        using IteratorType = typename ConstIterator::IteratorType;

        using iterator = Iterator;
        using const_iterator = ConstIterator;

    private:
        static const size_type DEFAULT_INITIAL_CAPACITY = 30;
        pointer elements = nullptr;
        size_type size;
        size_type capacity;
        mutable const_iterator pastTheEnd = nullptr;

    public:
        explicit Vector(size_type initialCapacity = DEFAULT_INITIAL_CAPACITY)
            : elements(new Type[initialCapacity]),
              size(0),
              capacity(initialCapacity),
              pastTheEnd(elements, this, IteratorType::END)
        {}

        Vector(std::initializer_list<Type> l)
            : Vector(l.size())
        {
            copyFromAndAppend(l);
        }

        Vector(const Vector &other)
            : Vector(other.getCapacity())
        {
            copyFromAndAppend(other);
        }

        Vector(Vector &&other) noexcept
            : pastTheEnd(elements, this, IteratorType::END)
        {
            moveFrom(other);
        }

        ~Vector()
        {
            freeMemoryIfAllocated();
        }

        Vector &operator=(const Vector &other)
        {
            if (this == &other)
                return *this;

            if (capacity < other.getSize())
                reallocateMemory(other.getSize());

            copyFromAndTruncate(other);

            return *this;
        }

        Vector &operator=(Vector &&other) noexcept
        {
            if (elements != nullptr)
                delete [] elements;

            moveFrom(other);

            return *this;
        }

        bool isEmpty() const
        {
            return size == 0;
        }

        size_type getSize() const
        {
            return size;
        }

        size_type getCapacity() const
        {
            return capacity;
        }

        void append(const Type &item)
        {
            reallocateMemoryIfNeeded();
            elements[size] = item;
            size++;
        }

        void prepend(const Type &item)
        {
            reallocateMemoryIfNeeded();
            shiftElementsToRightFrom(0);
            elements[0] = item;
            size++;
        }

        void insert(const const_iterator &insertPosition, const Type &item)
        {
            //NOTE: index needs to be calculated before reallocation!
            size_type insertIndex = insertPosition.calculateIndex();
            reallocateMemoryIfNeeded();
            shiftElementsToRightFrom(insertIndex);
            elements[insertIndex] = item;
            size++;
        }

        Type popFirst()
        {
            throwIfCollectionEmpty(
                    std::logic_error("cannot popFirst when collection is empty"));

            value_type value = elements[0];
            shiftElementsToLeftUpTo(0);
            size--;
            return value;
        }

        Type popLast()
        {
            throwIfCollectionEmpty(
                    std::logic_error("cannot popLast when collection is empty"));

            value_type value = elements[size-1];
            size--;
            return value;
        }

        void erase(const const_iterator &position)
        {
            throwIfCollectionEmpty(
                    std::out_of_range("cannot erase from empty collection"));

            throwIfIteratorEqaulsEnd(
                    position,
                    std::out_of_range("cannot erase end"));

            shiftElementsToLeftUpTo(position.calculateIndex());
            size--;
        }

        void erase(const const_iterator &firstIncluded, const const_iterator &lastExcluded)
        {
            if (firstIncluded == lastExcluded)
                return;

            size_type firstIncludeIndex = firstIncluded.calculateIndex();
            size_type lastExcludedIndex = lastExcluded.calculateIndex();

            size -= (lastExcludedIndex - firstIncludeIndex);

            for (size_type i = firstIncludeIndex, j = lastExcludedIndex; i < size; i++, j++)
                elements[i] = elements[j];

        }

        iterator begin()
        {
            return createBegin();
        }

        iterator end()
        {
            if (isEmpty())
                return createBeginAsEnd();
            else
                return preparePastTheEnd();
        }

        const_iterator cbegin() const
        {
            return createConstBegin();
        }

        const_iterator cend() const
        {
            if (isEmpty())
                return createConstBeginAsEnd();
            else
                return preparePastTheEnd();
        }

        const_iterator begin() const
        {
            return cbegin();
        }

        const_iterator end() const
        {
            return cend();
        }

    private:
        template<class Collection>
        void copyFromAndTruncate(const Collection &collection)
        {
            size = 0;
            copyFromAndAppend(collection);
        }

        template<class Collection>
        void copyFromAndAppend(const Collection &collection)
        {
            for (auto& el : collection)
                append(el);
        }

        void moveFrom(Vector& other)
        {
            elements = other.elements;
            size = other.getSize();
            capacity = other.getCapacity();
            other.elements = nullptr;
            other.size = 0;
        }

        void freeMemoryIfAllocated()
        {
            if (elements != nullptr)
                delete [] elements;
        }

        void reallocateMemoryIfNeeded()
        {
            if (size + 1 > capacity)
                reallocateMemory();
        }

        void reallocateMemory()
        {
            reallocateMemory(capacity*2);
        }

        void reallocateMemory(size_type newCapacity)
        {
            pointer oldElements = elements;

            capacity = newCapacity;
            elements = new Type[capacity];

            for (size_type i = 0; i < size; i++)
            {
                elements[i] = oldElements[i];
            }

            delete [] oldElements;
        }

        void shiftElementsToRightFrom(size_type beginIndex)
        {
            for (size_type i = size; i > beginIndex; i--)
            {
                elements[i] = elements[i-1];
            }
        }

        void shiftElementsToLeftUpTo(size_type consumedElementIndex)
        {
            for( size_type i = consumedElementIndex; i < size-1; i++)
            {
                elements[i] = elements[i+1];
            }
        }

        const_iterator& preparePastTheEnd() const
        {
            pastTheEnd.currentElement = &elements[size];
            return pastTheEnd;
        }

        iterator createBegin()
        {
            return Iterator(&elements[0], this, ConstIterator::IteratorType::BEGIN);
        }

        const_iterator createConstBegin() const
        {
            return ConstIterator(&elements[0], this, ConstIterator::IteratorType::BEGIN);
        }

        iterator createBeginAsEnd()
        {
            iterator it(begin());
            it.markEnd();
            return it;
        }

        const_iterator createConstBeginAsEnd() const
        {
            const_iterator it(begin());
            it.markEnd();
            return it;
        }

        template <typename Exception>
        void throwIfCollectionEmpty(const Exception& e)
        {
            if (isEmpty())
                throw e;
        }

        template <typename Exception>
        void throwIfIteratorEqaulsEnd(const ConstIterator &iterator, const Exception &e)
        {
            if (iterator.isEnd())
                throw e;
        }
    };

    template<typename Type>
    class Vector<Type>::ConstIterator
    {
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = typename Vector::value_type;
        using difference_type = typename Vector::difference_type;
        using pointer = typename Vector::const_pointer;
        using reference = typename Vector::const_reference;
        using size_type = typename Vector::size_type;

        enum class IteratorType {REGULAR, BEGIN, END};

        friend class Vector;

    private:
        pointer currentElement;
        const Vector *collection;
        IteratorType iteratorType;

    public:
        explicit ConstIterator(pointer currentElement, const Vector *collection,
                               IteratorType iteratorType = IteratorType::REGULAR)
            : currentElement(currentElement),
              collection(collection),
              iteratorType(iteratorType)
        {}

        ConstIterator(const ConstIterator& other)
            : ConstIterator(other.currentElement, other.collection, other.iteratorType)
        {}

        reference operator*() const
        {
            throwIfEnd(
                    std::out_of_range("end iterator cannot be dereferenced"));

            return *currentElement;
        }

        ConstIterator &operator++()
        {
            throwIfEnd(
                    std::out_of_range("cannot increment end iterator"));

            currentElement++;

            if (isBegin())
                markRegular();

            if ((size_type)(currentElement - collection->elements) >= collection->getSize())
                markEnd();

            return *this;
        }

        ConstIterator operator++(int)
        {
            ConstIterator old = *this;
            operator++();
            return old;
        }

        ConstIterator &operator--()
        {
            throwIfBegin(
                    std::out_of_range("cannot decrement begin iterator"));

            currentElement--;

            if (isEnd())
                markRegular();

            if (currentElement == collection->elements)
                markBegin();

            return *this;
        }

        ConstIterator operator--(int)
        {
            ConstIterator old = *this;
            operator--();
            return old;
        }

        ConstIterator operator+(difference_type d) const
        {
            return ConstIterator(currentElement + d, collection);
        }

        ConstIterator operator-(difference_type d) const
        {
            return ConstIterator(currentElement - d, collection);
        }

        bool operator==(const ConstIterator &other) const
        {
            if (isEnd() && other.isEnd())
                return true;

            return currentElement == other.currentElement;
        }

        bool operator!=(const ConstIterator &other) const
        {
            return !operator==(other);
        }

        size_type calculateIndex() const
        {
            return currentElement - collection->elements;
        }

    protected:
        bool isEnd() const
        {
            return iteratorType == IteratorType::END;
        }

        bool isBegin() const
        {
            return iteratorType == IteratorType::BEGIN;
        }

        bool isRegular() const
        {
            return iteratorType == IteratorType::REGULAR;
        }

        void markEnd()
        {
            iteratorType = IteratorType::END;
        }

        void markBegin()
        {
            iteratorType = IteratorType::BEGIN;
        }

        void markRegular()
        {
            iteratorType = IteratorType::REGULAR;
        }

        template <typename Exception>
        void throwIfBegin(const Exception& e) const
        {
            if (isBegin())
                throw e;
        }

        template <typename Exception>
        void throwIfEnd(const Exception& e) const
        {
            if (isEnd())
                throw e;
        }
    };

    template<typename Type>
    class Vector<Type>::Iterator : public Vector<Type>::ConstIterator
    {
    public:
        using pointer = typename Vector::pointer;
        using reference = typename Vector::reference;
        using IteratorType = typename ConstIterator::IteratorType;
        friend class Vector;

        explicit Iterator(pointer currentElement, Vector *collection,
                          IteratorType iteratorType = IteratorType::REGULAR)
            : ConstIterator(currentElement, collection, iteratorType)
        {}

        Iterator(const ConstIterator &other)
                : ConstIterator(other)
        {}

        Iterator &operator++()
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

        Iterator &operator--()
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

        bool operator==(const ConstIterator& other) const
        {
            return ConstIterator::operator==(other);
        }

        bool operator!=(const ConstIterator& other)
        {
            return !operator==(other);
        }
    };

}

#endif // AISDI_LINEAR_VECTOR_H
