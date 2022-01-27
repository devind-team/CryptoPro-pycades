#ifndef PHP_ABOUT_H_
#define PHP_ABOUT_H_

#include "CPPCadesAbout.h"
#include "php.h"

//объявление структуры, которая свяжет объект оборачиваемого класса
//с объектом php
struct about_obj {
    zend_object zo;
    boost::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesAboutObject>
        m_pCppCadesImpl;
};

//хэндлеры для обработки объектов оборачиваемого класса
extern zend_object_handlers about_obj_handlers;

extern zend_class_entry *about_ce;

//функция освобождения памяти. используется при уничтожении объектов
void about_free_storage(void *object TSRMLS_DC);

//функция создания хэндлера для нового объекта класса. используется при
//создании новых объектов
zend_object_value about_create_handler(zend_class_entry *type TSRMLS_DC);

//функция инициализации класса. должна включаться в
//функцию, инициализации модуля
void about_init(TSRMLS_D);

#endif
