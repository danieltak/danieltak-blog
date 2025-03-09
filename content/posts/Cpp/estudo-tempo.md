---
title: "Um Estudo sobre o Tempo"
date: '2024-03-03T20:30:32-03:00'
# weight: 1
# aliases: ["/first"]
tags: ["Tempo", "STL"]
categorias: ["C++", "Snippet"]
author: "danieltak"
# author: ["Me", "You"] # multiple authors
showToc: true
TocOpen: false
draft: false
hidemeta: false
comments: false
description: "Tempo no C++ com a biblioteca STL std::chrono"
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
    image: images/estudo-tempo/timetravel.png
    alt: "Ajaj1818, CC BY-SA 4.0" # alt text
    caption: "fonte: https://commons.wikimedia.org/wiki/user:Ajaj1818" # display caption under cover
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

O tempo parece tão simples e trivial, mas ao mesmo tempo um conceito complexo e relativo. Desde muito tempo atrás o estudo sobre o tempo é realizado, na faculdade fiz um resumo do estudo de Aristóteles sobre o tempo, e até os dias de hoje as pessoas ainda debatem sobre o estudo dele e de muitos outros que vieram posteriormente.

Mas e no C++?

Neste post explicarei um pouco sbre a biblioteca STL do C++ [std::chrono][1], num post anterior expliquei sobre o [tempo no Linux](/posts/linux-time.md).

## Tempo Decorrido

No C++ 11 o `std::chrono::steady_clock` foi implementado e um TL;DR; será demonstrado nesta seção com um snippet pequeno de como obter o tempo decorrido.

Para mais detalhes, nas próximas seções uma explicação mais detalhada será realizada.

O [código a seguir](https://stackoverflow.com/a/21995693/7690982) tem uma função de template `since()` usada para contar o tempo decorrido.

Na seção de tempo do [Working Draft do Cpp][2], a explicação sobre a biblioteca `chrono` de C++ e a biblioteca `ctime` de C pode ser visualizada.

```cpp
// .h
#include <chrono>

std::chrono::steady_clock::time_point m_testTimer;
template <
    class result_t   = std::chrono::milliseconds,
    class clock_t    = std::chrono::steady_clock,
    class duration_t = std::chrono::milliseconds
>
auto since(std::chrono::time_point<clock_t, duration_t> const& start)
{
    return std::chrono::duration_cast<result_t>(clock_t::now() - start);
}

// .cpp
m_testTimer = std::chrono::steady_clock::now();
// Do something
std::cout << "Time elapsed (ms):" << since(m_testTimer).count() << std::endl;
```

Quando quiser medir o tempo que o código leva para retornar a esta função, você pode resetar no final da tarefa com `now()`, medir no início da função e inicializar a variável no construtor com o seguinte pseudocódigo no arquivo cpp:

```cpp
// .cpp
//constructor
m_testTimer = std::chrono::steady_clock::now();
// function
std::cout << "Time elapsed (ms):" << since(m_testTimer).count() << std::endl;
// Do something
m_testTimer = std::chrono::steady_clock::now();
```

Um exemplo é na robótica ou controle de posição, que é um controle muito rápido, diferente do de temperatura. Então o tempo de scan do processador ou de comunicação com outros sistemas pode interferir no resultado, use o pseudocódigo anterior para obter o tempo que a função leva para ser chamada.

## <chrono> C++11

Essencialmente, a funcionalidade de fuso horário (C++20) é baseada na funcionalidade de calendário (C++20), que são baseadas na funcionalidade chrono (C++11). Consequentemente, esta terminologia chrono básica começa com os três componentes do C++ 11, [time point][3] (ponto de tempo), [duration][4] (duração de tempo) e [clock][5] (relógio).

A biblioteca [chrono][1] foi projetada para ser capaz de lidar com o fato de que temporizadores e relógios podem ser diferentes em sistemas diferentes e melhorar a precisão com o tempo. Para evitar a introdução de um novo tipo de tempo a cada 10 anos ou mais - como aconteceu com as bibliotecas de tempo POSIX, por exemplo - o objetivo era fornecer um conceito de precisão neutra, separando a [duration][4] (duração de tempo) e o [time point][3] (ponto de tempo) de específicos [clocks][5] (relógios). Como resultado, o núcleo da biblioteca chrono consiste nos seguintes tipos ou conceitos, que servem como mecanismos abstratos para especificar e lidar com pontos e durações de tempo.

- Um [time point][3] tem um ponto de partida, a chamada [epoch][6] (época), e uma duração de tempo adicional desde a [epoch][6] (época). Um exemplo típico é um ponto no tempo que representa “Meia-noite de Ano Novo de 2000”, que é descrito como “1.262.300.400 segundos desde 1º de janeiro de 1970” (este dia é a época do relógio do sistema UNIX e POSIX).
- A [duration][4] (duração de tempo) é a diferença entre dois pontos no tempo. O número de tiques do relógio define a duração do tempo.
- Um [clock][5] (relógio) tem um ponto inicial ([epoch][6]) e um tique para calcular o ponto no tempo atual.

O relógio é o objeto que define a [epoch][6] (época) de um [time point][3] (ponto de tempo). Assim, relógios diferentes têm épocas diferentes. Em geral, as operações que lidam com vários pontos no tempo, como o processamento da duração/diferença entre dois pontos no tempo, exigem o uso da mesma época/relógio. Um relógio também fornece uma função conveniente para fornecer o ponto no tempo de agora (now). Em outras palavras, o [time point][3] (ponto de tempo) é definido como uma duração antes ou depois de uma época, que é definida por um relógio.

Para mais informações leia o [N2661 - A Foundation to Sleep On][7], esse documento fornece base e motivação para decisões importantes de projeto e é a fonte de muitas informações sobre a biblioteca <chrono>.

### Duration (Duração de Tempo)

A duração do tempo é um template de classe, `std::chrono::duration` consiste no tipo do tick `Rep` e na duração de um tick `Period`. Mais informações em [time.syn](https://eel.is/c++draft/time.syn).

```cpp
template<
    class Rep,
    class Period = std::ratio<1>
> class duration;
```

O comprimento do tick é por padrão `std::ratio<1>`. `std::ratio<1>` significa um segundo e também pode ser escrito como `std::ratio<1,1>`. Portanto, `std::ratio<60>` é um minuto e `std::ratio<1,1000>` é um milissegundo. Quando `Rep` é um número de ponto flutuante, você pode usá-lo para armazenar frações de ticks de tempo.

Um exemplo de durações personalizadas:

```cpp
std::chrono::duration<int>vinteSegundos(20);
std::chrono::duration<double,std::ratio<60>>meioMinuto(0.5);
std::chrono::duration<long,std::ratio<1,1000>> umMilisegundo(1);
```

No C++11 as durações mais importantes são definidas:

```cpp
using nanoseconds  = duration<signed integer type of at least 64 bits, nano>;
using microseconds = duration<signed integer type of at least 55 bits, micro>;
using milliseconds = duration<signed integer type of at least 45 bits, milli>;
using seconds      = duration<signed integer type of at least 35 bits>;
using minutes      = duration<signed integer type of at least 29 bits, ratio<  60>>;
using hours        = duration<signed integer type of at least 23 bits, ratio<3600>>;
using days         = duration<signed integer type of at least 25 bits,
                            ratio_multiply<ratio<24>, hours::period>>;
using weeks        = duration<signed integer type of at least 22 bits,
                            ratio_multiply<ratio<7>, days::period>>;
using years        = duration<signed integer type of at least 17 bits,
                            ratio_multiply<ratio<146097, 400>, days::period>>;
using months       = duration<signed integer type of at least 20 bits,
                            ratio_divide<years::period, ratio<12>>>;
```

Com isso, podemos declarar as durações personalizadas do exemplo anterior, utilizando as definições padrões da biblioteca:

```cpp
std::chrono::seconds      vinteSegundos(20);
std::chrono::hours        umDia(24);
std::chrono::milliseconds umMilisegundo(1);
```

Com o [seguinte exemplo](https://onlinegdb.com/zb4M_o7x5), é possível verificar o tempo decorrido desde a [epoch][6] (época) com durações personalizadas:

```cpp
#include <chrono>
#include <iostream>

int main(){

  std::cout << std::fixed << std::endl;
  
  std::cout << "Tempo desde 1.1.1970:\n" << std::endl;

  auto timeNow= std::chrono::system_clock::now();
  auto duration= timeNow.time_since_epoch();
  std::cout << duration.count() << " nanoseconds " << std::endl;

  typedef std::chrono::duration<long double,std::ratio<1,1000000>> MyMicroSecondTick;
  MyMicroSecondTick micro(duration);
  std::cout << micro.count() << " microseconds" << std::endl;
  
  typedef std::chrono::duration<long double,std::ratio<1,1000>> MyMilliSecondTick;
  MyMilliSecondTick milli(duration);
  std::cout << milli.count() << " milliseconds" << std::endl;
  
  typedef std::chrono::duration<long double> MySecondTick;
  MySecondTick sec(duration);
  std::cout << sec.count() << " seconds " << std::endl;
  
  typedef std::chrono::duration<double, std::ratio<60>> MyMinuteTick;
  MyMinuteTick myMinute(duration);
  std::cout << myMinute.count() << " minutes" << std::endl;

  typedef std::chrono::duration<double, std::ratio<60*60>> MyHourTick;
  MyHourTick myHour(duration);
  std::cout << myHour.count() << " hours" << std::endl;
  
  typedef std::chrono::duration<double, std::ratio<60*60*24*365>> MyYearTick;
  MyYearTick myYear(duration);
  std::cout << myYear.count() << " years" << std::endl;

  typedef std::chrono::duration<double, std::ratio<60*45>> MyLessonTick;
  MyLessonTick myLesson(duration);
  std::cout << myLesson.count() << " lessons" << std::endl;

  std::cout << std::endl;
}
```

#### Operações Aritméticas

No [time.duration.nonmember](https://eel.is/c++draft/time.duration.nonmember), os seguintes operadores podem ser usados:

```cpp
template<class Rep1, class Period1, class Rep2, class Period2>
  constexpr common_type_t<duration<Rep1, Period1>, duration<Rep2, Period2>>
    operator+(const duration<Rep1, Period1>& lhs, const duration<Rep2, Period2>& rhs);

Returns: CD(CD(lhs).count() + CD(rhs).count()).

template<class Rep1, class Period1, class Rep2, class Period2>
  constexpr common_type_t<duration<Rep1, Period1>, duration<Rep2, Period2>>
  operator-(const duration<Rep1, Period1>& lhs, const duration<Rep2, Period2>& rhs);

Returns: CD(CD(lhs).count() - CD(rhs).count()).

template<class Rep1, class Period, class Rep2>
  constexpr duration<common_type_t<Rep1, Rep2>, Period>
    operator*(const duration<Rep1, Period>& d, const Rep2& s);

Constraints: is_convertible_v<const Rep2&, common_type_t<Rep1, Rep2>> is true.

Returns: CD(CD(d).count() * s).

template<class Rep1, class Rep2, class Period>
  constexpr duration<common_type_t<Rep1, Rep2>, Period>
    operator*(const Rep1& s, const duration<Rep2, Period>& d);

Constraints: is_convertible_v<const Rep1&, common_type_t<Rep1, Rep2>> is true.

Returns: d * s.

template<class Rep1, class Period, class Rep2>
  constexpr duration<common_type_t<Rep1, Rep2>, Period>
    operator/(const duration<Rep1, Period>& d, const Rep2& s);

Constraints: is_convertible_v<const Rep2&, common_type_t<Rep1, Rep2>> is true and Rep2 is not a specialization of duration.

Returns: CD(CD(d).count() / s).

template<class Rep1, class Period1, class Rep2, class Period2>
  constexpr common_type_t<Rep1, Rep2>
    operator/(const duration<Rep1, Period1>& lhs, const duration<Rep2, Period2>& rhs);

Let CD be common_type_t<duration<Rep1, Period1>, duration<Rep2, Period2>>.

Returns: CD(lhs).count() / CD(rhs).count().

template<class Rep1, class Period, class Rep2>
  constexpr duration<common_type_t<Rep1, Rep2>, Period>
    operator%(const duration<Rep1, Period>& d, const Rep2& s);

Constraints: is_convertible_v<const Rep2&, common_type_t<Rep1, Rep2>> is true and Rep2 is not a specialization of duration.

Returns: CD(CD(d).count() % s).

template<class Rep1, class Period1, class Rep2, class Period2>
  constexpr common_type_t<duration<Rep1, Period1>, duration<Rep2, Period2>>
    operator%(const duration<Rep1, Period1>& lhs, const duration<Rep2, Period2>& rhs);

Returns: CD(CD(lhs).count() % CD(rhs).count()).
```

Ou os [operadores de comparação](https://eel.is/c++draft/time.duration.comparisons):

```cpp
template<class Rep1, class Period1, class Rep2, class Period2>
  constexpr bool operator==(const duration<Rep1, Period1>& lhs,
                            const duration<Rep2, Period2>& rhs);

Returns: CT(lhs).count() == CT(rhs).count().

template<class Rep1, class Period1, class Rep2, class Period2>
  constexpr bool operator<(const duration<Rep1, Period1>& lhs,
                           const duration<Rep2, Period2>& rhs);

Returns: CT(lhs).count() < CT(rhs).count().

template<class Rep1, class Period1, class Rep2, class Period2>
  constexpr bool operator>(const duration<Rep1, Period1>& lhs,
                           const duration<Rep2, Period2>& rhs);

Returns: rhs < lhs.

template<class Rep1, class Period1, class Rep2, class Period2>
  constexpr bool operator<=(const duration<Rep1, Period1>& lhs,
                            const duration<Rep2, Period2>& rhs);

Returns: !(rhs < lhs).

template<class Rep1, class Period1, class Rep2, class Period2>
  constexpr bool operator>=(const duration<Rep1, Period1>& lhs,
                            const duration<Rep2, Period2>& rhs);

Returns: !(lhs < rhs).

template<class Rep1, class Period1, class Rep2, class Period2>
  requires three_way_comparable<typename CT::rep>
  constexpr auto operator<=>(const duration<Rep1, Period1>& lhs,
                             const duration<Rep2, Period2>& rhs);

Returns: CT(lhs).count() <=> CT(rhs).count().
```

O ponto importante aqui é que o tipo de unidade de duas durações envolvidas em tal operação pode ser diferente. Devido a uma sobrecarga fornecida de `common_type<>` para durações, a duração resultante terá uma unidade que é o máximo divisor comum das unidades de ambos os operandos.

Então no seguinte exemplo, `d1 - d2` retorna 41990 ticks e não 41.99 ticks. Se desejar um número com ponto flutuante, as definições padrões não podem ser utilizadas, pois declaram como int, mas uma personalizada com o tipo `long double` deve ser usada.

```cpp
#include <chrono>
#include <iostream>

typedef std::chrono::duration<long double> MySecondTick;

int main(){
    
MySecondTick sec(0);
    
std::chrono::seconds       d1(42);   // 42 seconds
std::chrono::milliseconds  d2(10);   // 10 milliseconds

sec = d1 - d2;
std::cout << (d1 - d2).count() << std::endl;
std::cout << sec.count() << std::endl;
}
```

Como vimos, conversões implícitas para um tipo de unidade mais preciso são sempre possíveis. No entanto, as conversões para um tipo de unidade mais grosseiro não o são, pois você pode perder informações. Por exemplo, ao converter um valor integral de 42.010 milissegundos em segundos, o valor integral resultante, 42, significa que a precisão de ter uma duração de 10 milissegundos em 42 segundos é perdida. Mas você ainda pode forçar explicitamente tal conversão com uma duração_cast. Por exemplo:

```cpp
std::chrono::seconds sec(55);
std::chrono::minutes m1 = sec;      // ERRO
std::chrono::minutes m2 =
std::chrono::duration_cast<std::chrono::minutes>(sec);  // OK
```

Como outro exemplo, a conversão de uma duração com um tipo de ponto flutuante também requer uma conversão explícita para convertê-la em um tipo de duração integral:

```cpp
std::chrono::duration<double,std::ratio<60>> halfMin(0.5);
std::chrono::seconds s1 = halfMin;   // ERROR
std::chrono::seconds s2 =
std::chrono::duration_cast<std::chrono::seconds>(halfMin);  // OK
```

Um exemplo típico é o código que segmenta uma duração em unidades diferentes. Por exemplo, o código a seguir segmenta uma duração de milissegundos nas horas, minutos, segundos e milissegundos correspondentes:

```cpp
#include <chrono>
#include <iomanip>
#include <iostream>

using namespace std::chrono;
using namespace std;

milliseconds ms(7255042);

int main(){


hours   hh        = duration_cast<hours>(ms);
minutes mm        = duration_cast<minutes>(ms % chrono::hours(1));
seconds ss        = duration_cast<seconds>(ms % chrono::minutes(1));
milliseconds msec = duration_cast<milliseconds>(ms % chrono::seconds(1));

// and print durations and values:
std::cout << "raw: " << hh.count() << "::" << mm.count() << "::"
                << ss.count() << "::" << msec.count() << std::endl;
std::cout << "     " << setfill('0') << setw(2) << hh.count() << "::"
                                << setw(2) << mm.count() << "::"
                                << setw(2) << ss.count() << "::"
                                << setw(3) << msec.count() << std::endl;
}
```

A classe também fornece três funções estáticas: `zero()`, que produz uma duração de 0 segundos, bem como `min()` e `max()`, que produzem o valor mínimo e máximo que uma duração pode ter.

### Relógios (Clocks)

Um relógio consiste em um ponto de partida e um tique de tempo. Por exemplo, um relógio pode marcar em milissegundos desde a [época do UNIX][6] (1º de janeiro de 1970) ou em nanossegundos desde o início do programa. Além disso, um relógio fornece um tipo para qualquer ponto de tempo especificado de acordo com esse relógio.

O C++ oferece três relógios, que podem ser vistos em [system.clock](https://eel.is/c++draft/time.clock):

- std::system_clock representa pontos de tempo associados ao relógio de tempo real usual do sistema atual. Este relógio também fornece funções convenientes `to_time_t()` e `from_time_t()` para converter entre qualquer ponto no tempo e o tipo de hora do sistema C `time_t`, o que significa que você pode converter de e para horários do calendário.
- std::steady_clock dá a garantia de que nunca será ajustado. Assim, os valores dos pontos no tempo nunca diminuem à medida que o tempo físico avança e avançam a uma taxa constante em relação ao tempo real.
- std::high_resolution_clock representa um relógio com o período de tick mais curto possível no sistema atual.

Observe que o padrão não fornece requisitos para a precisão, a [epoch][6] e o intervalo (pontos de tempo mínimo e máximo) desses relógios. Normalmente, o ponto de partida de std::chrono:system_clock é 1.1.1970, a chamada [era UNIX][6]. Para std::chrono::steady_clock, normalmente o tempo de inicialização do seu PC.

#### Precisão e Estabilidade

É interessante saber quais relógios são estáveis ​​e qual precisão eles fornecem. Você obtém as respostas pelas propriedades dos relógios.

```cpp
#include <chrono>
#include <iomanip>
#include <iostream>

using namespace std;

template <typename C>
void printClockData ()
{
    cout << "- precisão: ";
    // if time unit is less or equal one millisecond
    typedef typename C::period P;// type of time unit
    if (ratio_less_equal<P,milli>::value) {
       // convert to and print as milliseconds
       typedef typename ratio_multiply<P,kilo>::type TT;
       cout << fixed << double(TT::num)/TT::den
            << " milliseconds" << endl;
    }
    else {
        // print as seconds
        cout << fixed << double(P::num)/P::den << " seconds" << endl;
    }
    cout << "- estável: " << boolalpha << C::is_steady << endl;
}

int main(){
    std::cout << "system_clock: " << std::endl;
    printClockData<std::chrono::system_clock>();
    std::cout << "\nhigh_resolution_clock: " << std::endl;
    printClockData<std::chrono::high_resolution_clock>();
    std::cout << "\nsteady_clock: " << std::endl;
    printClockData<std::chrono::steady_clock>();
}
```

Resultado:

```
system_clock: 
- precisão: 0.000001 milliseconds
- estável: false

high_resolution_clock: 
- precisão: 0.000001 milliseconds
- estável: false

steady_clock: 
- precisão: 0.000001 milliseconds
- estável: true
```

Um relógio estável é um relógio monotônico, o que significa que o tempo só avança, nunca vai para trás, como um cronômetro. Ou seja, o valor retornado por uma chamada para `now()` é sempre menor ou igual ao valor retornado pela próxima chamada para `now()`.

Isso significa que você pode usar esse relógio para mediar o tempo antes de um evento, o tempo após um evento e subtraí-los confiavelmente para obter a duração do evento porque o relógio não será ajustado durante esse tempo.

### Time Point (Ponto de Tempo)

Um ponto de tempo representa um ponto específico no tempo, associando uma duração positiva ou negativa a um determinado relógio.

O [template da classe time_point](https://eel.is/c++draft/time.point) é a seguinte:

```cpp
namespace std::chrono {
  template<class Clock, class Duration = typename Clock::duration>
  class time_point {
  public:
    using clock    = Clock;
    using duration = Duration;
    using rep      = typename duration::rep;
    using period   = typename duration::period;

  private:
    duration d_;                                                // exposition only

  public:
    // [time.point.cons], construct
    constexpr time_point();                                     // has value epoch
    constexpr explicit time_point(const duration& d);           // same as time_point() + d
    template<class Duration2>
      constexpr time_point(const time_point<clock, Duration2>& t);

    // [time.point.observer], observer
    constexpr duration time_since_epoch() const;

    // [time.point.arithmetic], arithmetic
    constexpr time_point& operator++();
    constexpr time_point operator++(int);
    constexpr time_point& operator--();
    constexpr time_point operator--(int);
    constexpr time_point& operator+=(const duration& d);
    constexpr time_point& operator-=(const duration& d);

    // [time.point.special], special values
    static constexpr time_point min() noexcept;
    static constexpr time_point max() noexcept;
  };
}
```

Note no trecho a seguir, que é necessário um relógio com duração ou de um relógio e uma duração.

```cpp
namespace std {
   namespace chrono {
     template <typename Clock,
               typename Duration = typename Clock::duration>
         class time_point;
   }
}
```

O programa a seguir atribui esses pontos de tempo a tp e os imprime convertidos em uma notação de calendário:

```cpp
#include <chrono>
#include <ctime>
#include <string>
#include <iostream>

std::string asString (const std::chrono::system_clock::time_point& tp)
{
     // convert to system time:
     std::time_t t = std::chrono::system_clock::to_time_t(tp);
     std::string ts = std::ctime(&t);// convert to calendar time
     ts.resize(ts.size()-1);         // skip trailing newline
     return ts;
}

int main()
{
 
     // print the epoch of this system clock:
     std::chrono::system_clock::time_point tp;
     std::cout << "epoch: " << asString(tp) << std::endl;

     // print current time:
     tp = std::chrono::system_clock::now();
     std::cout << "now:   " << asString(tp) << std::endl;

     // print minimum time of this system clock:
     tp = std::chrono::system_clock::time_point::min();
     std::cout << "min:   " << asString(tp) << std::endl;

     // print maximum time of this system clock:
     tp = std::chrono::system_clock::time_point::max();
     std::cout << "max:   " << asString(tp) << std::endl;
}
```

## <chrono> C++20

No C++20 os seguintes relógios foram adicionados:

- utc_clock
- tai_clock
- gps_clock
- file_clock
- local_t

Os relógios `std::chrono::steady_clock` e `std::chrono::file_clock` têm uma epoch especificada na implementação. As epochs de `std::chrono::system_clock`, `std::chrono::gps_clock`, `std::chrono::tai_clock` e `std::chrono::utc_clock` começam às 00:00:00. `std::chrono::file_clock` é o relógio para entradas do sistema de arquivos.

Além disso, o C++ 11 oferece suporte a `std::chrono::high_resolution_clock`.

### clock_cast

Com o [std::chrono::clock_cast][10], você pode converter pontos de tempo entre os relógios com uma epoch. Estes são os relógios `std::chrono::system_clock`, `std::chrono::utc_clock`, `std::chrono::gps_clock` e `std::chrono::tai_clock`. Além disso, `std::chrono::file_clock` suporta conversão.

```cpp
#include <iostream>
#include <sstream>
#include <chrono>


int main() {

  std::cout << '\n';

  using namespace std::literals;

  auto timePoint = std::chrono::system_clock::now();

  auto timePointUTC = std::chrono::clock_cast<std::chrono::utc_clock>(timePoint);
  std::cout << "UTC_time:  " << std::format("{:%F %X %Z}", timePointUTC) << '\n';

  auto timePointSys = std::chrono::clock_cast<std::chrono::system_clock>(timePoint);
  std::cout << "sys_time:  " << std::format("{:%F %X %Z}", timePointSys) << '\n';

  auto timePointFile = std::chrono::clock_cast<std::chrono::file_clock>(timePoint);
  std::cout << "file_time: " << std::format("{:%F %X %Z}", timePointFile) << '\n';

  auto timePointGPS = std::chrono::clock_cast<std::chrono::gps_clock>(timePoint);
  std::cout << "GPS_time:  " << std::format("{:%F %X %Z}", timePointGPS) << '\n';

  auto timePointTAI = std::chrono::clock_cast<std::chrono::tai_clock>(timePoint);
  std::cout << "TAI_time:  " << std::format("{:%F %X %Z}", timePointTAI) << '\n';

  std::cout << '\n';

}
```

### std::chrono::parse

A função `std::chrono::parse` analisa o objeto chrono de um fluxo IO. Nas linhas a seguir, std::chrono::clock_cast converte o timePoint no relógio especificado. A linha a seguir exibe o ponto no tempo, especificando sua data (%F), sua representação de hora local (%X) e sua abreviação de fuso horário (%Z).

```cpp
std::istringstream{"2024-1-1 21:00:00"} >> std::chrono::parse("%F %T"s, timePoint);
```

Essa função ainda não foi implementada na maioria dos compiladores, e o gcc 14 ainda será lançado com o suporte a esta versão, o MSVC já possui suporte.

## Referência

- [std::chrono][1]

[1]: https://en.cppreference.com/w/cpp/chrono

- [Cpp Time library][2]

[2]: https://eel.is/c++draft/time

- [time_point][3]

[3]: https://en.cppreference.com/w/cpp/chrono/time_point

- [duration][4]

[4]: https://en.cppreference.com/w/cpp/chrono/duration

- [Clock][5]

[5]: https://en.cppreference.com/w/cpp/named_req/Clock

- [Era Linux / Epoch][6]

[6]: https://pt.wikipedia.org/wiki/Era_Unix

- [N2661 - A Foundation to Sleep On][7]

[7]: https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2008/n2661.htm

- [Clocks and Timers][8]

[8]: https://www.informit.com/articles/article.aspx?p=1881386&seqNum=2

- [Relógios de Monotônicos][9]

[9]: https://dev.to/zanfranceschi/conceito-relogios-monotonicos-1cni

- [clock_cast][10]

[10]: https://en.cppreference.com/w/cpp/chrono/clock_cast