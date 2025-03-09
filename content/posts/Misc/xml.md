---
title: "XML parser"
date: '2024-02-07T21:11:32-03:00'
tags: ["XML","parser"]
categorias: ["C++"]
author: "danieltak"
showToc: true
TocOpen: false
draft: false
hidemeta: false
comments: false
description: "Analisador Sintático"
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
    image: images/xml/xml.png # image path/url
    alt: "RRZEicons, CC BY-SA 3.0 <https://creativecommons.org/licenses/by-sa/3.0>, via Wikimedia Commons" # alt text
    caption: "fonte: https://commons.wikimedia.org/wiki/File:Text-xml.svg" # display caption under cover
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

Se você já progamou utilizando o HTML, provavelmente já se deparou com o DOM, que é muito utilizado nas funções do Javascript para realizar o parsing e encontrar os elementos desejados.

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

## xmlParseFile vs xmlReadFile

Embora o [tutorial oficial][6] sugira o uso da função `xmlParseFile()`, ela não é recomendada; em vez disso, use o `xmlReadFile`. É mais eficiente, [respostas no Stack Overflow](https://stackoverflow.com/questions/19315206/xmlparsefile-vs-xmlreadfile-libxml2) e [mailing list do GNOME](https://lists.gnome.org/archives/xml/2011-May/msg00006.html) também sugerem o uso da função.

O [site oficial](https://gnome.pages.gitlab.gnome.org/libxml2/devhelp/libxml2-parser.html#xmlParseFile) possui a seguinte mensagem para a função `xmlParseFile`:

> DEPRECATED: Use xmlReadFile. parse an XML file and build a tree. Automatic support for ZLIB/Compress compressed document is provided by default if found at compile-time.

Numa tradução livre:

> DESCONTINUADO: Use xmlReadFile para analisar um arquivo XML e criar uma árvore. O suporte automático para o documento compactado ZLIB/Compress é fornecido por padrão se for encontrado em tempo de compilação.

Porém, ao invés de `xmlReadFile`, o novo [xmlReader][7] é melhor no quesito que não carrega para a memória todo o arquivo ou o [SAX2][8], porém são mais difíceis de implementar. Creio que em sistemas modernos é muito fácil criar um arquivo XML muito grande, pela grande quantidade de informação. Por mais que a memória RAM esteja maior, todos os outros recursos do computador também estão consumindo mais memória.

O seguinte [exemplo do SOen](https://stackoverflow.com/a/3968399/7690982) é um bom ponto de partida:

```cpp
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/parserInternals.h>


void start_element_callback(void *user_data, const xmlChar *name, const xmlChar **attrs) {
  printf("Beginning of element : %s \n", name);
  while (NULL != attrs && NULL != attrs[0]) {
    printf("attribute: %s=%s\n",attrs[0],attrs[1]);
    attrs = &attrs[2];
  }
}

int main() {
  const char* xml_path = "hello_world.xml";
  FILE *xml_fh = fopen(xml_path,"w+");
  fputs("<hello foo=\"bar\" baz=\"baa\">world</hello>",xml_fh);
  fclose(xml_fh);


  // Initialize all fields to zero
  xmlSAXHandler sh = { 0 };

  // register callback
  sh.startElement = start_element_callback;

  xmlParserCtxtPtr ctxt;

  // create the context
  if ((ctxt = xmlCreateFileParserCtxt(xml_path)) == NULL) {
    fprintf(stderr, "Erreur lors de la création du contexte\n");
    return EXIT_FAILURE;
  }
  // register sax handler with the context
  ctxt->sax = &sh;

  // parse the doc
  xmlParseDocument(ctxt);
  // well-formed document?
  if (ctxt->wellFormed) {
    printf("XML Document is well formed\n");
  } else {
    fprintf(stderr, "XML Document isn't well formed\n");
    //xmlFreeParserCtxt(ctxt);
    return EXIT_FAILURE;
  }

  // free the memory
  // xmlFreeParserCtxt(ctxt);


  return EXIT_SUCCESS;
}
```

## Conversão de xmlChar

De acordo com a documentação do [xmlstring][9], um `xmlChar` é um typedef de `unsigned char`. A descrição a seguir pode ser vista:

>This is a basic byte in an UTF-8 encoded string. It's unsigned allowing to pinpoint case where char * are assigned to xmlChar * (possibly making serialization back impossible).

Numa tradução livre:

>Esse é um byte básico em uma string codificada em UTF-8. Não tem sinal, o que permite identificar o caso em que char * é atribuído a xmlChar * (possivelmente impossibilitando a serialização de volta).

O `xmlChar` é o tipo básico utilizado na biblioteca [libxml2][2] e as funções `xmlCharStrdup` ou `xmlCharStrndup` podem ser usadas para obter um `xmlChar *` de um `char *`.

Há uma macro `BAD_CAST` definida:

>Macro to cast a string to an xmlChar * when one know its safe.

Numa tradução livre:

>Macro para converter uma string em um xmlChar * quando se sabe que é seguro.

Portanto, um literal de string pode ser usado para criar um [xmlChar][9] usando a macro `BAD_CAST`:

```cpp
const xmlChar* languageNode = BAD_CAST "language";
```

## Ler de um Arquivo

Se o `xmlParseFile` já for usado no projeto e o DOM é desejado, o obsoleto `xmlParseFile` poderá ser usado:

```cpp
std::string fileName = "path/to/file.xml";
xmlDocPtr docPtr = nullptr;

docPtr = xmlParseFile( filename.c_str() );

if (docPtr == nullptr)
	{
    	fprintf( stderr, "Failed to parse %s\n", filename.c_str() );
		return;
    }
xmlFreeDoc(docPtr);
```

Caso contrário, se o arquivo for pequeno, use o `xmlReadFile`:

```cpp
std::string fileName = "path/to/file.xml";
xmlDocPtr docPtr = nullptr;

docPtr = xmlReadFile(filename.c_str(), NULL, 0);

if (docPtr == nullptr)
	{
    fprintf( stderr, "Failed to parse %s\n", filename.c_str() );
		return;
  }
xmlFreeDoc(docPtr);
```

Ou para arquivos muitos grandes, verifique o exemplo do [xmlReader](https://gnome.pages.gitlab.gnome.org/libxml2/examples/reader1.c) ou do 

### Ler os Nós

Após ler o arquivo, uma árvore xml será obtida e os nós obtidos podem ser manipulados com o tipo `xmlNodePtr`.

```cpp
//Get all nodes
xmlNodePtr pRootElement =  xmlDocGetRootElement(docPtr);
```

E um condicional `if()` pode ser adicionado para verificar se o nome do elemento é o correto, utilizando a função `xmlStrcmp` para comparar strings.

```cpp
if ( !(xmlStrcmp( pRootElement->name, BAD_CAST "application_content_update" ) ) )
```

E os nós filhos podem ser obitos:

```cpp
auto childrenNodes = pRootElement->children;
```

E o conteúdo de cada nó, seja do filho ou do pai:

```cpp
xmlChar * childContent = childrenNodes->content;
xmlChar * rootContent = pRootElement->content;
```

## Ler da Memória

O `xmlParseMemory` pode ser usado para ler a partir da memória para tamanhos de buffer pequenos, mas é obsoleto.

>DEPRECATED: Use xmlReadMemory. parse an XML in-memory block and build a tree.

Numa tradução livre:

>DESCONTINUADO: Use xmlReadMemory. Analise um bloco XML na memória e crie uma árvore.

```cpp
const char *pMemory = "<?xml version='1.0'?>\n\
<document xmlns:xi=\"http://www.w3.org/2003/XInclude\">\n\
  <p>List of people:</p>\n\
  <xi:include href=\"sql:select_name_from_people\"/>\n\
</document>\n";

xmlDocPtr docPtr = nullptr;

docPtr = xmlParseMemory(pMemory, strlen(pMemory));

if (docPtr == nullptr)
	{
    	fprintf( stderr, "Failed to parse %s\n", pMemory );
		return;
    }
xmlFreeDoc(docPtr);
```

Use o `xmlReadMemory` em vez da função obsoleta:

```cpp
xmlDocPtr docPtr = nullptr;

docPtr =  xmlReadMemory(pMemory, strlen(pMemory), "pMemory.xml", NULL, 0);

if (docPtr == nullptr)
	{
    	fprintf( stderr, "Failed to parse %s\n", pMemory );
		return;
    }
xmlFreeDoc(docPtr);
```

## Escrever para Arquivo

O `xmlNewTextWriterFilename` pode ser usado para gravar no arquivo, algumas funções de gravação do `xmlwriter` usam o `xmlTextWriterPtr` como argumento para criar o conteúdo do xml.

Depois de criar o conteúdo, encerre o documento e libere o objeto.

```cpp
int rc;
std::string str("/path/to/filename.xml");
xmlTextWriterPtr writer = xmlNewTextWriterFilename(str.c_str(), 0);

rc = xmlTextWriterStartDocument(writer, "1.0", "UTF-8", NULL);
if(rc < 0)
{
	std::cout << "An error occurred on xmlTextWriterStartDocument." << std::endl;
}

rc = xmlTextWriterStartElement(writer, BAD_CAST "document");
rc = xmlTextWriterWriteAttribute(writer,
				BAD_CAST "xmlns:xi",
				BAD_CAST "http://www.w3.org/2003/XInclude" );

rc = xmlTextWriterWriteFormatComment(writer,
			"This is a comment" );

rc = xmlTextWriterEndElement(writer);

rc = xmlTextWriterWriteString(writer, BAD_CAST "List of people:");

rc = xmlTextWriterEndDocument(writer);

xmlFreeTextWriter(writer);
```

## Escrever para a Memória

O `xmlNewTextWriterMemory` pode ser usado para gravar na memória do buffer, algumas funções de gravação do `xmlwriter` usam o `xmlTextWriterPtr` como argumento para criar o conteúdo do xml.

Depois de criar o conteúdo, encerre o documento e libere os objetos (escritor e buffer).

```cpp
xmlBufferPtr buffer = xmlBufferCreate();
xmlTextWriterPtr writer = xmlNewTextWriterMemory(buffer, 0);

rc = xmlTextWriterStartDocument(writer, "1.0", "UTF-8", NULL);
if(rc < 0)
{
	std::cout << "An error occurred on xmlTextWriterStartDocument." << std::endl;
}

rc = xmlTextWriterStartElement(writer, BAD_CAST "document");
rc = xmlTextWriterWriteAttribute(writer,
				BAD_CAST "xmlns:xi",
				BAD_CAST "http://www.w3.org/2003/XInclude" );

rc = xmlTextWriterWriteFormatComment(writer,
			"This is a comment" );
rc = xmlTextWriterEndElement(writer);

rc = xmlTextWriterWriteString(writer, BAD_CAST "List of people:");

rc = xmlTextWriterEndDocument(writer);

std::string memory = reinterpret_cast<char*> buffer->content;
std::cout << memory << std::endl;

xmlFreeTextWriter(writer);
xmlBufferFree(buffer);
```

## Ler SVG

Quando você tem um `xmlNodePtr` de uma árvore xml, o exemplo a seguir usa `xmlNodePtr &pNode` como argumento da função e o seguinte xml:

```xml
<?xml version="1.0" encoding="UTF-8"?>
<svg_content>
<position>1</position>
<svg xmlns="http://www.w3.org/2000/svg" id="1" viewBox="0 0 585 240" preserveAspectRatio="xMidYMid meet">
<rect id="rect_1" x="0" y="0" width="585" height="20" stroke-width="1" stroke="#FFFFFF" fill="#000000"/>
</svg>
</svg_content>
```

O `xmlNodeDump` pode ser usado para extrair os dados svg a serem despejados em um renderizador svg:

## Pegar o Atributo

O `xmlNode` é a estrutura usada na árvore resultante da análise dos dados xml. O atributo dessa estrutura pode ser acessado a partir de `properties`.

```cpp
typedef struct _xmlNode xmlNode;
typedef xmlNode *xmlNodePtr;
struct _xmlNode {
    void           *_private;	/* application data */
    xmlElementType   type;	/* type number, must be second ! */
    const xmlChar   *name;      /* the name of the node, or the entity */
    struct _xmlNode *children;	/* parent->childs link */
    struct _xmlNode *last;	/* last child link */
    struct _xmlNode *parent;	/* child->parent link */
    struct _xmlNode *next;	/* next sibling link  */
    struct _xmlNode *prev;	/* previous sibling link  */
    struct _xmlDoc  *doc;	/* the containing document */

    /* End of common part */
    xmlNs           *ns;        /* pointer to the associated namespace */
    xmlChar         *content;   /* the content */
    struct _xmlAttr *properties;/* properties list */
    xmlNs           *nsDef;     /* namespace definitions on this node */
    void            *psvi;	/* for type/PSVI information */
    unsigned short   line;	/* line number */
    unsigned short   extra;	/* extra data for XPath/XSLT */
};
```
O seguinte código é um exemplo de como acessar os atributos:

```cpp
xmlAttrPtr attribute = svgValues->properties;
xmlChar* content = (char*) xmlNodeListGetString(svgValues->doc, attribute->children, 0);
```

## Verificar se o arquivo mudou

Geralmente os arquivos XML são usados como arquivos de configuração e exigem vários requisitos, que o usuário final não pode alterar o arquivo final manualmente, somente pelo software.

**Como verificar se um arquivo foi alterado?**

Intuitivamente, a data de modificação seria utilizada. Mas essa forma é propensa a erros e a verificação do hash deve ser utilizada.

Conforme [esta resposta do SOen](https://stackoverflow.com/a/14697861/7690982), a data de modificação deve ser utilizada pelo desempenho, e se for diferente, realizar a verificação de hash.

Porque a verificação de hash é computacionalmente pesado, então a verificação de data de modificação é um filtro para diminuir a lista de arquivos.

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

- [Tutorial][6]

[6]: https://gnome.pages.gitlab.gnome.org/libxml2/tutorial/index.html

- [xmlReader][7]

[7]: https://gnome.pages.gitlab.gnome.org/libxml2/devhelp/libxml2-xmlreader.html

- [SAX2][8]

[8]: https://gnome.pages.gitlab.gnome.org/libxml2/devhelp/libxml2-SAX2.html

- [xmlstring][9]

[9]: https://gnome.pages.gitlab.gnome.org/libxml2/devhelp/libxml2-xmlstring.html#xmlChar