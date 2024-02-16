---
title: "QML Singleton"
date: '2024-02-16T20:11:32-03:00'
# weight: 1
# aliases: ["/first"]
tags: ["Singleton", "DesignPattern"]
categorias: ["C++", "QML", "Snippet"]
author: "danieltak"
# author: ["Me", "You"] # multiple authors
showToc: true
TocOpen: false
draft: false
hidemeta: false
comments: false
description: "Instância única"
disableHLJS: true # to disable highlightjs
disableShare: false
disableHLJS: false
hideSummary: false
searchHidden: false
ShowReadingTime: true
ShowBreadCrumbs: true
ShowPostNavLinks: true
ShowWordCount: true
ShowRssButtonInSectionTermList: true
UseHugoToc: true
cover:
    image: "<images/singleton.png>" # image path/url
    alt: "https://refactoring.guru/images/patterns/content/singleton/singleton.png" # alt text
    caption: "fonte: https://refactoring.guru/" # display caption under cover
    relative: false # when using page bundles set this to true
    hidden: false # only hide on current single page
editPost:
    URL: "https://github.com/danieltak/danieltak-blog/blob/master/content"
    Text: "Sugerir Alterações" # edit text
    appendFilePath: true # to append file path to Edit link
---

## Introdução

No QML muitas vezes é necessário o acesso global à variáveis e funções, isso pode ser alcançado com um padrão de projeto [Singleton][1].

Um exemplo é a configuração global de um software, que além de ser acessado por qualquer janela, deve também salvar os dados de configuração em algum arquivo.

>O Singleton é um padrão de projeto criacional que permite a você garantir que uma classe tenha apenas uma instância, enquanto provê um ponto de acesso global para essa instância.

## Singleton

O [Refactoring.guru][1] diz o seguinte:

O padrão Singleton resolve dois problemas de uma só vez, violando o princípio de responsabilidade única:

1. **Garantir que uma classe tenha apenas uma única instância.** Por que alguém iria querer controlar quantas instâncias uma classe tem? A razão mais comum para isso é para controlar o acesso a algum recurso compartilhado, por exemplo, uma base de dados ou um arquivo.

Funciona assim: imagine que você criou um objeto, mas depois de um tempo você decidiu criar um novo. Ao invés de receber um objeto fresco, você obterá um que já foi criado.

Observe que esse comportamento é impossível implementar com um construtor regular uma vez que uma chamada do construtor deve sempre retornar um novo objeto por design.

2. **Fornece um ponto de acesso global para aquela instância.** Se lembra daquelas variáveis globais que você (tá bom, eu) usou para guardar alguns objetos essenciais? Embora sejam muito úteis, elas também são muito inseguras uma vez que qualquer código pode potencialmente sobrescrever os conteúdos daquelas variáveis e quebrar a aplicação.

Assim como uma variável global, o padrão Singleton permite que você acesse algum objeto de qualquer lugar no programa. Contudo, ele também protege aquela instância de ser sobrescrita por outro código.

Há outro lado para esse problema: você não quer que o código que resolve o problema #1 fique espalhado por todo seu programa. É muito melhor tê-lo dentro de uma classe, especialmente se o resto do seu código já depende dela.

## CMake

Muitos tutoriais antigos dizem para alterar o qmldir, mas no Qt6, o qmldir é gerado automaticamente, portanto, uma das maneiras é declarar que uma classe QML é singleton no CMake.

`set_source_files_properties(MyTheme.qml PROPERTIES QT_QML_SINGLETON_TYPE TRUE)`

E no cabeçalho da classe `pragma Singleton`

## Referência

- [Singleton Design Pattern][1]

[1]: https://refactoring.guru/pt-br/design-patterns/singleton

- [time][2]
