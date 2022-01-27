/*
 * Copyright(C) 2004 Проект ИОК
 *
 * Этот файл содержит информацию, являющуюся
 * собственностью компании Крипто Про.
 *
 * Любая часть этого файла не может быть скопирована,
 * исправлена, переведена на другие языки,
 * локализована или модифицирована любым способом,
 * откомпилирована, передана по сети с или на
 * любую компьютерную систему без предварительного
 * заключения соглашения с компанией Крипто Про.
 */

/*!
 * \file $RCSfile$
 * \version $Revision$
 * \date $Date::                           $
 * \author $Author$
 *
 * \brief Обертки для stl классов, позволяющие их экспортировать в dll.
 */

#ifndef _CPSTLDLL_H_INCLUDED
#define _CPSTLDLL_H_INCLUDED

#include <list>

#if defined UNIX
#   define CDllList std::list
#   define EXPIMP_CDLLLIST_ITERATORS(...)
#else // !defined UNIX

#ifdef NO_EXPIMP_CDLLLIST_ITERATORS
#   define EXPIMP_CDLLLIST_ITERATORS(...)
#else
#   define EXPIMP_CDLLLIST_ITERATORS(Type, Extern, Declspec) \
	__pragma(warning(push)); \
	__pragma(warning(disable: 4231)); \
	Extern template class Declspec CDllList<Type>::_Const_iterator; \
	Extern template class Declspec CDllList<Type>::_Iterator; \
	__pragma(warning(pop));
#endif

namespace CryptoPro {

/**
 * \class CDllList cpstldll.h <cpstldll.h>
 * \brief Класс списка аналогичный по интерфейсу классу std::list из библиотеки
 * стандартных шаблонов.
 */
template<class _Ty>
class CDllList
{
    typedef typename std::list<_Ty> stlContainer;
    typedef CDllList<_Ty> _Myt;
    typedef typename stlContainer::pointer _Tptr;
    typedef typename stlContainer::reference _Reft;
#ifdef _STL70_
    typedef typename stlContainer::iterator cont_const_iterator;
#else
    typedef typename stlContainer::const_iterator cont_const_iterator;
#endif
    typedef typename stlContainer::iterator cont_iterator;
public:
    typedef typename stlContainer::allocator_type allocator_type;
    typedef typename stlContainer::size_type size_type;
    typedef typename stlContainer::difference_type difference_type;
    typedef typename stlContainer::pointer pointer;
    typedef typename stlContainer::const_pointer const_pointer;
    typedef typename stlContainer::reference reference;
    typedef typename stlContainer::const_reference const_reference;
    typedef typename stlContainer::value_type value_type;
    typedef typename stlContainer::const_reverse_iterator const_reverse_iterator;
    typedef typename stlContainer::reverse_iterator reverse_iterator;

    class _Const_iterator
#if defined(_MSC_VER) && (_MSC_VER >= 1500) && (_MSC_VER < 1600) && !defined ( _STL70_ )
	// Чтобы VS2008 считала итератор за checked
	: public std::_Iterator_base_universal
#endif // defined(_MSC_VER) && (_MSC_VER >= 1500) && (_MSC_VER < 1700)
    {
	friend CDllList;

	cont_const_iterator *pImpl_;

	_Const_iterator(const cont_const_iterator it);

    public:
#if defined(_MSC_VER) && (_MSC_VER >= 1500) && (_MSC_VER < 1600)	
	typedef std::_Range_checked_iterator_tag _Checked_iterator_category;
#endif //defined(_MSC_VER) && (_MSC_VER >= 1500) && (_MSC_VER < 1700)	

	typedef std::bidirectional_iterator_tag iterator_category;
	typedef _Ty value_type;
	typedef typename stlContainer::difference_type difference_type;
	typedef typename stlContainer::const_pointer pointer;
	typedef typename stlContainer::const_reference reference;

	_Const_iterator();
	~_Const_iterator();

	_Const_iterator(const _Const_iterator& _Right);
	_Const_iterator& operator=(const _Const_iterator& _Right);

	const_reference operator*() const;
	const_pointer operator->() const;
	_Const_iterator& operator++();
	_Const_iterator operator++(int);
	_Const_iterator& operator--();
	_Const_iterator operator--(int);
	bool operator==(const _Const_iterator& _Right) const;
	bool operator!=(const _Const_iterator& _Right) const;
    };

    class _Iterator : public _Const_iterator
    {
	friend CDllList;

	_Iterator(const cont_iterator it);

    public:
	_Iterator();

	_Reft operator*() const;
	_Tptr operator->() const;
	_Iterator& operator++();
	_Iterator operator++(int);
	_Iterator& operator--();
	_Iterator operator--(int);
    };

    typedef _Const_iterator const_iterator;
    typedef _Iterator iterator;

    CDllList();
    CDllList( const _Myt& _Right);
    ~CDllList();

    const_iterator begin() const;
    const_iterator end() const;
    iterator begin();
    iterator end();
    const_reverse_iterator rbegin() const;
    const_reverse_iterator rend() const;
    reverse_iterator rbegin();
    reverse_iterator rend();
    _Myt& operator=(const _Myt& _Right);
    void resize(size_type _Newsize);
    void resize(size_type _Newsize, _Ty _Val);
    size_type size() const;
    size_type max_size() const;
    bool empty() const;
    reference front();
    const_reference front() const;
    reference back();
    const_reference back() const;
    void push_front(const _Ty& _Val);
    void push_back(const _Ty& _Val);
    void pop_front();
    void pop_back();
    void assign(size_type _Count, const _Ty& _Val);
    iterator insert(iterator _Where, const _Ty& _Val);
    void insert(iterator _Where, iterator _First, iterator _Last);
    void insert(iterator _Where, size_type _Count, const _Ty& _Val);
    iterator erase(iterator _Where);
    iterator erase(iterator _First, iterator _Last);
    void clear();
    void swap(_Myt& _Right);
//    void sort();
//    void reverse();
protected:
    void* impl();
    const void* impl() const;
private:
    void* pImpl_;
};

} // namespace CryptoPro

#endif // !defined UNIX

#endif // _CPSTLDLL_H_INCLUDED
