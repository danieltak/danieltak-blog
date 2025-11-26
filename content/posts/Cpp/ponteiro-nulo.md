---
title: "Ponteiro Nulo - NULL e nullptr"
date: '2024-03-21T21:11:32-03:00'
# weight: 1
# aliases: ["/first"]
tags: ["Ponteiros","null"]
categorias: ["C++"]
author: "danieltak"
# author: ["Me", "You"] # multiple authors
showToc: true
TocOpen: false
draft: false
hidemeta: false
comments: false
description: "Valor de ponteiro nulo."

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
    image: "<image path/url>" # image path/url
    alt: "<alt text>" # alt text
    caption: "<text>" # display caption under cover
    relative: false # when using page bundles set this to true
    hidden: true # only hide on current single page
editPost:
    URL: "https://github.com/danieltak/danieltak-blog/blob/master/content"
    Text: "Sugerir Alterações" # edit text
    appendFilePath: true # to append file path to Edit link
---

## Introdução

Neste post eu irei explicar o que é um ponteiro nulo no C++ e se devemos usar o [NULL][2] ou [nullptr][3]?

TL;DR; use a palavra-chave `nullptr` no C++11 ou posterior, mesmo que o NULL seja um typedef para o `nullptr`.

Até o C++11 o ponteiro nulo era usado como um valor igual a 0 (ou NULL, sempre #definido como zero) nem era um tipo de ponteiro. Isso pode levar a alguns problemas em alguns casos, para isso o tipo [std::nullptr_t][4] foi introduzido.

### O que é?

O valor de ponteiro nulo é um valor salvo para indicar que o ponteiro ou referência não se refere a um objeto válido. De acordo com o padrão C++11:

>“Uma expressão constante inteira com o valor 0, ou uma expressão convertida para o tipo void *, é chamada de constante de ponteiro nulo. Se uma constante de ponteiro nulo for convertida em um tipo de ponteiro, o ponteiro resultante, chamado de ponteiro nulo, tem garantia de comparação desigual a um ponteiro para qualquer objeto ou função.

### Onde posso usar?

- Para inicializar uma variável de ponteiro quando essa variável de ponteiro ainda não recebeu nenhum endereço de memória válido.
- Para verificar um ponteiro nulo antes de acessar qualquer variável de ponteiro. Ao fazer isso, podemos realizar o tratamento de erros em código relacionado a ponteiros, por exemplo, desreferenciar uma variável de ponteiro apenas se ela não for NULL.
- Para passar um ponteiro nulo para um argumento de função quando não queremos passar nenhum endereço de memória válido.
- Um ponteiro NULL é usado em estruturas de dados como árvores, listas vinculadas, etc. para indicar o fim.

## Problema do NULL

Imagine que você tenha as duas declarações de função a seguir:

```cpp
void func(int myInt); 
void func(char *myPointer);
 
func( NULL ); // Adivinha qual função é chamada?
```

Embora pareça que a segunda função será chamada - afinal, você está passando o que parece ser um ponteiro - na verdade é a primeira função que será chamada! A ambiguidade ocorre, pois como NULL é 0 e 0 é um número inteiro, a primeira versão de func será chamada. Esse é o tipo de coisa que, sim, não acontece o tempo todo, mas quando acontece é extremamente frustrante e confuso. Se você não soubesse os detalhes do que está acontecendo, poderia parecer um bug do compilador. 

Um recurso de linguagem que parece um bug do compilador não é algo que você deseja.

No C++ 11, `nullptr` é uma nova palavra-chave que pode (e deve!) ser usada para representar ponteiros nulos. Na maioria dos compiladores o NULL é um typedef para 0 e nullptr, mas não podemos depender do compilador, para isso use a palavra-chave nullptr em todos os casos.

## Código

Com o seguinte código podemos realizar alguns testes e verificar como cada compilador e Sistema Operacional lhida com os ponteiros nulos.

```cpp
#include <iostream>
#include <cstddef>
#include <cxxabi.h>
#include <memory>

    std::string demangled(std::string const& sym) {
        std::unique_ptr<char, void(*)(void*)>
            name{abi::__cxa_demangle(sym.c_str(), nullptr, nullptr, nullptr), std::free};
        return {name.get()};
    }

int main()
{
        if( NULL == nullptr )
    {
        std::cout << "It is a fu***ng nullptr!!!" << "\n";
    }

    if( NULL == 0 )
    {
        std::cout << "It is a fu***ng integer!!!" << "\n";
    }

    if( 0 == nullptr )
    {
        std::cout << "nullptr is a fu***ng 0!!!" << "\n";
    }

    auto nullvar = NULL;
    auto nullptrvar = nullptr;
    std::cout << "The type of nullvar is " << typeid(nullvar).name() << "\n";
    std::cout << "The type of nullptrvar is " << typeid(nullptrvar).name() << "\n";

    if constexpr(std::is_same_v<decltype(NULL), std::nullptr_t>)
        std::cout << "NULL implemented with type std::nullptr_t" << "\n";
    else
        std::cout << "NULL implemented using an integral type" << "\n";

    if constexpr(std::is_same_v<decltype(nullptr), std::nullptr_t>)
        std::cout << "nullptr implemented with type std::nullptr_t" << "\n";
    else
        std::cout << "nullptr implemented using an integral type" << "\n";

    std::cout << demangled(typeid(nullvar).name()) << "\n";
    std::cout << demangled(typeid(nullptrvar).name()) << "\n";

    return 0;
}
```

No Windows no meu Laptop o seguinte foi obtido:

```
It is a fu***ng nullptr!!! 
It is a fu***ng integer!!! 
nullptr is a fu***ng 0!!! 
The type of nullvar is  x 
The type of nullptrvar is  Dn 
NULL implemented using an integral type 
nullptr implemented with type std::nullptr_t 
"long long" 
"decltype(nullptr)"
```

No Linux em um sistema embarcado:

```
It is a fu***ng nullptr!!!
It is a fu***ng integer!!!
nullptr is a fu***ng 0!!!
The type of nullvar is  l
The type of nullptrvar is  Dn
NULL implemented using an integral type
nullptr implemented with type std::nullptr_t
"long"
"decltype(nullptr)"
```

## __null

Você pode se deparar com o [__null][7], ele é exclusivo do G++ é similar à palavra-chave `nullptr` do C++11.

>De qualquer forma, você não deve usar `__null` porque é um detalhe de implementação do g++, portanto, usá-lo garante código não portável. Se você pode usar o C++11 (com certeza já pode?), use `nullptr`. Caso contrário, `NULL` é sua única opção portátil.

## Referências

- [nullptr na Microsoft][1]

[1]: https://learn.microsoft.com/en-us/cpp/extensions/nullptr-cpp-component-extensions?view=msvc-170

- [NULL][2]

[2]: https://en.cppreference.com/w/cpp/types/NULL

- [nullptr][3]

[3]: https://en.cppreference.com/w/cpp/language/nullptr

- [std::nullptr_t][4]

[4]: https://en.cppreference.com/w/cpp/types/nullptr_t

- [Better types in C++11 - nullptr][5]

[5]: https://www.cprogramming.com/c++11/c++11-nullptr-strongly-typed-enum-class.html

- [What is the nullptr keyword, and why is it better than NULL?][6]

[6]: https://stackoverflow.com/questions/1282295/what-is-the-nullptr-keyword-and-why-is-it-better-than-null

- [What is the difference between NULL and __null in C++?][7]

[7]: https://stackoverflow.com/questions/53963646/what-is-the-difference-between-null-and-null-in-c
