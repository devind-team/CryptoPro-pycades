Сборка расширения для языка Python
===
Сборка производится на Ubuntu 20.04.

1. Установить необходимые пакеты для сборки:
```
sudo apt install cmake build-essential libboost-all-dev python3-dev unzip
```
2. Скачать [архив с КриптоПро CSP](https://cryptopro.ru/products/csp/downloads), 
распаковать этот архив и установить КриптоПро CSP:
```
tar xvf linux-amd64_deb.tgz
cd linux-amd64_deb
sudo ./install.sh
```
3. Установить пакет cprocsp-devel:
```
sudo apt install ./lsb-cprocsp-devel_5.0*.deb
```
4. Скачать архив с [КриптоПро ЭЦП SDK](https://cryptopro.ru/products/cades/downloads), 
распаковать этот архив и установить пакет cprocsp-pki-cades (версия не ниже 2.0.14071)
```
tar xvf cades_linux_amd64.tar.gz
cd cades_linux_amd64
sudo apt install ./cprocsp-pki-cades*.deb
```
5. Скачать и распаковать архив с исходниками [pycades](https://cryptopro.ru/sites/default/files/products/cades/pycades/pycades.zip):
```
unzip pycades.zip
cd pycades_*
```
6. Задать значение переменной Python_INCLUDE_DIR в файле CMakeLists.txt (папка с Python.h). 
7. Выполнить сборку:
```
mkdir build
cd build
cmake ..
make -j4
```
