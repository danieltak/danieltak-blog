---
title: "Tempo no Linux"
date: '2024-02-15T21:11:32-03:00'
# weight: 1
# aliases: ["/first"]
tags: ["Tempo", "Linux"]
categorias: ["C++", "Linux", "Snippet"]
author: "danieltak"
# author: ["Me", "You"] # multiple authors
showToc: true
TocOpen: false
draft: false
hidemeta: false
comments: false
description: "Como manipular o tempo com o header em C time.h no Linux"
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

No POSIX o [time.h][1] pode ser utilizado ou a chamada de sistema [time()][2].

Este post falará brevemente com alguns snippets sobre como alterar a data e hora no Linux POSIX.

## Estruturas de Tempo

O [time_t][3] é o tipo aritmético capaz de representar tempos. Embora não esteja definido, esse é quase sempre um valor integral (mas pode ser floating point) que contém o número de segundos (sem contar os segundos bissextos) desde 00:00, 1º de janeiro de 1970 UTC, correspondente à [Era POSIX][5].

Já o [tm][4] é uma estrutura que contém uma data e hora de calendário dividida em seus componentes. A estrutura contém nove membros do tipo int (em qualquer ordem), que são:

| Membro   | Tipo | Descrição                    | Intervalo |
|----------|------|------------------------------|-----------|
| tm_sec   | int  | segundos após o minuto       | 0-60      |
| tm_min   | int  | minutos após a hora          | 0-59      |
| tm_hour  | int  | horas desde meia noite       | 0-23      |
| tm_mday  | int  | dia do mês                   | 1-31      |
| tm_mon   | int  | meses desde Janeiro          | 0-11      |
| tm_year  | int  | anos desde 1900              |           |
| tm_wday  | int  | dias da semana desde Domingo | 0-6       |
| tm_yday  | int  | dias desde 1 de Janeiro      | 0-365     |
| tm_isdst | int  | flag de Horário de Verão     |           |

O [timespec][6] é uma estrutura que contém um intervalo dividido em segundos e nanossegundos.

O cabeçalho <sys/time.h> define a estrutura **timeval** que inclui pelo menos os seguintes membros:

```
time_t         tv_sec      seconds
suseconds_t    tv_usec     microseconds
```

O cabeçalho <sys/time.h> define a estrutura **itimerval** que inclui pelo menos os seguintes membros:

```
struct timeval it_interval timer interval
struct timeval it_value    current value
```

O cabeçalho <sys/time.h> define a estrutura **timezone** que inclui pelo menos os seguintes membros:

```
int tz_minuteswest;     /* minutes west of Greenwich */
int tz_dsttime;         /* type of DST correction */
```

## Obter a data e hora

Você pode verificar usando o comando [date][7] no terminal do Linux, ele devolve a data e hora do sistema operacional.

Para obter a hora usando o cabeçalho time.h, use a função [gettimeofday][8] e NULL para o fuso horário, ou use também a função [time()][2].

A função `gettimeofday()` obtém a hora atual, expressa em segundos e microssegundos desde 00:00 Coordinated Universal Time (UTC), 1º de janeiro de 1970, e a armazena na estrutura timeval.

```cpp
#include <sys/time.h>

struct timeval tTime;
gettimeofday( &tTime, NULL);
std::cout << tTime.tv_sec << std::endl;
std::cout << tTime.tv_usec << std::endl;
```

## Definir a data e hora

Para definir a hora usando o cabeçalho time.h, use a função `settimeofday` e o argumento NULL para o fuso horário.

A função `settimeofday()` é similar à `gettimeofday()`, porém define a hora ao invés de obter.

```cpp
#include <sys/time.h>

struct timeval tnewTime;
int iReturn;

tnewTime.tv_sec = 1691067482; // O tempo em segundos é calculado a partir de alguma classe criada; aqui estamos assumindo um valor de tempo constante.
tnewTime.tv_usec = 0;

iReturn = settimeofday( & tnewTime , NULL );

if ( iReturn == 0 )
{
    system("hwclock --systohc");
}
```

Para atualizar a hora do rtc no hardware, use o `hwclock -w` ou `hwclock --systohc`. Assim, o aplicativo funciona no espaço do usuário e atualiza a hora do sistema e, posteriormente, é necessária uma sincronização para atualizar o relógio do hardware.

Ou seja, o horário do sistema operacional foi definido com a função `settimeofday()` e depois o horário do hardware é atualizado com o horário do sistema com a chamada de sistema `hwclock --systohc`.

Para verificar a hora do rtc no hardware, use o comando `hwclock`.

Se você quiser alterar o relógio do hardware e atualizar a hora do sistema, use o comando `hwclock -s` ou `hwclock --hctosys`.

É necessário atualizar a data e hora do hardware, pois ao iniciar o dispositivo, o sistema operacional obtém a data e hora do hardware. Caso não seja atualizado, ele sempre iniciará com as definições antigas.

### Opinião

Use sempre as opções que descrevem a intenção do argumento, por exemplo, utilizar o `hwclock --systohc`, pois você está realizando a operação do sys para o hc (hardware clock). Já com `hwclock -w`, o argumento `-w` pode significar uma infinidade de coisas.

No Linux as opções das chamadas de sistema geralmente fornecem duas possibilidades, como no caso do [hwclock][9] de `-w` e `--systohc`, sempre opte pela semântica.

## Referência

- [time.h(0P)][1]

[1]: https://man7.org/linux/man-pages/man0/time.h.0p.html

- [time][2]

[2]: https://man7.org/linux/man-pages/man2/time.2.html

- [time_t][3]

[3]: https://en.cppreference.com/w/c/chrono/time_t

- [tm][4]

[4]: https://en.cppreference.com/w/cpp/chrono/c/tm

- [timespec][6]

[6]: https://en.cppreference.com/w/cpp/chrono/c/timespec

- [Posix Time][5]

[5]: https://pt.wikipedia.org/wiki/Era_Unix

- [date][7]

[7]: https://man7.org/linux/man-pages/man1/date.1.html

- [gettimeofday][8]

[8]: https://pubs.opengroup.org/onlinepubs/007908775/xsh/gettimeofday.html

- [hwclock][9]

[9]: https://man7.org/linux/man-pages/man8/hwclock.8.html