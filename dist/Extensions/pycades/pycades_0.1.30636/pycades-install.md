Установка расширения для языка Python
===

---
Для запуска расширения необходимо указать путь до собранной библиотеки, например:
```python
import sys
sys.path.append(r'/path_to_pycades_so')
import pycades
```

---
Для удобства этот путь можно экспортировать в системную переменную PYTHONPATH.
```bash
echo 'export PYTHONPATH=/path_to_pycades_so' >> ~/.bashrc
source ~/.bashrc
```

В этом случае расширение будет доступно по умолчанию.
```python
>>> import pycades
>>> pycades.ModuleVersion()
'0.1.19595'
```
