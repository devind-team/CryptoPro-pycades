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
 * \brief Класс блоба.
 */

#ifndef _CPLIB_BLOB_H_INCLUDED
#define _CPLIB_BLOB_H_INCLUDED

#include <algorithm>
#include <list>
#include <cplib/StringProxy.h>

namespace CryptoPro {

/**
 * \class CBlob Blob.h <cplib/Blob.h>
 * \brief Двоичная последовательность произвольной длины.
 *
 * Класс предназначен для хранения двоичной последовательности.
 * Может использоваться как для хранения закодированных ASN.1 структур,
 * так и для хранения произвольных двоичных данных.
 *
 */
class CPLIB_CLASS CBlob
{
public:
    /// Создает пустой объект
    CBlob();
    /**
     * \brief Создает и инициализирует объект
     *
     * \param ptr [in] указатель на начало данных помещаемых в объект
     * \param length [in] длина данных в байтах
     * \remarks При инициализации объект отводит память под хранимые
     * данные и копирует их туда из указанного в агрументе ptr места.
     */
    CBlob(const unsigned char *ptr, unsigned long length );
    /**
     * \brief Создает объект
     *
     * \param length [in] длина данных в байтах
     * \remarks При инициализации объект отводит указанное количество памяти
     * под данные.
     */
    CBlob( unsigned long length );
    /// Уничтожает объект.
    ~CBlob();

    /**
     * \brief Создает копию заданного объекта.
     *
     * \param src [in] объект, копия которого создается
     */
    CBlob( const CBlob &src );
    /**
     * \brief Копирует заданный объект в текущий.
     *
     * \param src [in] объект, который копируется в текущий
     * \return Ссылка на текущий объект.
     */
    CBlob& operator=( const CBlob &src );

    /**
     * \brief Операция конкатенации (присоединения).
     *
     * \param right [in] объект, присоединяемый к текущему
     * \remarks При выполнении этой операции в конец текущего объекта присоединяются
     * данные, скопированные из заданного объекта.
     * \return Ссылка на текущий объект.
     */
    CBlob& operator+=( const CBlob &right );
    /**
     * \brief Операция проверки на равенство.
     *
     * \param src [in] объект для сравнения
     * \remarks Производится побитовое сравнение объектов.
     * \return true в случае равенства, false в другом случае.
     */
    bool operator==( const CBlob &src ) const;
    /**
     * \brief Операция проверки на неравенство.
     *
     * \param src [in] объект для сравнения
     * \remarks Производится побитовое сравнение объектов.
     * \return true в случае неравенства, false в другом случае.
     */
    bool operator!=( const CBlob &src ) const;
    /**
     * \brief Операция лексикографического сравнения (меньше).
     *
     * \param src [in] объект для сравнения
     * \return true в случае если текущий объект меньше, false в другом случае.
     */
    bool operator<( const CBlob &src ) const;
    /**
     * \brief Операция лексикографического сравнения (меньше или равно).
     *
     * \param src [in] объект для сравнения
     * \return true в случае если текущий объект меньше или равен, false в другом случае.
     */
    bool operator<=( const CBlob &src ) const;
    /**
     * \brief Операция лексикографического сравнения (больше).
     *
     * \param src [in] объект для сравнения
     * \return true в случае если текущий объект больше, false в другом случае.
     */
    bool operator>( const CBlob &src ) const;
    /**
     * \brief Операция лексикографического сравнения (больше или равно).
     *
     * \param src [in] объект для сравнения
     * \return true в случае если текущий объект больше или равен, false в другом случае.
     */
    bool operator>=( const CBlob &src ) const;

    /**
     * \brief Изменение размера объекта.
     *
     * \param length [in] новая длина данных
     * \remarks Если length больше текущей длины, то старые данные
     * в позициях от нуля до текущей длины не меняют своего значения.
     * Если length меньше текущей длины, то сохраняются данные на
     * позициях от 0 до length-1.
     */
    void resize_to( unsigned long length );
    /**
     * \brief Операция обмена объектов.
     *
     * \param right [in] объект для обмена
     * \remarks Функция не генерирует исключений.
     */
    void swap( CBlob &right ) throw();
    /// Инвертирование порядка байт данных.
    void reverse();
    /**
     * \brief Очищение объекта
     * 
     * Объект очищается и становится нулевой длины
     */
    void clear();
    /**
     * \brief Помещение данных в объект
     * 
     * \param ptr [in] указатель на начало данных
     * \param length [in] длина данных
     */
    void assign(const unsigned char *ptr, unsigned long length );
    void readFromFile( const char *name );
    void writeToFile( const char *name ) const;
    void readFromFile( const wchar_t *name );
    void writeToFile( const wchar_t *name ) const;
    void readFromHexString( const char *str );
    CStringProxy writeToHexString(unsigned long SpaceInterval = 0) const;

    unsigned long cbData() const;
    unsigned char* pbData() const;
private:
    unsigned long m_cbData;
    unsigned char *m_pbData;
};

// VS2008 bug/feature: Экспорт инстанцированных шаблонов вложенных классов
// (здесь - итераторов) должен предварять экспорт инстанцированного шаблона
// внешнего класса (здесь - CDllList<>), иначе из DLL не будут экспортированы
// методы вложенных классов.
EXPIMP_CDLLLIST_ITERATORS(CBlob, CPLIB_EXTERN_TEMPLATE, CPLIB_CLASS);

/// Список объектов CBlob
class CPLIB_CLASS CBlobList: public CDllList<CBlob> {};

} // namespace CryptoPro

#endif // _CPLIB_BLOB_H_INCLUDED
