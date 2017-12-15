#ifndef AISDI_LINEAR_LINKEDLIST_H
#define AISDI_LINEAR_LINKEDLIST_H

#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <boost/assert.hpp>

namespace aisdi
{

    template<typename Type>
    class LinkedList
    {
    public:
        using difference_type = std::ptrdiff_t;
        using size_type = std::size_t;
        using value_type = Type;
        using pointer = Type *;
        using reference = Type &;
        using const_pointer = const Type *;
        using const_reference = const Type &;

        class ConstIterator;
        class Iterator;

        using iterator = Iterator;
        using const_iterator = ConstIterator;

        struct Node
        {
            Node *prev;
            Node *next;

            explicit Node()
                : prev(nullptr),
                  next(nullptr)
            {}

            virtual ~Node() = default;
        };

        struct ValueNode : public Node
        {
            Type value;

            explicit ValueNode(const Type& value)
                : value(value)
            {}
        };

    private:
        Node *firstGuard, *lastGuard;
        size_type size;
        ConstIterator endIterator;

    public:
        explicit LinkedList()
            : firstGuard(new Node()),
              lastGuard(new Node()),
              size(0),
              endIterator(lastGuard, this)
        {
            collapseNodes(firstGuard, lastGuard);
        }

        LinkedList(std::initializer_list<Type> l)
                : LinkedList()
        {
            copyFrom(l);
        }

        LinkedList(const LinkedList &other)
                : LinkedList()
        {
            copyFrom(other);
        }

        LinkedList(LinkedList &&other) noexcept
            : LinkedList()
        {
            moveFrom(other);
        }

        ~LinkedList()
        {
            deleteList();
            delete firstGuard;
            delete lastGuard;
        }

        LinkedList &operator=(const LinkedList &other)
        {
            if (this == &other)
                return *this;

            if (!isEmpty())
                deleteList();

            copyFrom(other);

            return *this;
        }

        LinkedList &operator=(LinkedList &&other) noexcept
        {
            if (!isEmpty())
                deleteList();

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

        void append(const Type &item)
        {
            Node *nodeToAppend = new ValueNode(item);

            insertBetween(getLast(), lastGuard, nodeToAppend);

            size++;
        }

        void prepend(const Type &item)
        {
            Node *nodeToPrepend = new ValueNode(item);

            insertBetween(firstGuard, getFirst(), nodeToPrepend);

            size++;
        }

        void insert(const const_iterator &insertPosition, const Type &item)
        {
            Node *nodeToInsert = new ValueNode(item);
            Node *right = insertPosition.getCurrentNode();
            Node *left = right->prev;

            insertBetween(left, right, nodeToInsert);

            size++;
        }

        Type popFirst()
        {
            throwIfCollectionEmpty(
                    std::logic_error("cannot popFirst from empty collection"));

            ValueNode *first = getFirstValueNode();
            Type result = first->value;

            collapseNodes(firstGuard, first->next);

            deleteNode(first);

            return result;
        }

        Type popLast()
        {
            throwIfCollectionEmpty(
                    std::logic_error("cannot popLast from empty collection"));

            ValueNode *last = getLastValueNode();
            Type result = last->value;

            collapseNodes(last->prev, lastGuard);

            deleteNode(last);

            return result;
        }

        void erase(const const_iterator &possition)
        {
            throwIfCollectionEmpty(
                    std::out_of_range("cannot erase from empty collection"));

            throwIfIteratorEqaulsEnd(
                    possition,
                    std::out_of_range("cannot erase element on end iterator"));

            Node *nodeToErase = possition.getCurrentNode();

            collapseNodes(nodeToErase->prev, nodeToErase->next);

            deleteNode(nodeToErase);
        }

        void erase(const const_iterator &firstIncluded, const const_iterator &lastExcluded)
        {
            Node *left = firstIncluded.getCurrentNode()->prev;
            Node *right = lastExcluded.getCurrentNode();

            collapseNodes(left, right);

            deleteRange(firstIncluded, lastExcluded);
        }

        iterator begin()
        {
            if (isEmpty())
                return endIterator;

            return Iterator(getFirst(), this);
        }

        iterator end()
        {
            return endIterator;
        }

        const_iterator cbegin() const
        {
            if (isEmpty())
                return endIterator;

            return ConstIterator(getFirst(), this);
        }

        const_iterator cend() const
        {
            return endIterator;
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
        Node *getFirst() const
        {
            return firstGuard->next;
        }

        Node *getLast() const
        {
            return lastGuard->prev;
        }

        ValueNode *getFirstValueNode() const
        {
            return dynamic_cast<ValueNode*>(firstGuard->next);
        }

        ValueNode *getLastValueNode() const
        {
            return dynamic_cast<ValueNode*>(lastGuard->prev);
        }

        void deleteList()
        {
            if (firstGuard->next == lastGuard &&
                lastGuard->prev == firstGuard)
                return;

            for (Node *node = getFirst(); node != lastGuard; )
            {
                Node *old = node;
                node = node->next;
                delete old;
            }

            collapseList();
        }

        void deleteNode(Node *nodeToDestroy)
        {
            delete nodeToDestroy;
            size--;
        }

        void deleteRange(iterator firstIncluded, iterator lastExcluded)
        {
            size_type deletedCount = 0;
            for (auto it = firstIncluded; it != lastExcluded;)
            {
                Node *nodeToErase = it.getCurrentNode();
                it++;
                deletedCount++;
                delete nodeToErase;
            }
            size -= deletedCount;
        }

        template<class Collection>
        void copyFrom(const Collection& collection)
        {
            for (auto& el : collection)
                append(el);
        }

        void moveFrom(LinkedList& other)
        {
            collapseNodes(firstGuard, other.getFirst());
            collapseNodes(other.getLast(), lastGuard);
            size = other.size;
            other.collapseList();
        }

        void collapseList()
        {
            collapseNodes(firstGuard, lastGuard);
            size = 0;
        }

        void collapseNodes(Node *left, Node *right)
        {
            left->next = right;
            right->prev = left;
        }

        void insertBetween(Node *left, Node *right, Node *nodeToInsert)
        {
            left->next = nodeToInsert;
            nodeToInsert->prev = left;
            nodeToInsert->next = right;
            right->prev = nodeToInsert;
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
            if (iterator == endIterator)
                throw e;
        }
    };

    template<typename Type>
    class LinkedList<Type>::ConstIterator
    {
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = typename LinkedList::value_type;
        using difference_type = typename LinkedList::difference_type;
        using pointer = typename LinkedList::const_pointer;
        using reference = typename LinkedList::const_reference;

    private:
        Node *currentNode;
        const LinkedList *collection;

    public:
        explicit ConstIterator(Node *node, const LinkedList *collection)
            : currentNode(node),
              collection(collection)
        {}

        ConstIterator()
            : currentNode(nullptr),
              collection(nullptr)
        {}

        reference operator*() const
        {
            throwIfEnd(
                    std::out_of_range("end iterator cannot be dereferenced"));

            return dynamic_cast<ValueNode*>(currentNode)->value;
        }

        ConstIterator &operator++()
        {
            throwIfEnd(
                    std::out_of_range("cannot increment end iterator"));

            currentNode = currentNode->next;
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

            currentNode = currentNode->prev;
            return *this;
        }

        ConstIterator operator--(int)
        {
            ConstIterator old = *this;
            operator++();
            return old;
        }

        ConstIterator operator+(difference_type d) const
        {
            Node *node = currentNode;

            for (difference_type i = 0; i < d; i++)
                node = node->next;

            return ConstIterator(node, collection);
        }

        ConstIterator operator-(difference_type d) const
        {
            Node *node = currentNode;

            for (difference_type i = 0; i < d; i++)
                node = node->prev;

            return ConstIterator(node, collection);
        }

        bool operator==(const ConstIterator &other) const
        {
            return currentNode == other.currentNode;
        }

        bool operator!=(const ConstIterator &other) const
        {
            return !operator==(other);
        }

        friend class LinkedList;

    protected:
        Node *getCurrentNode() const
        {
            return currentNode;
        }

        template <typename Exception>
        void throwIfBegin(const Exception& e) const
        {
            if (*this == collection->begin())
                throw e;
        }

        template <typename Exception>
        void throwIfEnd(const Exception& e) const
        {
            if (*this == collection->end())
                throw e;
        }
    };

    template<typename Type>
    class LinkedList<Type>::Iterator : public LinkedList<Type>::ConstIterator
    {
    public:
        using pointer = typename LinkedList::pointer;
        using reference = typename LinkedList::reference;

        explicit Iterator(Node *currentNode, LinkedList *collection)
            : ConstIterator(currentNode, collection)
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
    };

}

#endif // AISDI_LINEAR_LINKEDLIST_H
