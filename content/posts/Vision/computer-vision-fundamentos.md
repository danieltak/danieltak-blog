---
title: "Sistemas de Visão Industrial - Fundamentos Básicos"
date: '2024-12-31T23:11:32-03:00'
# weight: 1
# aliases: ["/first"]
categorias: ["Computer Vision"]
tags: ["Fotografia", "Sistema de Visão Industrial"]
author: "danieltak"
# author: ["Me", "You"] # multiple authors
showToc: true
TocOpen: false
draft: true
hidemeta: false
comments: false
description: "Fundamentos Básicos para a Visão Computacional na Indústria."
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
    image: images/computer-vision/computer-vision.jpg # image path/url
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

Esse é o primeiro de uma série de posts que pretendo fazer sobre Sistemas de Visão Industriais, em que pode ser aplicado também em visão computacional comum, mas com a diferença que abordarei alguns temas como equipamentos mais robustos, que precisam funcionar 24 horas por dia e 7 dias por semana ininterruptos.

Portanto, a única diferença é essa: na indústria o sistema precisa ser robusto e muitas vezes rápido. Para isso, conseguimos controlar bem o sistema de captura de imagem e obter fotos mais padronizadas e com menos ruídos. O aumento da qualidade da obtenção da imagem diminui ou elimina o tempo de processamento, antes do algoritmo de obter os dados desejados na imagem.

Como a captura da imagem é importante, neste post falarei primeiro dos conceitos básicos de fotografia e visão computacional.

## O que é visão computacional?

A visão computacional é a tecnologia utilizada para substituir ou complementar inspeções e medições manuais com câmeras digitais e processamento de imagens. Essa tecnologia é aplicada em diversas indústrias para automatizar a produção e melhorar a qualidade dos produtos. A visão computacional pode ser descrita em quatro etapas:

1. Captura de Imagem: Obter uma imagem.

2. Processamento e Análise: Analisar a imagem para obter um resultado.

3. Comunicação: Enviar o resultado para o sistema que controla o processo.

4. Ação: Executar uma ação com base no resultado do sistema de visão.

## Aplicações comuns

Aplicações de sistemas visão industrial podem ser divididas em quatro tipos do ponto de vista técnico: localizar, medir, inspecionar e identificar.

### Localizar

Em aplicações de localização, o objetivo do sistema de visão é encontrar o objeto e relatar sua **posição** e **orientação**. Por exemplo, em aplicações de coleta de peças por robôs, a câmera identifica um ponto de referência no objeto e envia essa informação para um robô, que então coleta o objeto.

### Medir

Em aplicações de medição, o objetivo do sistema de visão é medir as **dimensões físicas** do objeto. Exemplos de dimensões físicas incluem distância, diâmetro, curvatura, área, altura e volume.

### Inspecionar

Em aplicações de inspeção, o objetivo do sistema de visão é **validar determinadas características**, como a presença ou ausência de um rótulo correto em uma garrafa, parafusos em uma montagem, chocolates em uma caixa ou defeitos de superfície.

### Identificar

Em aplicações de identificação, o sistema de visão lê códigos e caracteres. Um exemplo pode ser uma câmera que lê a data de validade em uma embalagem de alimentos. Um sistema de visão pode ler códigos e caracteres simultaneamente, por exemplo, para verificar se o código e o conteúdo do texto (OCR) correspondem.



## Referências

[Qual a diferença entre a fibra monomodo e multimodo?]: https://nextcable.com.br/qual-a-diferenca-entre-a-fibra-monomodo-e-multimodo/

- [Qual a diferença entre a fibra monomodo e multimodo?]

[Qual a diferença entre as fibras multimodo e monomodo?]: https://2flex.com.br/qual-a-diferenca-entre-os-cabos-opticos-monomodo-e-multimodo/

- [Qual a diferença entre as fibras multimodo e monomodo?]

[Distribuidor Interno Óptico DIO e Fusão Óptica: O guia definitivo]: https://nasatecnologia.com.br/distribuidor-interno-optico-dio-e-fusao-optica-o-guia-definitivo/

- [Distribuidor Interno Óptico DIO e Fusão Óptica: O guia definitivo]

[Qual a diferença entre GBIC e SFP?]: https://nextcable.com.br/qual-a-diferenca-entre-gbic-e-sfp/

- [Qual a diferença entre GBIC e SFP?]

[GBIC ou SFP? Qual o transceiver mais indicado para sua empresa?]: https://tecpartes.com/gbic-ou-sfp-qual-o-transceiver-mais-indicado-para-sua-empresa/

- [GBIC ou SFP? Qual o transceiver mais indicado para sua empresa?]

[Quais os diferentes tipos de conectores ópticos?]: https://nextcable.com.br/quais-os-diferentes-tipos-de-conectores-opticos/

- [Quais os diferentes tipos de conectores ópticos?]