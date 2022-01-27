#include "stdafx.h"
#include "PHPCadesAbout.h"
#include "PHPCadesVersion.h"
using namespace CryptoPro::PKI::CAdES;

//Полное объявление структуры

//Методы
PHP_METHOD(About, __construct) {
    about_obj *obj =
        (about_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    obj->m_pCppCadesImpl =
        boost::shared_ptr<CPPCadesAboutObject>(new CPPCadesAboutObject());
}

PHP_METHOD(About, get_MajorVersion) {
    unsigned int version;
    about_obj *obj =
        (about_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_MajorVersion(&version));

    RETURN_LONG(version);
}

PHP_METHOD(About, get_MinorVersion) {
    unsigned int version;

    about_obj *obj =
        (about_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_MinorVersion(&version));

    RETURN_LONG(version);
}

PHP_METHOD(About, get_BuildVersion) {
    unsigned int version;

    about_obj *obj =
        (about_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_BuildVersion(&version));

    RETURN_LONG(version);
}

PHP_METHOD(About, get_Version) {
    CAtlString AtlVersion;

    about_obj *obj =
        (about_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_Version(AtlVersion));

    RETURN_ATL_STRING(AtlVersion);
}

PHP_METHOD(About, PluginVersion) {

    boost::shared_ptr<CPPVersionObject> version;

    about_obj *obj =
        (about_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_PluginVersion(version));

    object_init_ex(return_value, version_ce);
    version_obj *pPluginVersion =
        (version_obj *)zend_object_store_get_object(return_value TSRMLS_CC);
    pPluginVersion->m_pCppCadesImpl = version;
}

PHP_METHOD(About, CSPVersion) {

    boost::shared_ptr<CPPVersionObject> version;
    char *szProvName;
    int szProvName_len = 0;
    DWORD dwProvType = 75;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|sl", &szProvName,
                              &szProvName_len, &dwProvType) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    CAtlString provName =
        CAtlString(CA2CT(CAtlStringA(szProvName, szProvName_len), CP_UTF8));
    about_obj *obj =
        (about_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    HR_ERRORCHECK_RETURN(
        obj->m_pCppCadesImpl->get_CSPVersion(provName, dwProvType, version));

    object_init_ex(return_value, version_ce);
    version_obj *pCSPVersion =
        (version_obj *)zend_object_store_get_object(return_value TSRMLS_CC);
    pCSPVersion->m_pCppCadesImpl = version;
}

//Вспомогательные функции обертки
zend_object_handlers about_obj_handlers;
zend_class_entry *about_ce;

void about_free_storage(void *object TSRMLS_DC) {
    about_obj *obj = (about_obj *)object;
    obj->m_pCppCadesImpl.reset();

    zend_hash_destroy(obj->zo.properties);
    FREE_HASHTABLE(obj->zo.properties);

    efree(obj);
}

zend_object_value about_create_handler(zend_class_entry *type TSRMLS_DC) {
    zend_object_value retval;

    about_obj *obj = (about_obj *)emalloc(sizeof(about_obj));
    memset(obj, 0, sizeof(about_obj));
    obj->zo.ce = type;

    ALLOC_HASHTABLE(obj->zo.properties);
    zend_hash_init(obj->zo.properties, 0, NULL, ZVAL_PTR_DTOR, 0);
#if PHP_VERSION_ID < 50399
    zval *tmp;
    zend_hash_copy(obj->zo.properties, &(type->default_properties),
                   (copy_ctor_func_t)zval_add_ref, (void *)&tmp,
                   sizeof(zval *));
#else
    object_properties_init(&obj->zo, type);
#endif

    retval.handle =
        zend_objects_store_put(obj, NULL, about_free_storage, NULL TSRMLS_CC);
    retval.handlers = &about_obj_handlers;

    return retval;
}

//связывание методов класса в function entry
zend_function_entry about_methods[] = {
    PHP_ME(About, __construct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(About, get_MajorVersion, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(About, get_MinorVersion, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(About, get_BuildVersion, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(About, get_Version, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(About, CSPVersion, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(About, PluginVersion, NULL, ZEND_ACC_PUBLIC){NULL, NULL, NULL}};

void about_init(TSRMLS_D) {
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "About", about_methods);
    about_ce = zend_register_internal_class(&ce TSRMLS_CC);
    about_ce->create_object = about_create_handler;
    memcpy(&about_obj_handlers, zend_get_std_object_handlers(),
           sizeof(zend_object_handlers));
    about_obj_handlers.clone_obj = NULL;
}
