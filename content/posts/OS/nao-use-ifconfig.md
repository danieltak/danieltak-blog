---
title: "Não use o ifconfig"
date: '2024-03-12T19:11:32-03:00'
# weight: 1
# aliases: ["/first"]
tags: ["Redes", "Linux"]
categorias: ["Linux", "Opinião"]
author: "danieltak"
# author: ["Me", "You"] # multiple authors
showToc: true
TocOpen: false
draft: false
hidemeta: false
comments: false
description: "Use o comando do Linux `ip` ao invés do antigo `ifconfig`"
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

## Por quê?

Em uma resposta do website [Server Fault de 2012][1], **"Eu devo parar de usar o ifconfig?"**.

A resposta é a seguinte:

>O comando `/bin/ip` já existe há algum tempo. Mas as pessoas continuam usando o comando antigo `/sbin/ifconfig`. Sejamos claros: o `ifconfig` não irá desaparecer rapidamente, mas sua versão mais recente, `ip`, é mais poderosa e eventualmente irá substituí-lo.
>
>A página [man do ip][2] pode parecer intimidante no início, mas depois que você se familiarizar com a sintaxe do comando, será uma leitura fácil. Esta página não apresentará os novos recursos do ip. Em vez disso, apresenta uma comparação lado a lado entre ifconfig e ip para obter uma visão geral rápida da sintaxe do comando.
>
>Da mesma forma, os comandos `arp`, `route` e `netstat` também estão obsoletos.

O [Iproute2][5] é uma coleção de utilidades para o controle de rede e tráfego TCP/IP e substitui o `ifconfig` (antigo `net-tools`) no Linux.

## Opinião

Nessa discussão de parar de usar o comando `ifconfig` o único motivo de manter o uso é de que é mais simples e curto. Mas eu, pessoalmente, prefiro um método mais completo e que o comando, por mais longo que seja, descreva a sua intenção, para eu conseguir ler o código com fluidez. Sem precisar ficar pesquisando o manual de cada função...

Outro motivo são os sistemas mais modernos, redes de empresas com firewall e afins, o ifconfig é muito útil para testes e configurar manualmente um dispositivo simples. Mas no momento em que são necessários rotas, switches e muitos outros parâmetros, um método mais robusto deve ser utilizado.

Outro motive é que o `net-tools` não é mais mantido e atualizado, o post [ifconfig sucks][4] explica melhor os problemas do ifconfig nos sistemas atuais.

Por que não aprender uma ferramenta completa? No mundo da era da internet e da Indústria 4.0, com certeza você vai se deparar com uma rede mais complexa.

## Referência

- [Should I quit using Ifconfig?][1]

[1]: https://serverfault.com/questions/458628/should-i-quit-using-ifconfig

- [ip][2]

[2]: https://linux.die.net/man/8/ip

- [Deprecated Linux networking commands and their replacements][3]

[3]: https://dougvitale.wordpress.com/2011/12/21/deprecated-linux-networking-commands-and-their-replacements/

- [ifconfig sucks][4]

[4]: https://inai.de/2008/02/19

- [Iproute2 ][5]

[5]: https://wiki.linuxfoundation.org/networking/iproute2