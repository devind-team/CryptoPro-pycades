Расширение для Python
===
Pycades представляет собой расширение для Python3. Расширение реализует интерфейс, аналогичный [CAdESCOM](https://docs.cryptopro.ru/cades/reference/cadescom).
Расширение предназначено для встраивания криптографических операций в серверные приложения на языке Python3 с использованием сертифицированного СКЗИ КриптоПро CSP.

Расширение предоставляет программный интерфейс, аналогичный КриптоПро ЭЦП Browser plug-in, для выполнения следующих криптографических операций:
* работа с сертификатами;
* создание и проверка подписи форматов CAdES BES, CAdES-T, CAdES-X Long Type 1;
* шифрование и расшифрование данных.

### Особенности
В модуле pycades добавлены все константы из списка [свойств плагина](https://docs.cryptopro.ru/cades/plugin/plugin-methods?id=%d0%9a%d0%be%d0%bd%d1%81%d1%82%d0%b0%d0%bd%d1%82%d1%8b). 

Для создания объектов необходимо вызвать соответствующий конструктор. Для создания доступны следующие объекты:

|Объект CAdESCOM|Объект pycades|
|-|-|
|[CAdESCOM.About](https://docs.cryptopro.ru/cades/reference/cadescom/cadescom_class/about)|pycades.About|
|[CAdESCOM.CadesSignedData](https://docs.cryptopro.ru/cades/reference/cadescom/cadescom_class/cadessigneddata)|pycades.SignedData|
|[CAdESCOM.CPAttribute](https://docs.cryptopro.ru/cades/reference/cadescom/cadescom_class/cpattribute)|pycades.Attribute|
|[CAdESCOM.Certificate](https://docs.cryptopro.ru/cades/reference/cadescom/cadescom_class/cpcertificate)|pycades.Certificate|
|[CAdESCOM.CRL](https://docs.cryptopro.ru/cades/reference/cadescom/cadescom_class/cpcrl)|pycades.CRL|
|[CAdESCOM.CPEnvelopedData](https://docs.cryptopro.ru/cades/reference/cadescom/cadescom_class/cpenvelopeddata)|pycades.EnvelopedData|
|[CAdESCOM.HashedData](https://docs.cryptopro.ru/cades/reference/cadescom/cadescom_class/cphasheddata)|pycades.HashedData|
|[CAdESCOM.CPSigner](https://docs.cryptopro.ru/cades/reference/cadescom/cadescom_class/cpsigner)|pycades.Signer|
|[CAdESCOM.RawSignature](https://docs.cryptopro.ru/cades/reference/cadescom/cadescom_class/rawsignature)|pycades.RawSignature|
|[CAdESCOM.SignedXML](https://docs.cryptopro.ru/cades/reference/cadescom/cadescom_class/signedxml)|pycades.SignedXML|
|[CAdESCOM.Store](https://docs.cryptopro.ru/cades/reference/cadescom/cadescom_class/store)|pycades.Store|
|[CAdESCOM.SymmetricAlgorithm](https://docs.cryptopro.ru/cades/reference/cadescom/cadescom_class/symmetricalgorithm)|pycades.SymmetricAlgorithm|

Для получения версии модуля добавлен метод ModuleVersion().
```python
>>> import pycades
>>> pycades.ModuleVersion()
'0.1.19509'
```

Лицензирование
---
Расширение распространяется бесплатно в виде исходных кодов и для своего функционирования не требует отдельной лицензии.
Для формирования ЭЦП с использованием криптоалгоритма ГОСТ необходима лицензия на КриптоПро CSP. 
Для формирования усовершенствованной ЭЦП необходимы лицензии на КриптоПро TSP Client и КриптоПро OCSP Client.

В этом разделе
---
[Сборка расширения для языка Python](/cades/pycades/pycades-build.md)<br/>
[Установка расширения для языка Python](/cades/pycades/pycades-install.md)<br/>
[Пример использования](/cades/pycades/pycades-samples.md)<br/>
