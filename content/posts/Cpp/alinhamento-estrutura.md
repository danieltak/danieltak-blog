---
title: "Alinhamento, Preenchimento e Empacotamento de Estruturas de Dados"
date: '2024-02-06T21:11:32-03:00'
# weight: 1
# aliases: ["/first"]
tags: ["Estrutura","struct"]
categorias: ["C++"]
author: "danieltak"
# author: ["Me", "You"] # multiple authors
showToc: true
TocOpen: false
draft: false
hidemeta: false
comments: false
description: "Alignment, padding and packing."
disableHLJS: true # to disable highlightjs
disableShare: false
disableHLJS: false
hideSummary: false
searchHidden: false
ShowReadingTime: false
ShowBreadCrumbs: true
ShowPostNavLinks: true
ShowWordCount: true
ShowRssButtonInSectionTermList: true
UseHugoToc: true
cover:
    image: images/alinhamento-estrutura/Bits_and_Bytes.png # image path/url
    alt: "Fcarmody, CC BY-SA 4.0 <https://creativecommons.org/licenses/by-sa/4.0>, via Wikimedia Commons" # alt text
    caption: "fonte: https://commons.wikimedia.org/wiki/File:Bits_and_Bytes.svg" # display caption under cover
    relative: false # when using page bundles set this to true
    hidden: false # only hide on current single page
    hiddenInSingle: false
    responsiveImages: true
editPost:
    URL: "https://github.com/danieltak/danieltak-blog/blob/master/content"
    Text: "Sugerir Alterações" # edit text
    appendFilePath: true # to append file path to Edit link
---


## O que é?

O [alinhamento][1] de estruturas de dados é a forma que um dado é organizado e acessado na memória do computador. E pode ser organizado em três temas:

- Data alignment - alinhamento de dados
- Data structure padding - preenchimento da estrutura de dados
- Data structure packing - empacotamento da estrutura de dados

## Alinhamento

Na maioria dos cenários, você nunca precisa se preocupar com o alinhamento porque o alinhamento padrão já é ideal. Mas ao trabalhar com baixo nível e sistemas embarcados, frequentemente irá se deparar com este assunto.

### Função alignof

Para obter o alinhamento, em bytes, o operador [alignof()][4] pode ser usado.

A seguinte estrutura possui um alinhamento de 4 bytes e será explicado na sessão [Preenchimento](#preenchimento).

```cpp
#include <iostream>

struct TestStructure
{
   char AA;
   int BB;
   char CC;
};

int main()
{
    struct TestStructure test;
    
    std::cout << "Size of TestStructure alignment: " << alignof(test) << std::endl;
}
```

### Função alignas

Para especificar o alinhamento de uma estrutura o especificador [alignas()][5] pode ser usado.

```cpp
#include <iostream>

struct alignas(8) MyAlignedStructure {};

struct TestStructure
{
   char AA;
   int BB;
   char CC;
};

int main()
{
    struct TestStructure test;
    struct MyAlignedStructure testAlignedAs;
    
    std::cout << "Size of TestStructure alignment: " << alignof(test) << std::endl;
    std::cout << "Size of MyAlignedStructure alignment: " << alignof(testAlignedAs) << std::endl;
}
```

Resultado:

```
Size of TestStructure alignment: 4
Size of MyAlignedStructure alignment: 8
```

Quando múltiplos alignas são aplicados à mesma declaração, aquele com o maior valor é usado. Um alignas valor de 0 é ignorado.

```cpp
#include <iostream>

struct alignas(8) alignas(16) MyAlignedStructure {};

struct TestStructure
{
   char AA;
   int BB;
   char CC;
};

union alignas(0) U1
{
    int i;
    float f;
};

union U2
{
    int i;
    float f;
};

int main()
{
    struct TestStructure test;
    struct MyAlignedStructure testAlignedAs;
    union U1 firstUnion;
    union U2 secondUnion;
    
    std::cout << "Size of TestStructure alignment: " << alignof(test) << std::endl;
    std::cout << "Size of MyAlignedStructure alignment: " << alignof(testAlignedAs) << std::endl;
    std::cout << "Size of firstUnion alignment: " << alignof(firstUnion) << std::endl;
    std::cout << "Size of secondUnion alignment: " << alignof(secondUnion) << std::endl;
}
```

Resultado:

```
Size of TestStructure alignment: 4
Size of MyAlignedStructure alignment: 16
Size of firstUnion alignment: 4
Size of secondUnion alignment: 4
```

Você pode fornecer um tipo como o valor de alinhamento. O alinhamento padrão do tipo é usado como o valor de alinhamento.

```cpp
#include <iostream>

union alignas(long) U1
{
    int i;
    float f;
};

union U2
{
    int i;
    float f;
};

int main()
{
    union U1 firstUnion;
    union U2 secondUnion;
    
    std::cout << "Size of firstUnion alignment: " << alignof(firstUnion) << std::endl;
    std::cout << "Size of secondUnion alignment: " << alignof(secondUnion) << std::endl;
}
```

Resultado:

```
Size of firstUnion alignment: 8
Size of secondUnion alignment: 4
```

Um pacote de parâmetros de modelo `(alignas (pack...))` pode ser usado para o valor de alinhamento. O maior valor de alinhamento de todos os elementos da embalagem é usado.

```cpp
#include <iostream>

template <typename... Ts>
class alignas(Ts...) C2
{
    char c;
};


int main()
{
    C2<> c1;
    C2<short, int> c4;
    C2<int, float, double> c8;
    
    std::cout << "Size of c1 alignment: " << alignof(c1) << std::endl;
    std::cout << "Size of c4 alignment: " << alignof(c4) << std::endl;
    std::cout << "Size of c8 alignment: " << alignof(c8) << std::endl;

    return 0;
}
```

Resultado:

```
Size of c1 alignment: 1
Size of c4 alignment: 4
Size of c8 alignment: 8
```

## Preenchimento

A maioria dos compiladores, quando você declara um `struct`, insere preenchimento entre os membros para garantir que eles sejam alinhados aos endereços apropriados na memória (geralmente um múltiplo do tamanho do tipo). Isso evita a penalidade de desempenho (ou erro total) em algumas arquiteturas associadas ao acesso a variáveis que não estão alinhadas corretamente.

No exemplo abaixo, temos duas variáveis do tipo `char`, `AA` e `CC`, e uma do tipo `int`, nomeada `BB`.

```cpp
#include <iostream>

struct TestStructure
{
   char AA;
   int BB;
   char CC;
};

int main()
{
    struct TestStructure test;
    
    std::cout << "Size of char:" << " " << sizeof(test.AA) << std::endl;
    std::cout << "Size of int:" << " " << sizeof(test.BB) << std::endl;
    std::cout << "Size of char:" << " " << sizeof(test.CC) << std::endl;
}
```

O tamanho individual de cada variável foi obitda com a função `sizeof()` e a seguinte saída:

```
Size of char: 1
Size of int: 4
Size of char: 1
```

> Qual é o tamanho da struct?

Intuitivamente falamos que seria a soma das variáveis da estrutura, ou seja, 6 bytes.

Porém, essa afirmação está errada e usando a função `sizeof()`, verificamos que o tamanho da estrutura é de 12 bytes!

Isso ocorre por causa do preenchimento (padding), conforme ilustrado abaixo:

```
|   1   |   2   |   3   |   4   |
| AA(1) | pad.................. |  // 1 byte + 3 bytes pad
| BB(1) | BB(2) | BB(3) | BB(4) |  // 4 bytes
| CC(1) | pad.................. |  // 1 byte + 3 bytes pad
```

A variável AA ocupa 4 bytes, sendo 1 byte a variável e 3 bytes de preenchimento.

## #pragma pack

O [#pragma pack][6] instrui o compilador a empacotar os membros da estrutura com um alinhamento específico. A maioria dos compiladores, quando você declara um struct, insere preenchimento entre os membros para garantir que eles sejam alinhados aos endereços apropriados na memória (geralmente um múltiplo do tamanho do tipo de dado).

Então ao especificar `#pragma pack(1)`, o alinhamento é de 1 byte para todos os membros do escopo daquela definição. Menos para as struturas que forem sobrescritas com `alignas()` ou outra forma de alterar o alinhamento.

```cpp
#include <iostream>
#pragma pack(1)
struct alignas(2)  MyAlignedStructure {};

struct TestStructure
{
   char AA;
   int BB;
   char CC;
};

int main()
{
    struct TestStructure test;
    struct MyAlignedStructure testAlignedAs;
    
    std::cout << "Size of TestStructure alignment: " << alignof(test) << std::endl;
    std::cout << "Size of MyAlignedStructure alignment: " << alignof(testAlignedAs) << std::endl;
    
    std::cout << "Size of testAlignedAs struct:" << " " << sizeof(testAlignedAs) << std::endl;
    std::cout << "Size of test struct:" << " " << sizeof(test) << std::endl;
}
```

Resultado:

```
Size of TestStructure alignment: 1
Size of MyAlignedStructure alignment: 2
Size of testAlignedAs struct: 2
Size of test struct: 6
```

Então com o alinhamento de 1 byte, o tamanho da estrutura é a soma de seus membros.

> E ao utilizar um alinhamento de 2 bytes?

```cpp
#include <iostream>
#pragma pack(2)
struct alignas(2)  MyAlignedStructure {};

struct TestStructure
{
   char AA;
   int BB;
   char CC;
};

int main()
{
    struct TestStructure test;
    struct MyAlignedStructure testAlignedAs;
    
    std::cout << "Size of TestStructure alignment: " << alignof(test) << std::endl;
    std::cout << "Size of MyAlignedStructure alignment: " << alignof(testAlignedAs) << std::endl;
    
    std::cout << "Size of testAlignedAs struct:" << " " << sizeof(testAlignedAs) << std::endl;
    std::cout << "Size of test struct:" << " " << sizeof(test) << std::endl;
}
```

Resultado:

```
Size of TestStructure alignment: 2
Size of MyAlignedStructure alignment: 2
Size of testAlignedAs struct: 2
Size of test struct: 8
```

Então a estrutura é empacotada da seguinte forma:

```
|   1   |   2   |
| AA(1) | pad.. |  // 1 byte + 1 byte pad
| BB(1) | BB(2) |  // 2 bytes
| BB(3) | BB(4) |  // 2 bytes
| CC(1) | pad.. |  // 1 byte + 1 byte pad
```

### Problema

O [artigo ][7] "Anybody who writes #pragma pack(1) may as well just wear a sign on their forehead that says “I hate RISC”" explica os riscos de usar o `#pragma pack(1)`.

Isso é verdade em sistemas desktop, porém em sistemas embarcados, nem tanto...

Em muitos casos o gargalo não está no processamento, mas em outros locais, como a comunicação. Então a perda de desempenho na otimização do processamento se torna aceitável, ao ganhar mais espaço para criar um pacote de dados e evitar os preenchimentos, ou até mesmo para dar compatibilidade entre dispositivos diferentes.

Portanto, cada caso deve ser analisado e não existem dogmas.

### Opinião

**Não utilizar as diretivas de compilador** `#pragma`, pois ela é dependente do compilador utilizado. A maioria dos compiladores possuem suporte e um comportamento similar, mas em raros casos isso não é verdade. E é bem quando você precisar entregar o projeto atrasado, que a nova versão de um compilador pode quebrar tudo.

Esse tipo de abordagem é muito utilizado por programador de C ou programadores muito experientes acostumados com o C++ 98.

O recomendado é se manter no STL do C++ e usar as funções padrões fornecidas e testadas pelo mundo inteiro.

Mas nos casos em que é necessário usar o pragma pack, opte por usar o `push` e o `pop`.

## Aprofundamento

A principal referência é o [The Lost Art of Structure Packing][3], um guia em inglês que aborda em outras linguagens de programação.

Também é [possível usar as diretivas](https://stackoverflow.com/q/74239354/7690982) `#pragma pack(push, n)` e `#pragma pack(pop)`.

Um [artigo no Geek for Geeks][8] é sempre recomendado.

## Referências

- [Alinhamento - Microsoft C++][1]

[1]: https://learn.microsoft.com/pt-br/cpp/cpp/alignment-cpp-declarations?view=msvc-170

- [Structure padding and packing][2]

[2]: https://stackoverflow.com/q/4306186/7690982

- [The Lost Art of Structure Packing][3]

[3]: http://www.catb.org/esr/structure-packing/

- [alignof() - Cpp Reference][4]

[4]: https://en.cppreference.com/w/cpp/language/alignof

- [alignas() - Cpp Reference][5]

[5]: https://en.cppreference.com/w/cpp/language/alignas

- [#pragma pack effect][6]

[6]: https://stackoverflow.com/questions/3318410/pragma-pack-effect

- [Anybody who writes #pragma pack(1) may as well just wear a sign on their forehead that says “I hate RISC”][7]

[7]: https://devblogs.microsoft.com/oldnewthing/20200103-00/?p=103290

- [Structure Member Alignment, Padding and Data Packing][8]

[8]: https://www.geeksforgeeks.org/structure-member-alignment-padding-and-data-packing/