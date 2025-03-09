---
title: "Enviar Sinal para Pthread ou Processo"
date: '2024-03-10T21:11:32-03:00'
# weight: 1
# aliases: ["/first"]
tags: ["Linux"]
categorias: ["C++", "Linux", "Snippet"]
author: "danieltak"
# author: ["Me", "You"] # multiple authors
showToc: true
TocOpen: false
draft: false
hidemeta: false
comments: false
description: "Como enviar sinais para uma thread ou processo no POSIX"
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

Se você deseja enviar um sinal para um `thread`, você pode usar `pthread_kill()`, embora não seja semanticamente correto, a página man7 afirma:

> A função pthread_kill() envia o sinal `sig` para `thread`, um
       thread no mesmo processo que o chamador. O sinal é
       direcionado de forma assíncrona ao thread.
>
> Se `sig` for 0, nenhum sinal será enviado, mas a verificação de erros ainda será
       realizada.

## Vivo ou Morto?

### Thread

Um código para obter o sinal de uma `thread` e verificar se a `thread` está "viva":

```cpp	
pthread_t m_iThreadID = your_thread_id_here;
int	iStatus  = pthread_kill( m_iThreadID, 0 );
if( iStatus != 0 )  
{
    // Thread Stopped!
    std::cout << "pthread_kill Error: " << errno << std::endl;
}
```

Porém, é semanticamente estranho usar uma função kill para recuperar um sinal e não matar o thread, certo?

Embora pareça estranho, [pthread_kill()][1] é amplamente utilizado e possui muitos tutoriais e exemplos.

Se você quiser usar outra função ou enviar parâmetros, [pthread_sigqueue()][2] pode ser usado. Da página de manual:

> A função `pthread_sigqueue()` executa uma tarefa semelhante a
       sigqueue(3), mas, em vez de enviar um sinal para um processo, ele
       envia um sinal para um thread no mesmo processo que o thread chamador.
>
> O argumento thread é o ID de um thread no mesmo processo que
       o chamador. O argumento sig especifica o sinal a ser enviado.
       O argumento value especifica dados para acompanhar o sinal; ver
       sigqueue(3) para detalhes.

O argumento opcional na página de manual:

> O argumento value é usado para especificar um item acompanhante de
       dados (um número inteiro ou um valor de ponteiro) a serem enviados com o
       sinal, e tem o seguinte tipo:
>
>           union sigval {
>               int   sival_int;
>               void *sival_ptr;
>           };

Um exemplo com um argumento value nulo:

```cpp	
pthread_t m_iThreadID = your_thread_id_here;
sigval_t siValue;

int	iStatus  = pthread_sigqueue( m_iThreadID, 0, siValue );
if( iStatus != 0 )  
{
    // Thread Stopped!
    std::cout << "pthread_sigqueue Error: " << errno << std::endl;
}
```

### Processos

O mesmo pode ser aplicado aos processos!

A função [kill()][3] pode ser usada para obter o status de uma função, na página man:

>A chamada de sistema [kill()][3] pode ser usada para enviar qualquer sinal para qualquer
>grupo de processos ou processo.
>
>Se pid for positivo, então o sinal sig é enviado ao processo com
>o ID especificado pelo `pid`.
>
>Se `pid` for igual a 0, então sig é enviado para todos os processos do processo
>grupo do processo de chamada.
>
>Se `pid` for igual a -1, então sig é enviado para todos os processos para os quais o
>o processo de chamada tem permissão para enviar sinais, exceto para
>processo 1 (init), mas veja abaixo.
>
>Se `pid` for menor que -1, então sig é enviado para todos os processos no
>grupo de processos cujo ID é -pid.
>
>Se `sig` for 0, nenhum sinal será enviado, mas as verificações de existência e permissão ainda são realizadas; isso pode ser usado para verificar a existência de um ID de processo ou ID de grupo de processos que o chamador está permitido sinalizar.
>
>Para que um processo tenha permissão para enviar um sinal, ele deve
ser privilegiado (no Linux: ter o recurso CAP_KILL no
namespace do usuário do processo alvo), ou o real ou efetivo ID do usuário do processo de envio deve ser igual à configuração real ou salva.
>No caso do SIGCONT, é suficiente quando os processos de envio e recebimento pertencem ao
mesma sessão. (Historicamente, as regras eram diferentes; veja NOTAS.)

Um exemplo:

```cpp	
pid_t m_iProcID = your_proc_id_here;

int	iStatus  = kill( m_iProcID, 0 );
if( iStatus != 0 )  
{
    // Process Stopped!
    std::cout << "kill Error: " << errno << std::endl;
}
```

Ou para usar o `sigqueue()`:

```cpp	
pid_t m_iProcID = your_proc_id_here;
sigval_t siValue;

int	iStatus  = sigqueue( m_iProcID, 0, siValue );
if( iStatus != 0 )  
{
    // Process Stopped!
    std::cout << "sigqueue Error: " << errno << std::endl;
}
```

### Sinais

Os [sinais][4] descritos no manual do POSIX podem ser usados para enviar sinais para a thread e uma ação será realizada, por exemplo, para matar uma thread ou processo o `SIGKILL` pode ser utilizado.

```cpp
pthread_kill( m_iThreadID, SIGKILL );
```

O valor de enum dos sinais podem variar para cada processador ou distribuição do Linux, no Ubuntu os signais podem ser vistos no [manual signal - lista de sinais disponíveis][5].

## Referência

- [pthread_kill man7][1]

[1]: https://man7.org/linux/man-pages/man3/pthread_kill.3.html

- [pthread_sigqueue][2]

[2]: https://man7.org/linux/man-pages/man3/pthread_sigqueue.3.html

- [kill][3]

[3]: https://man7.org/linux/man-pages/man2/kill.2.html

- [signal][4]

[4]: https://man7.org/linux/man-pages/man7/signal.7.html

- [signal Ubuntu][5]

[5]: https://manpages.ubuntu.com/manpages/trusty/pt/man7/signal.7.html