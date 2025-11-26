---
title: "Quebrando Dependências"
date: '2024-10-05T21:11:32-03:00'
# weight: 1
# aliases: ["/first"]
categorias: ["C++", "Software Design"]
tags: ["Software Design", "Video"]
author: "danieltak"
# author: ["Me", "You"] # multiple authors
showToc: true
TocOpen: false
draft: false
hidemeta: false
comments: false
description: "Vídeo de Klaus Iglberger."

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
    image: images/quebrando-dependencias/cube.png # image path/url
    alt: "AI Generated" # alt text
    caption: "fonte: AI generated" # display caption under cover
    relative: false # when using page bundles set this to true
    hidden: false # only hide on current single page
    hiddenInSingle: false
    responsiveImages: true
editPost:
    URL: "https://github.com/danieltak/danieltak-blog/blob/master/content"
    Text: "Sugerir Alterações" # edit text
    appendFilePath: true # to append file path to Edit link
---

## Introdução

Esse post fala sobre o vídeo do [Klaus Iglberger] no "Meeting C++ de 2022": [Breaking Dependencies: The Path to High-Quality Software][Breaking Dependencies], em uma tradução livre "Quebrando Dependências: O Caminho para Software de Alta Qualidade".

O Software precisa mudar constantemente, mas não é fácil projetar um software para atender a esses requisitos.

Definição de Design de Software:

> Design de Software é a arte de gerenciar interdependências entre componentes de software. Seu objetivo é minimizar dependências (técnicas) e introduzir as abstrações e os compromissos necessários.

Fácil de alterar, manter e testar, com abstrações para lidar com a complexidade.

### Gráfico de um projeto de software de baixa qualidade

O gráfico de um projeto de software representa Desenvolvimento de Software x Tempo. No início, ele começa como um desenvolvimento ideal, sem problemas e bem rápido, mas depois de algum tempo a qualidade começa a diminuir devido à falta de design.

- As coisas estão ficando mais difíceis de mudar
- Novos recursos se tornam mais difíceis de adicionar
- Menos tempo resta para cuidar do código

Depois de mais algum tempo:

- Mais e mais bugs aparecem
- Mais tempo é perdido na depuração
- Ainda menos tempo resta para cuidar do código

Mais tarde, mais pessoas são contratadas:

- Novos desenvolvedores precisam de treinamento
- Menos tempo para os desenvolvedores antigos

Ponto de frustração máxima:

- Difícil cumprir prazos
- Desenvolvedores deixam a empresa

### A Qualidade Importa

> Os detalhes da implementação importam, mas o design importa mais!

O design desempenha um papel muito mais central no sucesso de um projeto do que qualquer recurso jamais poderia. Um bom software não se trata exclusivamente do uso adequado de qualquer recurso, mas sim de uma arquitetura e design sólidos. Um bom design de software pode tolerar algumas decisões ruins de implementação, mas um design de software ruim não pode ser salvo apenas pelo uso heroico de recursos.


## Padrões de Design

### O Padrão de Design Clássico Factory Method (Método de Fábrica)

Define uma interface para criar um objeto, mas permite que as subclasses decidam qual classe instanciar. O Factory Method permite que uma classe adie a instanciação para subclasses.

É frequentemente usado como sinônimo de "criar algo", `std::make_unique()` é um exemplo.

Podemos separar esse padrão em Alto nível e Baixo nível, para o uso do aplicativo e os detalhes de implementação.

`std::make_unique()` não é um Factory Method, porque não permite customização, não gerencia o relacionamento entre entidades, não inverte dependências, não ajuda a quebrar dependências e não é um método, é uma função. Uma função virtual às vezes é chamada de método em C++.

Portanto, é um exemplo de uma função de fábrica.

### O Padrão de Design Clássico Strategy (Estratégia)

O Contexto aponta para a estratégia, a força é a delegação e tem um limite de arquitetura entre o uso e os detalhes de implementação (Baixo e Alto nível).

A estratégia OO clássica é frequentemente considerada a ÚNICA implementação, nada poderia estar mais longe da verdade. A própria Biblioteca Padrão C++ tem várias estratégias.

```cpp
template<
    class T,
    class Deleter = std::default_delete<T>
> class unique_ptr;
```

O `Deleter` é uma estratégia.

```cpp
template<
    class Key,
    class Hash = std::hash<Key>,
    class KeyEqual = std::equal_to<Key>,
    class Allocator = std::allocator<Key>
> class unordered_set;
```

`Hash`, `KeyEqual` e `Allocator` são estratégias.

### Padrão Singleton

> Garante que uma classe tenha apenas uma instância, enquanto fornece um ponto de acesso global a essa instância.

Uma forma comum de Singleton é o chamado 'Meyers' Singleton'

```cpp
// Singleton.h
// ... (código em C++ igual ao original)
```

> Sempre que você torna algo acessível a todas as partes do seu programa, você está pedindo por problemas.

Variáveis globais são uma má ideia porque:

- elas representam estado mutável;
- operações de leitura e gravação são difíceis de controlar, especialmente em ambientes multithread;
- são difíceis de se raciocinar;
- podem estar sujeitas ao problema da Ordem de Inicialização Estática (Static Initialization Order Fiasco - SIOF).

> Há momentos em que passar manualmente um objeto é gratuito ou torna o código ativamente mais difícil de ler. Alguns sistemas, como logging ou gerenciamento de memória, não devem fazer parte da API pública de um módulo.

Então, parece que às vezes precisamos de Singletons, mas Singletons criam dependências.

## As Muitas Escolhas de Padrões de Design

> Tudo Depende...

Como toda solução complexa, não existe uma fórmula mágica para resolver o problema. É difícil e complicado, então o designer precisa de uma base sólida de conhecimento.

Lista de pessoas para seguir:

- Charles Bay
- Tony van Eerd
- Mike Shah

Recomendo ver o vídeo completo, é muito interessante:

{{< youtube B4s381OrjWo >}}


## Referências

[Breaking Dependencies]: https://www.youtube.com/watch?v=B4s381OrjWo&ab_channel=MeetingCpp

- [Breaking Dependencies]

[Klaus Iglberger]: https://meetingcpp.com/2023/Speaker/items/Klaus_Iglberger.html

- [Klaus Iglberger]