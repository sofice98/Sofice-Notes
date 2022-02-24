vscode调试-添加配置 就可不用每次出来debug configuration



argparse 是python自带的命令行参数解析包

```python
import argparse

def main():
    parser = argparse.ArgumentParser(description="Demo of argparse")
    parser.add_argument('-n','--name', default=' Li ')
    parser.add_argument('-y','--year', default='20')
    args = parser.parse_args()
    print(args)
    name = args.name
    year = args.year
    print('Hello {}  {}'.format(name,year))

if __name__ == '__main__':
    main()

```



append会原封不动的push_back，extend会迭代与原 list 相同维度进行push_back



```python
# 浮点range
from floatrange import floatrange
```

