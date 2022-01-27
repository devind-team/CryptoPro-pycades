Пример использования pycades
===
Для работы примеров необходим сертификат с привязкой к закрытому ключу.

Тестовый сертификат можно установить с помощью команды (для amd64):
```bash
/opt/cprocsp/bin/amd64/cryptcp -createcert -dn "CN=test" -provtype 80 -cont '\\.\HDIMAGE\test' -ca https://cryptopro.ru/certsrv
```

В данном разделе
---

[Пример создания и проверки подписи](/cades/pycades/pycades-samples/pycades-sign-verify.md)<br>
[Пример создания и проверки отделенной подписи формата CAdES-BES по хэш-значению данных](/cades/pycades/pycades-samples/pycades-signhash-verifyhash.md)<br>
[Пример создания и проверки подписи документа XML](/cades/pycades/pycades-samples/pycades-sign-verify-xml.md)<br>
[Пример шифрования и расшифрования данных](/cades/pycades/pycades-samples/pycades-encrypt-decrypt.md)<br>

