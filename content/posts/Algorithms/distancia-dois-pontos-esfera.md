---
title: "Distância entre Dois Pontos de uma Esfera"
date: '2024-02-26T23:41:32-03:00'
# weight: 1
# aliases: ["/first"]
tags: ["Distância", "Trigonometria"]
categorias: ["PHP", "Snippet"]
author: "danieltak"
# author: ["Me", "You"] # multiple authors
showToc: true
TocOpen: false
draft: false
hidemeta: false
comments: false
description: "Distâncias entre dois pontos de uma esfera a partir de suas latitudes e longitudes."
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
    image: images/distancia-dois-pontos-esfera/havesine.png # image path/url
    alt: " Jono Hey, Sketchplanations" # alt text
    caption: "fonte: https://sketchplanations.com/the-haversine-formula" # display caption under cover
    relative: false # when using page bundles set this to true
    hidden: false # only hide on current single page
    hiddenInSingle: false
    responsiveImages: true
editPost:
    URL: "https://github.com/danieltak/danieltak-blog/blob/master/content"
    Text: "Sugerir Alterações" # edit text
    appendFilePath: true # to append file path to Edit link
---

## Geodésia

Segundo a [Wiki][1]:

> O estudo de geodésias em um elipsoide surgiu em conexão com a geodésia, especificamente com a solução de redes de triangulação. A figura da Terra é bem aproximada por um elipsoide oblato, uma esfera ligeiramente achatada. Uma geodésia é o caminho mais curto entre dois pontos em uma superfície curva, análogo a uma linha reta em uma superfície plana. A solução de uma rede de triangulação em um elipsoide é, portanto, um conjunto de exercícios de trigonometria esferoidal (Euler, 1755).
>
> Se a Terra for tratada como uma esfera, as geodésias são grandes círculos (todos fechados) e os problemas se reduzem aos da trigonometria esférica. Entretanto, Newton (1687) mostrou que o efeito da rotação da Terra faz com que ela se assemelhe a um elipsoide ligeiramente oblato: nesse caso, o equador e os meridianos são as únicas geodésias simples e fechadas. Além disso, o caminho mais curto entre dois pontos no equador não necessariamente passa pelo equador. Por fim, se o elipsoide for ainda mais perturbado para se tornar um elipsoide triaxial (com três semieixos distintos), apenas três geodésias serão fechadas.

Existem dois algoritmos mais conhecidos a [Haversine][2] e [Vincenty][3].

## Haversine vs Vincenty

[Haversine formula][5] (Great Circle Distance):

$$ D(x, y) = 2\arcsin[\\sqrt{\\sin^2( \frac{(x1 - y1)}{2}) + \\cos(x1)\\cos(y1)\\sin^2( \frac{(x2 - y2)}{2})}] $$

Usado por aproximar a terra com uma esfera e perder precisão, mas ser mais rápido e funcionar bem para pequenas distâncias.
        
[Vincenty's formulae][6] é mais preciso e é um método iterativo, que pode ocorrer erros com problemas de antipodais próximos, mas no caso de não necessitar distâncias entre Brasil e Japão, então o problema de antípode não interfere.

Por ser iterativo, pode ser mais lento, mas para distâncias num mesmo país não será um problema.

Haversine e Vincenty são dois algoritmos para resolver problemas diferentes. O Haversine calcula a distância do grande círculo em uma esfera, enquanto o Vincenty calcula a distância mais curta (geodésica) na superfície de um elipsoide de revolução. Portanto, a resposta à sua pergunta pode ser dividida em duas partes:

1. Você deseja calcular a distância em uma esfera em um elipsoide?
2. Qual é a precisão de Haversine ou Vincenty no cálculo do problema em questão?

Para aplicações terrestres, um elipsoide de revolução é uma aproximação razoável do "nível médio do mar"; o erro é de ± 100 m. O achatamento desse elipsoide é pequeno, cerca de 1/300, e, portanto, pode ser aproximado por uma esfera (de igual volume, por exemplo).

As distâncias do grande círculo diferem das distâncias geodésicas em até 0,5%. Em algumas aplicações, como, por exemplo, qual é a distância do Cabo ao Cairo, esse erro pode ser desprezado. Em outras aplicações, por exemplo, a determinação de fronteiras marítimas, esse erro é muito grande (é de 5 m em uma distância de 1 km). Em geral, é mais seguro usar a distância geodésica.

Se estiver interessado na distância percorrida (de carro, barco ou avião), há muitas restrições no caminho percorrido e nem o grande círculo nem a distância geodésica, que medem o comprimento dos caminhos mais curtos em uma superfície ideal, seriam apropriados. Mas para estimativas de preço ou filtrar um mapa pelo raio do alvo, esses algoritmos se tornam interessantes.

Para distâncias e trajetos mais precisos, a API de mapa será muito mais precisa e com informações mais relevantes. As mais famosas são Google Maps, Mapbox e OpenStreetMaps.

## Código em PHP

Um exemplo de código de Haversine formula em PHP pode ser visto a seguir:

```php
<?php

class Localizador{

    public function __construct($latA,$longA,$latB,$longB ){
        if(is_float($longA) && is_float($latA) && is_float($longB) && is_float($latB)){
            $this->longA = $longA;
            $this->latA = $latA;
            $this->longB = $longB;
            $this->latB = $latB;
        }
    }

    /**
     * Calculates the great-circle distance between two points, with
     * the Vincenty formula.
     * @param float $latitudeDe Latitude of start point in [deg decimal]
     * @param float $longitudeDe Longitude of start point in [deg decimal]
     * @param float $latitudePara Latitude of target point in [deg decimal]
     * @param float $longitudePara Longitude of target point in [deg decimal]
     * @param float $raioTerra Mean earth radius in [m]
     * @return float Distance between points in [m]
     */
    public static function calcDist($latitudeDe, $longitudeDe, $latitudePara, $longitudePara, $raioTerra = 6371000){
        // converte de graus para radianos
        $latDe = deg2rad($latitudeDe);
        $lonDe = deg2rad($longitudeDe);
        $latPara = deg2rad($latitudePara);
        $lonPara = deg2rad($longitudePara);

        $lonDelta = $lonPara - $lonDe;
        $a = pow(cos($latPara) * sin($lonDelta), 2) +
            pow(cos($latDe) * sin($latPara) - sin($latDe) * cos($latPara) * cos($lonDelta), 2);
        $b = sin($latDe) * sin($latPara) + cos($latDe) * cos($latPara) * cos($lonDelta);

        $angulo = atan2(sqrt($a), $b);
        return $angulo * $raioTerra;
    }
}
```

Para um teste, vamos verificar a distância entre dois pontos de (42.167803, -87.921589) para (42.144516, -87.910345):

```php
<?php
$raioTerra = 6371000;

$latitudeDe = 42.167803;
$longitudeDe = -87.921589;

$latitudePara = 42.144516;
$longitudePara = -87.910345;

$latDe = deg2rad($latitudeDe);
$lonDe = deg2rad($longitudeDe);
$latPara = deg2rad($latitudePara);
$lonPara = deg2rad($longitudePara);

$lonDelta = $lonPara - $lonDe;
$a = pow(cos($latPara) * sin($lonDelta), 2) +
    pow(cos($latDe) * sin($latPara) - sin($latDe) * cos($latPara) * cos($lonDelta), 2);
$b = sin($latDe) * sin($latPara) + cos($latDe) * cos($latPara) * cos($lonDelta);

$angulo = atan2(sqrt($a), $b);
        
$distancia = $angulo * $raioTerra;
        
echo $distancia;
?>
```

O resultado é:

`2750.2778474759 m`

No [Google Maps](https://www.google.com/maps/dir/42.167803,+-87.921589/42.144516,+-87.910345/@42.1561577,-87.9366888,14z/am=t/data=!3m1!4b1!4m14!4m13!1m5!1m1!1s0x0:0xe9ab391aaa796aa6!2m2!1d-87.921589!2d42.167803!1m5!1m1!1s0x0:0xa427f1cf0ccb05ab!2m2!1d-87.910345!2d42.144516!3e0?entry=ttu) essa distância é de 2,8 km, sendo bem preciso.

Outro exemplo do [GeekForGeeks][8] pode ser visto no código a seguir, em que o resultado bateu com o da referência:

```php
<?php
$raioTerra = 6371000;

$latitudeDe = 53.32055555555556;
$longitudeDe = -1.7297222222222221;
$latitudePara = 53.31861111111111;
$longitudePara = -1.6997222222222223;

$latDe = deg2rad($latitudeDe);
$lonDe = deg2rad($longitudeDe);
$latPara = deg2rad($latitudePara);
$lonPara = deg2rad($longitudePara);

$lonDelta = $lonPara - $lonDe;
$a = pow(cos($latPara) * sin($lonDelta), 2) +
    pow(cos($latDe) * sin($latPara) - sin($latDe) * cos($latPara) * cos($lonDelta), 2);
$b = sin($latDe) * sin($latPara) + cos($latDe) * cos($latPara) * cos($lonDelta);

$angulo = atan2(sqrt($a), $b);
        
$distancia = $angulo * $raioTerra;
        
echo $distancia;
?>
```

## Referência

- [Estudo de geodésias em um elipsoide][1]

[1]: https://en.wikipedia.org/wiki/Geodesics_on_an_ellipsoid

- [Calculate distance, bearing and more between Latitude/Longitude points][2]

[2]: https://www.movable-type.co.uk/scripts/latlong.html

- [Vincenty solutions of geodesics on the ellipsoid][3]

[3]: https://www.movable-type.co.uk/scripts/latlong-vincenty.html

- [Is the Haversine Formula or the Vincenty's Formula better for calculating distance?][4]

[4]: https://stackoverflow.com/questions/38248046/is-the-haversine-formula-or-the-vincentys-formula-better-for-calculating-distan

- [Fórmula de haversine][5]

[5]: https://pt.wikipedia.org/wiki/F%C3%B3rmula_de_haversine

- [Vincenty's formulae][6]

[6]: https://en.wikipedia.org/wiki/Vincenty's_formulae

- [Increase Accuracy of Mapbox GL Geocoder][7]

[7]: https://stackoverflow.com/questions/70615313/increase-accuracy-of-mapbox-gl-geocoder

- [Program for distance between two points on earth][8]

[8]: https://www.geeksforgeeks.org/program-distance-two-points-earth/