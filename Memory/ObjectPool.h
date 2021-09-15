#pragma once

#include <cassert>

#include "block.h"

namespace mem {

	/*
		USAGE CONDITIONS
		* The type T must satisfy sizeof(T) >= sizeof(void *).
	*/

	template <class T>
	class ObjectPool	{
	public:
		ObjectPool() : m_maxNumElements(0)
		{}

		~ObjectPool()
		{
			Destroy();
		}

		/*
		PRECONDITIONS
		* maxNumElements >= 1
		RETURN VALUE
		Returns 0 iff no error occured.
		*/
		int Create(size_t maxNumElements)
		{
			assert(maxNumElements != 0);

			m_maxNumElements = maxNumElements;

			auto error = block_allocate(&m_block, sizeof(node) * m_maxNumElements);
			if (error) {
				m_maxNumElements = 0;
				return -1;// failure
			}

			clear_free_list();

			return 0;// success
		}

		void Destroy()
		{
			m_head = nullptr;
			m_maxNumElements = 0;
			block_free(&m_block);
		}

		ObjectPool(const ObjectPool &other) = delete;
		ObjectPool & operator=(const ObjectPool &other) = delete;
		ObjectPool(const ObjectPool &&other) = delete;
		ObjectPool & operator=(const ObjectPool &&other) = delete;

		void Clear()
		{
			clear_free_list();
		}

		/*
		PRECONDITIONS
		* pp != nullptr
		RETURN VALUE
		Returns 0 iff an element was allocated.
		*/
		int AllocOneElement(T **pp)
		{
			assert(pp != nullptr);

			if (is_full()) {
				return -1;// failure
			}
			else {
				*pp = reinterpret_cast<T *>(m_head);
				m_head = m_head->next;
				return 0;// success
			}
		}

		/*
		PRECONDITIONS
		* pp is the address of a node allocated by AllocOneElement.
		*/
		void FreeOneElement(T **pp)
		{
			auto q = reinterpret_cast<node *>(*pp);
			q->next = m_head;

			m_head = q;
		}

	private:
		int is_full() const
		{
			return nullptr == m_head;
		}

		void clear_free_list()
		{
			// Initialize the linked list; all nodes are free.
			m_head = static_cast<node *>(m_block.ptr);
			auto *node = m_head;
			for (size_t i = 0; i < m_maxNumElements - 1; ++i, ++node) {
				node->next = node + 1;
			}
			// Last node
			node->next = nullptr;
		}

	private:
		size_t m_maxNumElements;

		block m_block;
		// Memory block


		// The singly linked list of free nodes

		struct node {			
			union {
				T element;

				node *next;
				// Address of the next free node or null
			};
		};

		node *m_head;

		//size_t m_numNodes;
		//// Number of nodes that the memory block can contain.
		//// m_numNodes = number free nodes + number of occupied nodes.
	};
}