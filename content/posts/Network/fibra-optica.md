---
title: "Dicas para um projeto de Fibra Óptica"
date: '2024-12-23T23:11:32-03:00'
# weight: 1
# aliases: ["/first"]
categorias: ["Redes de Computadores"]
tags: ["Fibra"]
author: "danieltak"
# author: ["Me", "You"] # multiple authors
showToc: true
TocOpen: false
draft: false
hidemeta: false
comments: false
description: "Dicas para um projeto de Fibra Óptica (ou Ótica)."
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
    image: images/fibra-optica/green-fiber.png # image path/url
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

Esse post fala sobre algumas dicas importantes ao realizar um projeto de fibra óptica (ou fibra ótica) ou acompanhar a implementação de um projeto.

Muitas vezes quando se trabalha para uma empresa multinacional ou de grande porte, o projeto acaba sendo terceirizado, mas a responsabilidade pela aprovação e implementação pode ser sua, então alguns conceitos sobre fibra são necessários.

## Monomodo ou Multimodo

O tipo de fibra pode depender do modo de dispersão da luz, isso dependerá de cada projeto. Mas se já há uma fibra instalada, saiba que não há compatibilidade entre os modos e **é necessário saber qual modo está instalado.** Outro ponto são as distâncias e curvas que a fibra realizará; **o modo pode interferir na distância; as curvas necessitam de uma angulação mínima e muitas vezes as eletrocalhas existentes não atendem com curvas de 90°**.

Um resumo rápido sobre os modos:

|    Característica    |          Monomodo          |        Multimodo       |
|:--------------------:|:--------------------------:|:----------------------:|
| Diâmetro   do núcleo | 8-10 µm                    | 50-62,5 µm             |
| Fonte de   luz       | Laser                      | LED/Laser barato       |
| Alcance              | Longas distâncias          | Curtas distâncias      |
| Uso típico           | Redes metropolitanas, WANs | Redes locais, LANs, AV |
| Custo                | Mais caro                  | Mais barato            |

### Monomodo


A fibra óptica monomodo é um tipo de fibra projetada para transmitir luz em apenas um único modo ou caminho dentro do núcleo. Isso é alcançado devido a um núcleo extremamente fino, com diâmetro típico de 8 a 10 micrômetros. Essa característica reduz significativamente a dispersão modal, permitindo que os sinais sejam transmitidos com maior clareza e a distâncias muito maiores em comparação com a fibra multimodo.

**Vantagens:**

- Baixa atenuação: Sinais são menos propensos a enfraquecer ao longo de grandes distâncias.
- Alta largura de banda: suporta transmissões de dados de altíssima velocidade.
- Menor dispersão: reduz os problemas de sobreposição de sinais.

**Desvantagens:**

- Custo mais elevado: equipamentos associados, como lasers e conectores, são mais caros.
- Complexidade na instalação: requer maior precisão no alinhamento dos conectores devido ao núcleo menor.

### Multimodo

A fibra óptica multimodo é um tipo de fibra projetada para transmitir luz em vários modos ou caminhos simultaneamente dentro de seu núcleo. Isso ocorre devido ao seu núcleo maior, com diâmetro típico de 50 µm ou 62,5 µm, permitindo que múltiplos raios de luz sejam refletidos internamente em diferentes ângulos.

**Vantagens:**

- Custo mais baixo: equipamentos, conectores e instalação são mais baratos.
- Fácil alinhamento: o núcleo maior facilita o alinhamento das conexões.
- Compatibilidade com LEDs: fontes de luz mais acessíveis.

**Desvantagens:**

- Maior dispersão modal: o uso de múltiplos modos de luz resulta em sobreposição e perda de sinal em distâncias mais longas.
- Menor alcance: é inadequado para transmissões de longa distância.
- Menor largura de banda: comparada à fibra monomodo, possui capacidade de transmissão limitada em distâncias maiores.

## Quantidade de pares nos cabos

O mais comum geralmente é a utilização do cabo de seis pares (6P) e o revestimento depende do ambiente em que a fibra será instalada.

Sempre projete mais pares do que serão utilizados, pois a fusão da fibra óptica é sempre complicada e dificilmente fica perfeita. É necessário um equipamento com precisão micrométrica, o qual nem sempre alinha corretamente na realização da fusão. Outro desafio consiste em encontrar o ponto de rompimento da fibra em longas distâncias. **Se um par de fibra estiver comprometido, substitua para um par reserva em cada ponta do cabo e o problema estará resolvido.**

## Distribuidor Interno Óptico (DIO)

O Distribuidor Interno Óptico (DIO), também conhecido como patch panel óptico ou caixa de distribuição óptica, é um equipamento utilizado em redes de fibra óptica para organizar, proteger e interconectar cabos ópticos de forma eficiente e segura. Ele desempenha um papel essencial no gerenciamento das conexões de fibra em ambientes como data centers, edifícios comerciais, redes de telecomunicações e sistemas industriais.

O DIO é uma solução indispensável para qualquer rede de fibra óptica que necessite de confiabilidade, organização e facilidade de manutenção. O DIO de rack pode ser visto na imagem a seguir:

![DIO](/posts/images/fibra-optica/DIO.png)

Fonte: Furukawa

As fibras devem estar identificadas conforme o projeto, o DIO de cada rack deve estar corretamente identificado, para conectar o mesmo par em cada lado do cabo. Imagina instalar centenas de pares de fibra com comprimentos de muitos quilômetros e não identificar ou organizar? Depois ficaria quase impossível instalar os equipamentos, realizar a manutenção ou expansão da rede.

## GBIC ou SFP

A decisão entre GBIC (Gigabit Interface Converter) e SFP (Small Form-factor Pluggable) não é inteiramente deixada ao critério do consumidor, pois depende do tipo de encaixe do dispositivo e da largura do cabo que será utilizado. O GBIC é um transceiver de maior tamanho e foi um dos primeiros formatos de transceivers usados para conexão em redes de alta velocidade, enquanto o SFP, sendo menor e mais compacto, oferece maior densidade de portas e é considerado mais moderno. Antes de adquirir o equipamento, é fundamental analisar qual tipo de transceiver é exigido pelo dispositivo em questão. Além disso, o SFP pode ser uma opção mais flexível, pois existem variantes como o SFP+ e SFP28, que suportam velocidades superiores, enquanto o GBIC é mais limitado nesse aspecto.

### Introdução

GBIC (Gigabit Interface Converter) e SFP (Small Form-factor Pluggable) são tipos de transceptores usados para conectar equipamentos de rede como switches, roteadores e servidores em redes de alta velocidade. Ambos servem ao propósito de converter sinais elétricos em ópticos (ou vice-versa) para transmissão de dados por fibra óptica ou cabo de cobre. No entanto, eles possuem diferenças significativas em termos de design, capacidade e aplicação.

|         Aspecto        |                               GBIC                              |                                                         SFP                                                         |
|:----------------------:|:---------------------------------------------------------------:|:-------------------------------------------------------------------------------------------------------------------:|
| Tamanho                | Maior, ocupa mais espaço em   dispositivos.                     | Menor, mais compacto, ideal para   equipamentos densos.                                                             |
| Capacidade   de Portas | Permite menos portas por   dispositivo devido ao tamanho maior. | Permite mais portas por   dispositivo, maximizando o uso do espaço.                                                 |
| Velocidade   de Dados  | Suporta até 1 Gbps.                                             | Suporta até 4 Gbps no padrão   inicial, com variantes mais modernas como SFP+ (10 Gbps) e QSFP (40 Gbps ou   mais). |
| Consumo   de Energia   | Maior consumo devido à tecnologia   mais antiga.                | Menor consumo, mais eficiente   energeticamente.                                                                    |
| Facilidade   de Uso    | Encaixe e troca simples   (hot-swappable).                      | Também é hot-swappable, mas mais   popular em designs modernos.                                                     |
| Compatibilidade        | Utilizado em equipamentos mais   antigos.                       | Comumente usado em dispositivos   mais recentes e de alta densidade.                                                |
| Custo                  | Geralmente mais barato devido à   obsolescência.                | Pode ser mais caro, mas tem melhor   custo-benefício em longo prazo devido à eficiência e desempenho.               |

### Dicas importantes

**Verifique se os switches comprados utilizam GBIC ou SFP e compre alguns conectores extras**, de acordo com a quantidade de switches que serão instalados. Isso é importante, porque este conector não é barato e não está sempre disponível em estoque, portanto, sempre é bom possuir spare parts.

**Verifique se o switch é fornecido com o conector de fibra,** pois muitos fabricantes não fornecem! Isso é importante, pois nem sempre o prazo de entrega é curto e o projeto pode atrasar para esperar a importação destes conectores...

## Conectores

Para redes industriais e robustas, normalmente escolha o conector Ferrule Connector (FC). Porém existem outros tipos de conectores no mercado, que podem ser vistos abaixo:

| Tipo de Conector | Características                                                                 | Aplicações                                                         |
|------------------|---------------------------------------------------------------------------------|--------------------------------------------------------------------|
| SC (Subscriber Connector) | Mecanismo de encaixe push-pull, formato quadrado, alta densidade.          | Redes de telecomunicações e data centers.                          |
| LC (Lucent Connector)     | Menor que o SC, mecanismo de travamento semelhante a RJ-45, compacto.     | Data centers e redes de alta velocidade.                           |
| ST (Straight Tip)         | Design de baioneta, cilíndrico, fácil de conectar e desconectar.          | Redes corporativas e cabeamento estruturado.                       |
| FC (Ferrule Connector)    | Mecanismo de rosca, robusto e confiável, ideal para ambientes com vibração. | Redes de telecomunicações e aplicações industriais.                |
| MTP/MPO (Multi-fiber Termination Push-on/Pull-off) | Conecta múltiplas fibras, ideal para alta densidade.               | Data centers e redes de alta capacidade.                           |
| E2000                   | Tampa de proteção automática, protege contra poeira e danos.               | Redes de telecomunicações e ambientes críticos.                    |
| MU (Miniature Unit)     | Semelhante ao LC, mas menor, permite maior densidade de porta.             | Equipamentos de rede compactos e aplicações de alta densidade.     |

## Normas

Algumas normas técnicas podem ser citadas, segue a lista:

- NBR 14771: Cabo óptico interno — Especificação especifica os requisitos para a fabricação dos cabos ópticos internos
- NBR 14772: Cabo óptico de terminação - Especificação
- ICEA S-104-696: INDOOR-OUTDOOR OPTICAL FIBER CABLE
- NBR 14773: Cabo óptico dielétrico protegido contra o ataque de roedores para aplicação subterrânea em duto ou aérea espinado — Especificação
- NBR 14433: Conectores de fibra óptica montados em mídias ópticas e adaptadores — Especificação
- NBR 14565: Cabeamento estruturado para edifícios comerciais
- ICEA S-87-640: Standard for Optical Fiber Outside Plant Communications Cable
- ICEA S-83-596: INDOOR OPTICAL FIBER CABLE
- GR-409-CORE: Generic Requirements for Indoor Fiber Optic Cable
- GR-20-CORE: Generic Requirements for Optical Fiber and Optical Fiber Cable
- GR-326: Generic Requirements for Single-Mode Optical Connectors and Jumper Assemblies

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