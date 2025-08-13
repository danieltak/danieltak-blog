---
title: "Sistemas de Visão Industrial - Fundamentos Básicos"
date: '2025-07-17T16:11:32-03:00'
# weight: 1
# aliases: ["/first"]
categorias: ["Computer Vision"]
tags: ["Fotografia", "Sistema de Visão Industrial"]
author: "danieltak"
# author: ["Me", "You"] # multiple authors
showToc: true
TocOpen: false
draft: false
hidemeta: false
comments: false
description: "Fundamentos Básicos para a Visão Computacional na Indústria."
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

Esse é o primeiro de uma série de posts que pretendo fazer sobre Sistemas de Visão Industriais, em que pode ser aplicado também em visão computacional comum, mas com a diferença que abordarei alguns temas como equipamentos mais robustos, feita para aguentar o tranco da indústria: 24 horas por dia, 7 dias por semana, sem pedir férias.

Portanto, a única diferença é essa: na indústria o sistema precisa ser robusto e muitas vezes rápido. Para isso, conseguimos controlar bem o sistema de captura de imagem e obter fotos mais padronizadas e com menos ruídos. O aumento da qualidade da obtenção da imagem mitiga ou elimina o tempo de processamento, antes do algoritmo de obter os dados desejados na imagem.

Como a captura da imagem é importante, neste post falarei primeiro dos conceitos básicos de fotografia e visão computacional.

Podemos utilizar câmeras 2D e 3D, com variações nas tecnologias. Em câmeras 3D, há muitas tecnologias em que uma linha é adquirida (perfil) e com um encoder medimos a posição e conseguimos juntar em uma imagem 3D, sabendo o perfil e a posição de cada perfil, isso é mais preciso. Para adquirir o perfil, o LiDAR pode ser usado ou uma cortina a laser com vários emissores.
Para sistemas em que a precisão não é tão importante, uma tecnologia de time of flight (ToF) pode ser utilizada, em que uma nuvem de sinais é emitida, reflete no objeto e depois é recebida. Em outros casos, os pontos são integrados com uma câmera 2D e a imagem possui cor. Em outros duas câmeras 2D são utilizadas e uma sensação de profundidade pode ser obtida, como os olhos humanos.

Ah, e hoje o foco será nas câmeras 2D, principalmente na **resolução**, **lentes** e **iluminação**. 

> Spoiler: nem sempre mais resolução é melhor — mais pixels também significam mais trabalho para o processador.

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

Em aplicações de medição, o objetivo do sistema de visão é medir as **dimensões físicas** do objeto para avaliar a qualidade do produto. Exemplos de dimensões físicas incluem distância, diâmetro, curvatura, área, altura e volume.

### Inspecionar

Em aplicações de inspeção, o objetivo do sistema de visão é **validar determinadas características**, como a presença ou ausência de um rótulo correto em uma garrafa, parafusos em uma montagem, chocolates em uma caixa ou defeitos de superfície.

### Identificar

Em aplicações de identificação, o sistema de visão lê códigos e caracteres. Um exemplo pode ser uma câmera que lê a data de validade em uma embalagem de alimentos. Um sistema de visão pode ler códigos e caracteres simultaneamente, por exemplo, para verificar se o código e o conteúdo do texto (OCR) correspondem.

## Captura de imagem

O termo *imaging* define o ato de criar uma imagem. *Imaging* possui vários nomes técnicos: aquisição, captura ou obtenção. Obter uma imagem de alta qualidade é o objetivo número um para o sucesso de uma aplicação de visão.
Este capítulo aborda os conceitos mais básicos que são essenciais para compreender como capturar imagens.

![Captura](/posts/images/computer-vision-fundamentos/imaging.png)

### Sensor Digital

Na câmera digital, um sensor de imagem é utilizado para capturar uma imagem digital.

No sensor, há uma matriz de pixels sensíveis à luz, sendo "pixel" uma abreviação de picture elements (elementos da imagem). No caso mais simples, cada pixel no sensor corresponde a um pixel na imagem. O sensor também é, às vezes, chamado de imager (formador de imagem).

Existem duas tecnologias utilizadas para sensores de imagem digital:

- CCD (Charge-Coupled Device – Dispositivo de Carga Acoplada)

- CMOS (Complementary Metal Oxide Semiconductor – Semicondutor de Óxido de Metal Complementar)

Cada tipo possui suas vantagens e desvantagens técnicas. A diferença entre essas tecnologias não será abordada.

Em sistemas baseados em PC, um frame grabber (placa de captura) converte os dados brutos da imagem para um formato adequado ao software de análise de imagem.
Uma câmera de varredura linear (line scan camera) é um caso especial, em que o sensor possui apenas uma linha de pixels. Ela captura uma linha por vez, que pode ser analisada individualmente ou combinada com outras linhas para formar uma imagem completa.

## Lentes e Distância Focal

A lente foca a luz que entra na câmera de forma a criar uma imagem nítida, outro termo para lente é **objetiva**.

Uma imagem em foco significa que as bordas do objeto aparecem nítidas. Se o objeto estiver fora de foco, a imagem se torna borrada.
Lentes usadas em fotografia frequentemente possuem **auto-foco**, enquanto lentes para visão de máquina possuem foco ajustável manualmente.

![Foco](/posts/images/computer-vision-fundamentos/foco.png)

### Ângulo de abertura

As principais diferenças entre os tipos de lentes são o ângulo de abertura (angle view) e a distância focal (focal length). Esses dois termos são, essencialmente, maneiras diferentes de descrever a mesma coisa.

O ângulo de abertura determina quanto da cena visual a câmera consegue enxergar. Uma lente de grande angular vê uma parte maior da cena, enquanto o ângulo reduzido de uma teleobjetiva permite ver detalhes a partir de distâncias maiores.

![angleView](/posts/images/computer-vision-fundamentos/Photo_lenses_with_a_focal_length_and_angle.svg)

### Distância focal

A distância focal é a distância entre a lente e o ponto focal. Quando o ponto focal está sobre o sensor, a imagem está em foco.

![DistFocalTeoria](/posts/images/computer-vision-fundamentos/Biconvex_lens-behaviour_of_light_rays_from_focal_point.png)

Na imagem acima, o sensor estaria do lado esquerdo, no ponto focal (focal point), quando a imagem está em foco.

A distância focal está relacionado ao ângulo de abertura, pois uma distância focal longa corresponde a um ângulo de abertura pequeno, e vice-versa.

![DistFocal](/posts/images/computer-vision-fundamentos/distFocal.png)

### Campo de Visão (FOV - Field of View)

O FOV (Campo de Visão) em sistemas 2D é toda a área que uma câmera consegue enxergar, o FOV é especificado por sua largura e altura.

A distância do objeto é a distância entre a lente e o objeto, também chamado de distância de trabalho.

![FOV](/posts/images/computer-vision-fundamentos/fov.png)

### Abertura e F-stop

A abertura é a abertura na lente que controla a quantidade de luz que chega ao sensor, a abertura pode ser ajustável.

![Abertura](/posts/images/computer-vision-fundamentos/aperture.png)

O diâmetro da abertura do diafragma é expresso pelo seu valor F (F-stop). Valores altos de F indicam uma abertura física menor do diafragma, permitindo a passagem de menos luz para o sensor. Por outro lado, valores baixos de F correspondem a uma abertura maior, resultando em maior entrada de luz.

### Profundidade de campo

A distância mínima de foco (Minimum Object Distance) é a menor distância entre o plano focal da câmera e o objeto na qual a lente consegue obter foco nítido. Já a distância máxima de foco é a maior distância em que a lente mantém foco. Lentes padrão normalmente não possuem limite máximo, alcançando o foco até o infinito. No entanto, certos tipos de lentes especiais, como as macro, podem apresentar um limite máximo de foco definido.

O plano focal é a distância, medida a partir do plano do sensor ou filme, na qual a imagem atinge o foco mais preciso possível. Objetos posicionados ligeiramente à frente ou atrás desse plano também podem parecer nítidos, desde que permaneçam dentro de uma faixa aceitável de nitidez. Essa faixa de distâncias, na qual o foco é considerado satisfatório, é denominada profundidade de campo (Depth of Field).

A profundidade de campo depende tanto da distância focal da lente quanto da abertura utilizada. Do ponto de vista teórico, o foco perfeito ocorre apenas no plano focal, localizado a uma distância exata da lente. No entanto, na prática, considera-se como “aceitavelmente nítida” toda a região que se encontra dentro da profundidade de campo.

1. Distâncias focais longas resultam em menor profundidade de campo; distâncias focais curtas resultam em maior profundidade de campo.

2. Aberturas grandes (números F pequenos) produzem menor profundidade de campo; aberturas pequenas (números F grandes) produzem maior profundidade de campo.

### Exposição

Exposição é a quantidade total de luz captada pelo sensor durante a captura da imagem.

O nível de exposição é determinado pela combinação de quatro fatores principais:

1. Intensidade da luz incidente – quantidade de luz que atinge a lente, proveniente da cena ou objeto fotografado.

2. Sensibilidade do sensor – capacidade do sensor de responder à luz que entra pela lente, expressa em ISO. Sensores mais sensíveis (ISO alto) captam mais luz, mas podem gerar ruído digital.

3. Tempo de exposição (Exposure Time ou Shutter Speed) – duração em que o sensor permanece recebendo luz, normalmente medida em milissegundos (ms) ou frações de segundo. Tem origem no conceito de "velocidade do obturador" da fotografia tradicional. Tempos longos permitem mais luz, mas aumentam o risco de desfoque por movimento.

4. Tamanho da abertura (Aperture) – controlado pelo diafragma da lente, regula a quantidade de luz que entra. É expresso pelo valor F (F-stop), em que valores menores representam aberturas maiores.

A exposição total é o resultado combinado desses parâmetros, frequentemente referida como triângulo de exposição na fotografia (no caso de câmeras convencionais: abertura, velocidade e ISO; em visão computacional, intensidade da luz também é um fator externo relevante).

Quando o tempo de exposição é muito curto ou a luz é insuficiente, o sensor não recebe luz suficiente e a imagem fica subexposta, apresentando áreas escuras e perda de detalhes nas sombras.

Quando a luz é excessiva ou o tempo de exposição é longo demais, ocorre superexposição, saturando o sensor e resultando em áreas claras sem detalhes (regiões “estouradas”).

Em sistemas de visão computacional, o controle preciso da exposição é fundamental para garantir contraste adequado e qualidade de dados para processamento, especialmente em aplicações que exigem alta repetibilidade, como inspeção industrial e medições de precisão.

### Motion Blur

Um tema relacionado ao tempo de exposição é o motion blur (desfoque de movimento). Esse fenômeno ocorre quando o objeto se desloca durante o período em que o sensor está captando luz. Se o tempo de exposição for longo em relação à velocidade do objeto, sua imagem será registrada com contornos borrados, prejudicando a nitidez e comprometendo a robustez da aplicação.

Em aplicações onde a velocidade do objeto é elevada, muitas vezes é necessário utilizar tempos de exposição curtos para “congelar” o movimento. No entanto, isso reduz a quantidade de luz captada, tornando a imagem mais escura. Para compensar e manter um nível de luminosidade adequado, podem ser adotadas as seguintes estratégias:

1. Iluminação de alta intensidade (strobe lighting) – uso de flashes ou luzes pulsadas sincronizadas com a captura da imagem, permitindo tempos de exposição extremamente curtos sem perda significativa de luminosidade.

2. Abertura maior – aumentar o diâmetro do diafragma (reduzir o valor F), permitindo que mais luz entre na câmera.

3. Ganho eletrônico – amplificação do sinal do sensor, aumentando artificialmente a intensidade aparente da luz captada (explicado na próxima seção), com o possível custo de maior ruído na imagem.

Informações adicionais:

- O motion blur é medido em pixels de deslocamento, e seu impacto depende tanto da velocidade relativa do objeto quanto do tempo de exposição.

- Em fotografia convencional, o desfoque de movimento pode ser usado como efeito artístico (p. ex., capturar o fluxo de água ou rastros de luz).

- Em visão computacional e inspeção industrial, normalmente é um problema, pois reduz a precisão de algoritmos de detecção, medição ou reconhecimento.

- Uma regra (rule of thumb) para minimizar o motion blur é ajustar o tempo de exposição para que o deslocamento do objeto durante a captura não exceda 0,5 pixel no sensor.

## Conceitos Computaacionais

### Pixels e resolução

Um pixel é a menor unidade que compõe uma imagem digital. Em condições normais, cada pixel da imagem corresponde diretamente a um pixel físico presente no sensor da câmera.

Esses pixels são tão pequenos que só se tornam distinguíveis individualmente quando a imagem é ampliada significativamente.

A seguir, vê-se um exemplo de uma imagem extremamente pequena, com dimensões de 15×13 pixels. Nessas dimensões, o eixo X representa as colunas da imagem e o eixo Y representa as linhas. Cada quadrado do tabuleiro da imagem é um pixel.

![Pixel](/posts/images/computer-vision-fundamentos/pixel.png)

A resolução de um sensor de visão é dado por pixels, em que a representação de linhas e colunas é dado por "número x número pixels" ou pela multiplicação das linhas e colunas  "número pixels". Exemplo: 640 × 480 pixels ou 307200 pixels ou 0,3 Mp (Mega pixels).

Valores típicos de resolução de sensores em sistemas de visão computacional 2D incluem:

- VGA (Video Graphics Array): 640 × 480 pixels
- XGA (Extended Graphics Array): 1024 × 768 pixels
- SXGA (Super Extended Graphics Array): 1280 × 1024 pixels

A resolução do objeto é a dimensão física no objeto que corresponde a um único pixel no sensor da câmera. As unidades mais comuns para expressar essa resolução são micrômetros por pixel (µm/pixel) ou milímetros por pixel (mm/pixel).

Em algumas aplicações de medição, é possível obter uma resolução aparente menor que o tamanho de um pixel. Isso é viabilizado por meio de algoritmos de interpolação, capazes de extrair informações subpixel a partir dos dados capturados, aumentando a precisão da análise.

Em sistemas de visão observamos que o eixo Y na representação de imagens digitais possui direção oposta àquela ensinada na matemática escolar tradicional. Isso ocorre porque a imagem é tratada como uma matriz, na qual o canto superior esquerdo corresponde ao elemento (0,0).

Essa convenção de coordenadas e a representação matricial têm como objetivo facilitar cálculos e implementação em programação, tornando as operações sobre a imagem mais diretas e eficientes.

![Coord](/posts/images/computer-vision-fundamentos/spatial_coordinates.gif)

Exemplo de cálculo de resolução:

Possuímos um sensor XGA (1024 × 768 pixels) e o plano que gostaríamos de medir possui uma largura de 100 mm na distância desejada.

$$ Resolucao(x) = \frac{largura (mm)}{colunas (px)} = \frac{100}{1024} = 0,098 \frac{mm}{px} $$

### Intensidade

O brilho de um pixel é denominado intensidade. As informações de intensidade são registradas individualmente para cada pixel da imagem e podem assumir diferentes formatos, dependendo do tipo de espaço de cores da imagem e tipo de dado.

Por exemplo, num sistema binário cada pixel assumirá somente dois valores, que podem ser representado por duas cores na visualização da imagem.

No espaço de cores em escalas de cinza 8 bits, a cor pode variar de preto (0) a branco (255) com intensidades intermediárias em escalas de cinza.

![Grayscale](/posts/images/computer-vision-fundamentos/grayscale.png)

No espaço de cores RGB, tipicamente é utilizado um byte por pixel para cada componente de cor. Para representar informações completas de cor, são necessários três bytes por pixel, correspondendo às três componentes primárias: R (Red – vermelho), G (Green – verde) e B (Blue – azul). Porém, normalmente também temos a informação de opacidade (alpha) que é representado por mais um byte, totalizando 32 bits ou 4 bytes por pixel.

Assim, cada pixel em uma imagem colorida contém três valores numéricos independentes, um para cada canal de cor.

![RGB](/posts/images/computer-vision-fundamentos/rgb.png)

Quando a intensidade de um pixel é digitalizada e representada por um byte, a informação é quantizada em níveis discretos. A quantidade de bits utilizada para representar cada pixel é denominada profundidade de bits (bit depth).

Em sistemas de visão computacional, é comum utilizar 8 bits por pixel, o que permite representar 256 níveis de intensidade. Entretanto, sensores de alto desempenho e aplicações que exigem maior sensibilidade podem empregar profundidades de bits superiores, proporcionando maior faixa dinâmica e capacidade de capturar variações sutis de luminosidade.

Devido às diferentes quantidades de dados necessárias para armazenar cada pixel — por exemplo, 1 bit (imagem binária), 8 bits (tons de cinza) ou 24 bits (imagem colorida RGB) — o tempo de processamento de imagem tende a ser maior para imagens em tons de cinza e coloridas do que para imagens binárias.

Isso ocorre porque o aumento na profundidade de bits eleva proporcionalmente o volume de dados a ser manipulado, demandando maior capacidade de processamento e mais largura de banda de memória durante as operações de visão computacional.

### Ganho

Tempo de exposição e tamanho da abertura são métodos físicos para controlar a intensidade da imagem, regulando diretamente a quantidade de luz que chega ao sensor.

Existe também um método eletrônico, chamado ganho (gain), que amplifica os valores de intensidade depois que o sensor já foi exposto à luz. Essa amplificação funciona de forma análoga ao controle de volume de um rádio: aumentar o volume não faz o artista cantar mais alto, apenas amplifica o sinal captado.

O uso de ganho elevado como compensação para uma exposição insuficiente traz como efeito colateral a amplificação do ruído eletrônico presente no sinal, resultando em uma imagem granulada (grainy image), conforme a imagem a seguir.

![Ganho](/posts/images/computer-vision-fundamentos/gain.png)

Informações adicionais:

- Em sistemas de visão computacional, o ganho é geralmente expresso em dB (decibéis) ou em um fator multiplicativo.

- Ganho alto pode melhorar a visibilidade em condições de pouca luz, mas degrada a relação sinal-ruído (SNR), reduzindo a qualidade para análise automatizada.

- Sensores modernos podem oferecer diferentes tipos de ganho:

    - Ganho analógico – aplicado antes da conversão A/D, preserva melhor a qualidade, mas ainda aumenta o ruído de leitura.

    - Ganho digital – aplicado após a conversão A/D, não melhora o SNR e apenas aumenta a intensidade dos pixels junto com o ruído.

- Em aplicações críticas, recomenda-se priorizar aumento de luz incidente (melhor iluminação ou abertura maior) antes de recorrer a altos níveis de ganho.

### Contraste

Contraste é a diferença relativa entre as áreas claras e escuras de uma imagem.

O contraste é fundamental para a percepção visual — sem ele, não é possível distinguir formas, bordas ou detalhes, resultando em uma imagem plana e indistinta.

Informações adicionais:

- Em processamento de imagens, o contraste pode ser medido de forma global (diferença entre os tons mais claros e mais escuros) ou local (diferença entre pixels ou regiões vizinhas).

- Contraste insuficiente dificulta a segmentação e o reconhecimento de padrões, enquanto contraste excessivo pode causar perda de detalhes nas áreas muito claras ou muito escuras (clipping).

- Técnicas como equalização de histograma ou ajuste de gama podem otimizar o contraste para melhorar a análise automática ou a qualidade visual.

- Em visão computacional, o nível ideal de contraste depende da aplicação, mas geralmente busca-se maximizar a separação entre o objeto de interesse e o fundo.

### Histograma

Um histograma é um gráfico no qual os pixels de uma imagem são organizados de acordo com seus valores de intensidade em ordem crescente. No histograma, cada barra representa a quantidade de pixels que possuem uma determinada intensidade.

Em imagens em escalas de cinza, o eixo horizontal do histograma representa os níveis de intensidade (de preto à esquerda a branco à direita), enquanto o eixo vertical representa a frequência de pixels com aquele valor.

O histograma é uma ferramenta útil para compreender melhor o conceito de contraste. Um alto contraste resulta em um histograma mais largo, distribuído por uma ampla faixa de intensidades, cobrindo áreas próximas do preto e do branco. Um baixo contraste gera um histograma estreito, concentrado em uma faixa limitada de intensidades, resultando em uma imagem com pouca distinção entre áreas claras e escuras.

Informações adicionais:

- Em imagens coloridas RGB, podem ser gerados histogramas separados para cada canal (R, G e B), permitindo análise independente da distribuição de cores.

- Em visão computacional, a análise de histogramas pode auxiliar em tarefas como equalização de iluminação, detecção de falhas e segmentação por limiarização (thresholding).

- Histogramas são ferramentas fundamentais para avaliar contraste, brilho e faixa dinâmica de uma imagem.

- Ajustes de exposição, ganho, gama ou equalização de histograma podem modificar a forma do gráfico, melhorando a qualidade da imagem para visualização ou processamento automático.

- Ajustes automáticos de contraste e brilho muitas vezes são baseados na redistribuição dos valores do histograma para ocupar toda a faixa dinâmica disponível.



## Referências

[Introduction to Machine Vision]: https://www.cognex.com/what-is/machine-vision

- [Introduction to Machine Vision]

[Exploring impact and features of machine vision for progressive industry 4.0 culture]: https://www.sciencedirect.com/science/article/pii/S266635112100053X

- [Exploring impact and features of machine vision for progressive industry 4.0 culture]

[Digital imaging]: https://en.wikipedia.org/wiki/Digital_imaging

- [Digital imaging]

[What Is a CMOS Image Sensor?]: https://www.lifewire.com/cmos-image-sensor-493271

- [What Is a CMOS Image Sensor?]

[What Are the Benefits of CMOS vs CCD Machine Vision Cameras?]: https://www.1stvision.com/machine-vision-solutions/2019/07/benefits-of-cmos-based-machine-vision-cameras-vs-ccd.html

- [What Are the Benefits of CMOS vs CCD Machine Vision Cameras?]

[Aperture]: https://en.wikipedia.org/wiki/Aperture

- [Aperture]

[How to use depth of field to your advantage]: https://www.automate.org/vision/tech-papers/how-to-use-depth-of-field-to-your-advantage

- [How to use depth of field to your advantage]

[Imaging Electronics 101: Basics of Digital Camera Settings for Improved Imaging Results]: https://www.edmundoptics.com/knowledge-center/application-notes/imaging/basics-of-digital-camera-settings-for-improved-imaging-results/

- [Imaging Electronics 101: Basics of Digital Camera Settings for Improved Imaging Results]
