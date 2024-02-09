---
title: "XML parser"
date: '2024-02-07T21:11:32-03:00'
tags: ["XML","parser"]
categories: ["C++"]
author: "danieltak"
showToc: true
TocOpen: false
draft: false
hidemeta: false
comments: false
description: "Análise Sintática"
disableHLJS: true # to disable highlightjs
disableShare: false
disableHLJS: false
hideSummary: false
searchHidden: true
ShowReadingTime: true
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
    URL: "https://github.com/danieltak/danieltak-blog/blob/master/content/posts/xml.md"
    Text: "Suggest Changes" # edit text
    appendFilePath: true # to append file path to Edit link
---

## Introdução

[Libxml2][1] é um XML C parser e toolkit desenvolvido pelo projeto Gnome.

[Libxml2][2] é conhecida por ser muito portátil, a biblioteca deve ser construída e funcionar sem problemas sérios em uma variedade de sistemas (Linux, Unix, Windows, CygWin, MacOS, RISC Os, OS/2, VMS, QNX, MVS, ...).

Portanto, este XML parser é universal e pode ser utilizado em diversos casos.

Tutoriais:
- http://www.xmlsoft.org/examples/
- https://gnome.pages.gitlab.gnome.org/libxml2/tutorial/
- https://gnome.pages.gitlab.gnome.org/libxml2/examples/

Repositório:
- https://github.com/GNOME/libxml2

Espelho do Repositório:
- https://gitlab.gnome.org/GNOME/libxml2

## SAX vs DOM vs pull parser

> TL;DR; Use um analisador [DOM ou pull][3] com arquivos menores que caibam na RAM. Use um analisador SAX para arquivos grandes que não cabem. 

Depende totalmente da situação, por exemplo, se o arquivo xml for muito grande, você não pode optar pelos analisadores DOM, pois eles primeiro trazem o arquivo para a memória e depois o analisam. Nesse caso, você deve optar pelo analisador SAX, que é leve e consome menos memória.

O segundo caso é quando o arquivo não é muito grande. Nesse caso, você pode optar pelo analisador XML pull porque, nesse caso, você terá controle total sobre o XML e poderá pular o ciclo de parsing em qualquer lugar, o que não é possível no SAX. Portanto, se a tag que você está procurando é a primeira no arquivo, então por que você iria percorrer o arquivo inteiro?

Portanto, até onde sei, se você considerar apenas a velocidade com um arquivo pequeno, use o analisador XML pull e, se o arquivo for grande e você quiser analisar tudo, use o SAX.

[Qual é a diferença entre DOM e SAX?][4]

No SAX, os eventos são acionados quando o XML está sendo analisado. Quando o analisador está analisando o XML e encontra uma tag iniciando (por exemplo, `<algo>`), ele aciona o evento tagStarted (o nome real do evento pode ser diferente). Da mesma forma, quando o final da tag é encontrado durante a análise (`</algo>`), ele aciona o tagEnded. Usar um analisador SAX implica que você precisa lidar com esses eventos e dar sentido aos dados retornados com cada evento.

No DOM, não há eventos acionados durante a análise. O XML inteiro é analisado e uma árvore DOM (dos nós no XML) é gerada e retornada. Depois de analisada, o usuário pode navegar na árvore para acessar os vários dados previamente incorporados nos vários nós do XML.

Em geral, o DOM é mais fácil de usar, mas tem a sobrecarga de analisar todo o XML antes que você possa começar a usá-lo, ou seja, recomendado para arquivos pequenos.

SAX (Simple API for XML): É um processador baseado em fluxo. Você tem apenas uma pequena parte na memória a qualquer momento e "fareja" o fluxo XML implementando o código de retorno de chamada para eventos como tagStarted() etc. Ele quase não usa memória, mas você não pode fazer coisas do "DOM", como usar xpath ou percorrer árvores.

DOM (Document Object Model): Você carrega tudo na memória, o que consome muita memória. Você pode estourar a memória até mesmo com documentos de tamanho médio. Mas você pode usar xpath e percorrer a árvore etc.

### DOM

- Analisador de modelo de árvore (baseado em objeto) (árvore de nós).
- O DOM carrega o arquivo na memória e, em seguida, analisa o arquivo.
- Tem restrições de memória, pois carrega todo o arquivo XML antes de analisá-lo.
- O DOM é de leitura e gravação (pode inserir ou excluir nós).
- Se o conteúdo XML for pequeno, prefira o analisador DOM.
- É possível fazer buscas para trás e para frente para pesquisar as tags e avaliar as informações dentro das tags. Portanto, isso facilita a navegação.
- Mais lento em tempo de execução.

### SAX

- Analisador baseado em eventos (Sequência de eventos).
- O SAX analisa o arquivo à medida que o lê, ou seja, analisa nó por nó.
- Não há restrições de memória, pois ele não armazena o conteúdo XML na memória.
- O SAX é somente leitura, ou seja, não é possível inserir ou excluir o nó.
- Use o analisador SAX quando o conteúdo da memória for grande.
- O SAX lê o arquivo XML de cima para baixo e não é possível navegar para trás.
- Mais rápido em tempo de execução.

### Diferença resumida

Dom Parser - Usa uma abordagem baseada em objetos, ou seja, primeiro carrega todo o XML na memória, converte os nós XML em objetos e, em seguida, começa a analisá-los. Portanto, é bem mais lento.

Analisador SAX e PULL - eles usam uma abordagem baseada em eventos. Ambos são praticamente iguais em termos de memória e desempenho. No entanto, há algumas situações distintas sobre quando usá-los, conforme descrito abaixo.

Dom Parser - Use-o quando precisar validar todo o XML antes da análise. Nunca o utilize quando o XML for muito grande e a validação puder ser comprometida. Quando começa a analisar, ele analisa do nó inicial ao nó final. Não há como analisar somente determinados nós.

SAX - Use-o quando quiser analisar o XML inteiro. Quando começa a analisar, ele analisa do nó inicial ao nó final. Não há como analisar apenas nós específicos.

PULL - Use-o quando não quiser analisar todo o XML. É mais fácil de implementar do que o SAX, porque você não precisa manter o estado do analisador. Você pode extrair apenas um nó específico no qual esteja interessado.

Minha sugestão é: 

- se precisar de validação, opte pelo DOM;
- se o tamanho do arquivo for pequeno ou se não estiver interessado em analisar todo o XML, opte pelo PULL; 
- se o tamanho do arquivo for grande ou se precisar analisar todo o arquivo XML, opte pelo SAX.

## Libere os objetos XML

Quando usar DOM, não se esqueça de liberar o buffer e o doc dos objetos xml, principalmente quando o objeto for um membro da classe.

Use as funções fornecidas pela biblioteca, por exemplo:

- xmlFreeDoc
- xmlFreeParserCtxt
- xmlXPathFreeObject 
- xmlXPathFreeContext 
- xmlFreeTextReader 
- xmlFreeTextWriter 
- xmlBufferFree

## xmlParser vs xmlReader



## Referências

- [libxml2 API Modules][1]

[1]: https://gnome.pages.gitlab.gnome.org/libxml2/devhelp/general.html

- [libxml2 wiki][2]

[2]: https://gitlab.gnome.org/GNOME/libxml2/-/wikis/home

- [SAX parser vs XMLPull parser][3]

[3]: https://stackoverflow.com/questions/5808105/sax-parser-vs-xmlpull-parser

- [What is the difference between SAX and DOM?][4]

[4]: https://stackoverflow.com/questions/6828703/what-is-the-difference-between-sax-and-dom

- [Difference among XML SAX parser, Pull parser & DOM Parser in android][5]

[5]: https://stackoverflow.com/questions/11297273/difference-among-xml-sax-parser-pull-parser-dom-parser-in-android